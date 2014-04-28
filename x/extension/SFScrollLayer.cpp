//
//  SFScrollLayer.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFScrollLayer.h"

#include "../base/SFScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFScrollLayer::SFScrollLayer(void)
: SFFiniteLayer()
, m_pScrollController(NULL)
{
	
}

SFScrollLayer::~SFScrollLayer(void)
{
	setScrollController(NULL);
}

bool SFScrollLayer::init(void)
{
	if (!SFFiniteLayer::init())
	{
		return false;
	}
	setScrollController(NULL);
	return true;
}

bool SFScrollLayer::initWithDictionary(CCDictionary * pDict)
{
	CCString * pFilename = (CCString *)pDict->objectForKey("File");
	if (pFilename)
	{
		CNSprite * pSprite = CNSprite::spriteWithFile(pFilename->getCString());
		if (SFFiniteLayer::initWithNode(pSprite))
		{
			setAttributes(pDict);
		}
		else
		{
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
	}
	else if (SFFiniteLayer::initWithDictionary(pDict))
	{
		CCString * pSize = (CCString *)pDict->objectForKey("Size");
		if (pSize)
		{
			setContentSize(CCSizeFromString(pSize->getCString()));
		}
		else
		{
			CCString * pWidth = (CCString *)pDict->objectForKey("Width");
			CCString * pHeight = (CCString *)pDict->objectForKey("Height");
			if (pWidth && pHeight)
			{
				setContentSize(CCSizeMake(pWidth->floatValue(), pHeight->floatValue()));
			}
		}
	}
	else
	{
		return false;
	}
	
	return true;
}

void SFScrollLayer::onEnter()
{
	SFFiniteLayer::onEnter();
	
	CNScrollLayerController * pController = new CNScrollLayerController();
	pController->init();
	pController->setNode(this);
	pController->setDragEnabled(true);
	setScrollController(pController);
	pController->release();
}

void SFScrollLayer::onExit()
{
	m_pScrollController->setNode(NULL);
	setScrollController(NULL);
	
	SFFiniteLayer::onExit();
}

NS_SF_END
