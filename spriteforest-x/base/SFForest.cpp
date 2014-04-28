//
//  SFForest.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFForest.h"

#include "../transition/SFTransitionScene.h"
#include "SFNodeFileParser.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFForest::SFForest(void)
: CCObject()
, m_pPath(NULL)
, m_pScenes(NULL)
, m_pDefaultScene(NULL)
{
	
}

SFForest::~SFForest(void)
{
	setPath(NULL);
	setScenes(NULL);
	setDefaultScene(NULL);
}

bool SFForest::init(void)
{
	setPath(NULL);
	setScenes(NULL);
	setDefaultScene(NULL);
	return true;
}

SFForest * SFForest::forest(const char * pszPath)
{
	SFForest * pForest = new SFForest();
	if (pForest && pForest->initWithPath(pszPath))
	{
		pForest->autorelease();
		return pForest;
	}
	CC_SAFE_DELETE(pForest);
	return NULL;
}

bool SFForest::initWithPath(const char * pszPath)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	
	if (!pszPath || strlen(pszPath) == 0)
	{
		CNLog("error");
		return false;
	}
	
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	pm->push();
	
	std::string path(pszPath);
	std::string ext(pszPath);
	ext = CNString::pathExtension(ext);
	if (strcasecmp(ext.c_str(), "plist") != 0)
	{
		path = CNString::stringByAppendingPathComponent(path, "main.plist");
	}
	
	std::string string(path);
	string = CNString::stringByDeletingLastPathComponent(string);
	CCString * pString = CCString::stringWithCString(string.c_str());
	setPath(pString);
	
	// parse it
	SFNodeFileParser * parser = SFNodeFileParser::parser(path.c_str());
	CCDictionary * pDict = parser ? (CCDictionary *)parser->node() : NULL;
	if (!pDict)
	{
		CNLog("error");
		pm->pop();
		return false;
	}
	
	// default scene name
	setDefaultScene((CCString *)pDict->objectForKey("DefaultScene"));
	if (!m_pDefaultScene)
	{
		setDefaultScene(CCString::stringWithCString("default"));
	}
	CNLog("DefaultScene: %s", m_pDefaultScene->getCString());
	
	// scene dictionary
	setScenes(CNDictionary::dictionaryForKey("Scenes", pDict));
	if (!m_pScenes)
	{
		CNLog("parse error!");
		pm->pop();
		return false;
	}
	
	// check default scene
	CCArray * allKeys = m_pScenes->allKeys();
	if (!CNString::containsInArray(m_pDefaultScene->getCString(), allKeys))
	{
		if (allKeys && allKeys->count() > 0)
		{
			setDefaultScene((CCString *)allKeys->objectAtIndex(0));
		}
		else
		{
			CNLog("error");
			pm->pop();
			return false;
		}
	}
	
	CNLog("default scene = %s", m_pDefaultScene->getCString());
	
	pm->pop();
	
	return true;
}

CCScene * SFForest::scene(const char * name) const
{
	CCString * pSceneName = (name && strlen(name) > 0) ? CCString::stringWithCString(name) : m_pDefaultScene;
	CNLog("scene name = %s", pSceneName->getCString());
	
	// get scene filename
	CCString * pFilename = (CCString *)m_pScenes->objectForKey(pSceneName->getCString());
	if (!pFilename)
	{
		CNLog("no such scene");
		return NULL;
	}
	
	// load scene data by filename
	pFilename = CCString::stringWithFormat("%s/%s", m_pPath->getCString(), pFilename->getCString());
	CNLog("loading scene from %s", pFilename->getCString());
	
	SFNodeFileParser * parser = SFNodeFileParser::parser(pFilename->getCString());
	CCDictionary * pDict = parser ? (CCDictionary *)parser->node() : NULL;
	if (!pDict)
	{
		CNLog("error");
		return NULL;
	}
	
	CCNode * pNode = SFScene::nodeWithDictionary(pDict);
	return dynamic_cast<CCScene *>(pNode);
}

bool SFForest::performScene(CCObject * data) const
{
	CCObject * scene = NULL;
	
	if (CCString * pString = dynamic_cast<CCString *>(data))
	{
		scene = this->scene(pString->getCString());
	}
	else if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(data))
	{
		scene = pDict->objectForKey("Scene");
		if (!scene)
		{
			scene = this->scene(NULL);
		}
		else if (CCString * pString = dynamic_cast<CCString *>(scene))
		{
			scene = this->scene(pString->getCString());
		}
		if (!dynamic_cast<CCScene *>(scene))
		{
			CNLog("failed to create acene");
			return false;
		}
		
		// transit the scene
		pDict->setObject(scene, "Scene");
		scene = SFTransitionScene::transitionScene(pDict);
	}
	else
	{
		scene = this->scene(NULL);
	}
	
	CCScene * pScene = dynamic_cast<CCScene *>(scene);
	if (!pScene)
	{
		CNLog("failed to create scene");
		return false;
	}
	
	SFScene::perform(pScene);
	return true;
}

NS_SF_END
