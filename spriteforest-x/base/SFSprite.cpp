//
//  SFSprite.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFSprite.h"

#include "SFScene.h"

using namespace std;

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFSprite::SFSprite(void)
: CNSprite()
, m_pTextures(NULL)
, m_pEventDelegate(NULL)
{
	
}

SFSprite::~SFSprite(void)
{
	setTextures(NULL);
	setEventDelegate(NULL);
}

bool SFSprite::init()
{
	if (!CNSprite::init())
	{
		CNLog("init error");
		return false;
	}
	setTextures(NULL);
	setEventDelegate(NULL);
	return true;
}

CCNode * SFSprite::nodeWithString(const char * pszString)
{
	if (!pszString || strlen(pszString) == 0)
	{
		pszString = "SFSprite";
	}
	return SFNode::nodeWithString(pszString);
}

CCNode * SFSprite::nodeWithDictionary(CCDictionary * pDict)
{
	CCString * pClassName = (CCString *)pDict->objectForKey("Class");
	while (!pClassName)
	{
		// extend touch sprite
		CCString * pTouchEnabled = (CCString *)pDict->objectForKey("TouchEnabled");
		if (pTouchEnabled && pTouchEnabled->boolValue())
		{
			pDict->setObject(CCString::stringWithCString("SFTouchSprite"), "Class");
			break;
		}
		
		// extend drag sprite
		CCString * pDragEnabled = (CCString *)pDict->objectForKey("DragEnabled");
		if (pDragEnabled && pDragEnabled->boolValue())
		{
			pDict->setObject(CCString::stringWithCString("SFDragSprite"), "Class");
			break;
		}
		
		// extend text sprite
		CCString * pText = (CCString *)pDict->objectForKey("Text");
		if (pText && pText->length() > 0)
		{
			pDict->setObject(CCString::stringWithCString("SFTextSprite"), "Class");
			break;
		}
		
		pDict->setObject(CCString::stringWithCString("SFSprite"), "Class");
		break;
	}
	return SFNode::nodeWithDictionary(pDict);
}

bool SFSprite::initWithDictionary(CCDictionary * pDict)
{
	if (!CNSprite::initWithDictionary(pDict))
	{
		CNLog("init error");
		return false;
	}
	
	CCDictionary * pEventTree = CNDictionary::dictionaryForKey("EventTree", pDict);
	CCDictionary * pActionTree = CNDictionary::dictionaryForKey("ActionTree", pDict);
	appointHandler(pEventTree, pActionTree);
	
	
	// load textures
	//     WARNING: For simplify reason, I hope you should never use it!
	CCArray * pTextures = CNDictionary::arrayForKey("Textures", pDict);
	setTextures(SFScene::loadTextures(pTextures));
	
	// add sub layers
	//     WARNING: For simplify reason, I hope you should never use it!
	CCArray * pLayers = CNDictionary::arrayForKey("Layers", pDict);
	addLayers(pLayers);
	
	// add sub sprites
	CCArray * pSprites = CNDictionary::arrayForKey("Sprites", pDict);
	addSprites(pSprites);

	return true;
}

CCArray * SFSprite::getTextures()
{
	return m_pTextures;
}

void SFSprite::setTextures(CCArray * pTextures)
{
	if (m_pTextures != pTextures)
	{
		CNLog("cleaning textures");
		SFScene::cleanTextures(m_pTextures);
		
		CC_SAFE_RETAIN(pTextures);
		CC_SAFE_RELEASE(m_pTextures);
		m_pTextures = pTextures;
	}
}

#pragma mark -

void SFSprite::appointHandler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFEventDelegate * pHander = SFEventHandler::handler(pEventTree, pActionTree);
	setEventDelegate(pHander);
}

void SFSprite::onEnter()
{
	CNSprite::onEnter();
	
	if (m_pEventDelegate)
	{
		m_pEventDelegate->doEvent("onEnter", this);
	}
}

void SFSprite::onEnterTransitionDidFinish()
{
	CNSprite::onEnterTransitionDidFinish();
	
	if (m_pEventDelegate)
	{
		m_pEventDelegate->doEvent("onEnterTransitionDidFinish", this);
	}
}

void SFSprite::onExitTransitionDidStart()
{
	if (m_pEventDelegate)
	{
		m_pEventDelegate->doEvent("onExitTransitionDidStart", this);
	}
	
	CNSprite::onExitTransitionDidStart();
}

void SFSprite::onExit()
{
	if (m_pEventDelegate)
	{
		m_pEventDelegate->doEvent("onExit", this);
	}
	
	SFEventHandler * pHandler = dynamic_cast<SFEventHandler *>(m_pEventDelegate);
	if (pHandler)
	{
		pHandler->restore(); // for restore 'Target' from CCNode to CCString
	}
	
	CNSprite::onExit();
}

NS_SF_END
