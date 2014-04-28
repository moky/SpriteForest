//
//  SFParticleSystem.cpp
//  BevaTing-X
//
//  Created by Moky on 12-12-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFParticleSystem.h"

#include "../extension/SFTouchSprite.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFParticleSystem::SFParticleSystem(void)
: CCParticleSystemQuad()
, m_sPositionString("")
{
	
}

SFParticleSystem::~SFParticleSystem(void)
{
	
}

bool SFParticleSystem::init(void)
{
	if (!CCParticleSystemQuad::init())
	{
		return false;
	}
	m_sPositionString.clear();
	return true;
}

bool SFParticleSystem::initWithDictionary(CCDictionary * pDict)
{
	CCString * pFilename = (CCString *)pDict->objectForKey("File");
	if (!pFilename || !CNFileManager::isExists(pFilename->getCString()))
	{
		CNLog("cannot get 'File' tag");
		return false;
	}
	
	if (!CCParticleSystemQuad::initWithFile(pFilename->getCString()))
	{
		return false;
	}
	
	// Position
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	m_sPositionString = pPosition ? pPosition->getCString() : "";
	
//	// ZOrder
//	CCString * pZOrder = (CCString *)pDict->objectForKey("ZOrder");
//	setZOrder(pZOrder ? pZOrder->intValue() : 0);
	
	// PositionType
	CCString * pPositionType = (CCString *)pDict->objectForKey("PositionType");
	if (!pPositionType)
	{
		// do nothing
	}
	else if (strcasecmp(pPositionType->getCString(), "Free") == 0)
	{
		setPositionType(kCCPositionTypeFree);
	}
	else if (strcasecmp(pPositionType->getCString(), "Relative") == 0)
	{
		setPositionType(kCCPositionTypeRelative);
	}
	else if (strcasecmp(pPositionType->getCString(), "Grouped") == 0)
	{
		setPositionType(kCCPositionTypeGrouped);
	}
	else
	{
		CNLog("unrecognized position type: %s", pPositionType->getCString());
	}
	
	// auto remove on finished ?
	
	return true;
}

SFParticleSystem * SFParticleSystem::particle(CCDictionary * pDict)
{
	SFParticleSystem * pSystem = new SFParticleSystem();
	if (pSystem && pSystem->initWithDictionary(pDict))
	{
		pSystem->autorelease();
		return pSystem;
	}
	CC_SAFE_DELETE(pSystem);
	return NULL;
}

void SFParticleSystem::run(CCNode * pNode)
{
	if (!pNode)
	{
		CNLog("could not happen");
		return;
	}
	// get position
	SFTouchSprite * pSprite = dynamic_cast<SFTouchSprite *>(pNode);
	if (pSprite)
	{
		CNTouchController * pController = pSprite->getController();
		if (!pController)
		{
			CNLog("could not happen");
		}
		else if (strcasecmp(m_sPositionString.c_str(), "TouchBeganPoint") == 0)
		{
			setPosition(pController->getTouchBeganPoint());
		}
		else if (strcasecmp(m_sPositionString.c_str(), "TouchPoint") == 0)
		{
			setPosition(pController->getTouchPoint());
		}
		else if (strcasecmp(m_sPositionString.c_str(), "TouchEndedPoint") == 0)
		{
			setPosition(pController->getTouchEndedPoint());
		}
		else
		{
			CNLog("error, position string: %s", m_sPositionString.c_str());
		}
	}
	
	// show
	pNode->addChild(this);
}

NS_SF_END
