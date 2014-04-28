//
//  SFLord.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-4.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFLord.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFLord::SFLord(void)
: CCObject()
, m_pCurrentForest(NULL)
, m_pHistory(NULL)
{
	
}

SFLord::~SFLord(void)
{
	setCurrentForest(NULL);
	setHistory(NULL);
}

bool SFLord::init(void)
{
	setCurrentForest(NULL);
	setHistory(CCArray::arrayWithCapacity(29));
	return true;
}

static SFLord * m_pSharedLord = NULL;

SFLord * SFLord::sharedLord(void)
{
	if (!m_pSharedLord)
	{
		m_pSharedLord = new SFLord();
		if (m_pSharedLord && m_pSharedLord->init())
		{
			CNLog("new lord born!");
		}
		else
		{
			CNLog("could not happen!");
			CC_SAFE_DELETE(m_pSharedLord);
			m_pSharedLord = NULL;
		}
	}
	return m_pSharedLord;
}

void SFLord::end(void)
{
	if (m_pSharedLord)
	{
		CNLog("my lord is abdicating...");
	}
	CC_SAFE_RELEASE_NULL(m_pSharedLord);
}

bool SFLord::isForestExists(const char * pszPath)
{
	if (!pszPath || strlen(pszPath) == 0)
	{
		CNLog("error");
		return false;
	}
	
	std::string path(pszPath);
	std::string ext(pszPath);
	ext = CNString::pathExtension(ext);
	if (strcasecmp(ext.c_str(), "plist") != 0)
	{
		path = CNString::stringByAppendingPathComponent(path, "main.plist");
	}
	
	return CNFileManager::isExists(path.c_str());
}

bool SFLord::runIntoForest(const char * pszPath, CCObject * scene = NULL)
{
	if (!pszPath || strlen(pszPath) == 0)
	{
		CNLog("invalid path");
		return false;
	}
	std::string str(pszPath);
	{
		std::size_t pos1, pos2;
		while ((pos1 = str.find("/../")) != std::string::npos)
		{
			pos2 = str.rfind("/", pos1 - 1);
			if (pos2 == std::string::npos)
			{
				pos2 = - 1;
			}
			str = str.substr(0, pos2 + 1) + str.substr(pos1 + 4);
		}
		CNLog("convert string '%s' to '%s'", pszPath, str.c_str());
		pszPath = str.c_str();
	}
	
	if (!isForestExists(pszPath))
	{
		CNLog("forest not exists at path: %s", pszPath);
		return false;
	}
	
	CCDictionary * pHis = CCDictionary::dictionary();
	pHis->setObject(CCString::stringWithCString(pszPath), "File");
	m_pHistory->addObject(pHis);
	
	CNLog("running into forest: %s", pszPath);
	setCurrentForest(SFForest::forest(pszPath));
	return performScene(scene);
}

bool SFLord::performScene(CCObject * scene) const
{
	if (!m_pCurrentForest)
	{
		CNLog("error");
		return false;
	}
	
	CCObject * pObj = NULL;
	if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(scene))
	{
		pObj = pDict->objectForKey("Scene");
	}
	else if (scene)
	{
		pObj = scene;
	}
	if (!pObj)
	{
		pObj = new CCObject();
		pObj->autorelease();
	}
	CCDictionary * pHis = CCDictionary::dictionary();
	pHis->setObject(pObj, "Scene");
	m_pHistory->addObject(pHis);
	
	return m_pCurrentForest->performScene(scene);
}

//////////////////////////////////
//
//  history stack:
//
//        (0)   File : "/path/to/forest/root/default.bundle/main.plist"
//        (1)   Scene: [NSNull null]
//        (2)   Scene: "scene2"
//        (x)   ...
//        (x+1) File : "/path/to/forest/root/forest2.bundle/main.plist"
//        (x+2) Scene: [NSNull null]
//
bool SFLord::goBack(void)
{
	// lock begin
	
	if (!m_pHistory)
	{
		CNLog("could not happen");
		return false;
	}
	
	if (m_pHistory->count() <= 2)
	{
		CNLog("reach the first scene");
		return false;
	}
	
	m_pHistory->removeLastObject();
	
	CCDictionary * pLast = (CCDictionary *)m_pHistory->lastObject();
	if (!pLast)
	{
		CNLog("could not happen");
		m_pHistory->removeLastObject();
		return false;
	}
	
	CCString * pPath = NULL;
	if (pLast->objectForKey("File"))
	{
		// it's the bounds of anthor forest
		m_pHistory->removeLastObject();
		
		// searchig the previous forest's path
		for (int pos = m_pHistory->count() - 1; pos >= 0; pos--)
		{
			CCDictionary * pDict = (CCDictionary *)m_pHistory->objectAtIndex(pos);
			if (!pDict)
			{
				CNLog("could not happen");
				continue;
			}
			pPath = (CCString *)pDict->objectForKey("File");
			if (pPath)
			{
				CNLog("path = %s", pPath->getCString());
			}
		}
	}
	
	CCObject * pData = NULL;
	pLast = (CCDictionary *)m_pHistory->lastObject();
	if (pLast)
	{
		pData = pLast->objectForKey("Scene");
	}
	
	CC_SAFE_RETAIN(pPath);
	CC_SAFE_RETAIN(pData);
	m_pHistory->removeLastObject();
	
	// do it!
	if (pPath)
	{
		runIntoForest(pPath->getCString(), pData);
		if (m_pHistory->count() > 2)
		{
			// remove duplicated 'File' record
			m_pHistory->removeObjectAtIndex(m_pHistory->count() - 2);
		}
	}
	else
	{
		performScene(pData);
	}
	
	CC_SAFE_RELEASE(pPath);
	CC_SAFE_RELEASE(pData);
	
	// lock end
	
	return true;
}

//void SFLord::showLoadingIndicator(void)
//{
//	CNLog("not implement");
//}
//
//void SFLord::hideLoadingIndicator(void)
//{
//	CNLog("not implement");
//}

NS_SF_END
