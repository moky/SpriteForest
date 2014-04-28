//
//  SFLayer.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFLayer.h"

#include "SFScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFLayer::SFLayer(void)
: CNLayer()
, m_pTextures(NULL)
{
	
}

SFLayer::~SFLayer(void)
{
	setTextures(NULL);
}

bool SFLayer::init(void)
{
	if (!CNLayer::init())
	{
		CNLog("error");
		return false;
	}
	setTextures(NULL);
	return true;
}

CCNode * SFLayer::nodeWithString(const char * pszString)
{
	if (!pszString || strlen(pszString) == 0)
	{
		pszString = "SFLayer";
	}
	return SFNode::nodeWithString(pszString);
}

CCNode * SFLayer::nodeWithDictionary(CCDictionary * pDict)
{
	CCString * pClassName = (CCString *)pDict->objectForKey("Class");
	while (!pClassName)
	{
		// extend scroll layer
		CCString * pScrollEnabled = (CCString *)pDict->objectForKey("ScrollEnabled");
		if (pScrollEnabled && pScrollEnabled->boolValue())
		{
			pDict->setObject(CCString::stringWithCString("SFScrollLayer"), "Class");
			break;
		}
		
		// extend scale layer
		CCString * pScaleEnabled = (CCString *)pDict->objectForKey("ScaleEnabled");
		if (pScaleEnabled && pScaleEnabled->boolValue())
		{
			pDict->setObject(CCString::stringWithCString("SFScaleLayer"), "Class");
			break;
		}
		
		pDict->setObject(CCString::stringWithCString("SFLayer"), "Class");
		break;
	}
	return SFNode::nodeWithDictionary(pDict);
}

bool SFLayer::initWithDictionary(CCDictionary * pDict)
{
	if (!CNLayer::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
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

CCArray * SFLayer::getTextures()
{
	return m_pTextures;
}

void SFLayer::setTextures(CCArray * pTextures)
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

NS_SF_END
