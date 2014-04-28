//
//  SFActionInterval.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFActionInterval.h"

#include "SFAnimation.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#pragma mark SFActionInterval

CCAction * SFActionInterval::ccAction(void)
{
	CNLog("override me!");
	return NULL;
}

#pragma mark SFSequence

SFSequence::SFSequence(void)
: SFActionInterval()
, m_pActions(NULL)
{
	
}

SFSequence::~SFSequence(void)
{
	setActions(NULL);
}

bool SFSequence::init(void)
{
	setActions(NULL);
	return true;
}

bool SFSequence::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCArray * pActions = SFSequence::subActionsFromDictionary(pDict);
	if (!pActions)
	{
		CNLog("Error: no sub actions");
		return false;
	}
	
	CCArray * pArray = new CCArray();
	pArray->initWithCapacity(pActions->count());
	
	CCObject * pObj = NULL;
	CCARRAY_FOREACH_REVERSE(pActions, pObj)
	{
		if (!dynamic_cast<CCFiniteTimeAction *>(pObj))
		{
			pArray->addObject(pObj);
		}
	}
	
	pActions->removeObjectsInArray(pArray);
	pArray->release();
	
	if (pActions->count() == 0)
	{
		CNLog("error");
		return false;
	}
	
	setActions(pActions);
	return true;
}

CCAction * SFSequence::ccAction(void)
{
	if (!m_pActions || m_pActions->count() == 0)
	{
		CNLog("Error: no sub actions");
		return NULL;
	}
	return CCSequence::actionsWithArray(m_pActions);
}

#pragma mark SFRepeat

SFRepeat::SFRepeat(void)
: SFActionInterval()
, m_pAction(NULL)
, m_iTimes(0)
{
	
}

SFRepeat::~SFRepeat(void)
{
	setAction(NULL);
}

bool SFRepeat::init(void)
{
	setAction(NULL);
	setTimes(0);
	return true;
}

bool SFRepeat::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCAction * pAction = SFRepeat::subActionFromDictionary(pDict);
	setAction(dynamic_cast<CCFiniteTimeAction *>(pAction));
	
	CCString * pTimes = (CCString *)pDict->objectForKey("Times");
	m_iTimes = pTimes ? pTimes->intValue() : 0;
	
	return true;
}

CCAction * SFRepeat::ccAction(void)
{
	if (!m_pAction || m_iTimes == 0)
	{
		CNLog("error");
		return NULL;
	}
	return CCRepeat::actionWithAction(m_pAction, m_iTimes);
}

#pragma mark SFSpawn

SFSpawn::SFSpawn(void)
: SFActionInterval()
, m_pActions(NULL)
{
	
}

SFSpawn::~SFSpawn(void)
{
	setActions(NULL);
}

bool SFSpawn::init(void)
{
	setActions(NULL);
	return true;
}

bool SFSpawn::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCArray * pActions = SFSpawn::subActionsFromDictionary(pDict);
	if (!pActions)
	{
		CNLog("Error: no sub actions");
		return false;
	}
	
	CCArray * pArray = new CCArray();
	pArray->initWithCapacity(pActions->count());
	
	CCObject * pObj = NULL;
	CCARRAY_FOREACH_REVERSE(pActions, pObj)
	{
		if (!dynamic_cast<CCFiniteTimeAction *>(pObj))
		{
			pArray->addObject(pObj);
		}
	}
	
	pActions->removeObjectsInArray(pArray);
	pArray->release();
	
	if (pActions->count() == 0)
	{
		CNLog("error");
		return false;
	}
	
	setActions(pActions);
	return true;
}

CCAction * SFSpawn::ccAction(void)
{
	if (!m_pActions || m_pActions->count() == 0)
	{
		CNLog("Error: no sub actions");
		return NULL;
	}
	return CCSpawn::actionsWithArray(m_pActions);
}

#pragma mark SFRotateTo

bool SFRotateTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pAngle = (CCString *)pDict->objectForKey("Angle");
	if (!pAngle)
	{
		pAngle = (CCString *)pDict->objectForKey("Rotation");
	}
	m_fAngle = pAngle ? pAngle->floatValue() : 0.0f;
	
	return true;
}

CCAction * SFRotateTo::ccAction(void)
{
	return CCRotateTo::actionWithDuration(m_fDuration, m_fAngle);
}

#pragma mark SFRotateBy

CCAction * SFRotateBy::ccAction(void)
{
	return CCRotateBy::actionWithDuration(m_fDuration, m_fAngle);
}

#pragma mark SFMoveTo

bool SFMoveTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	m_tPosition = pPosition ? CCPointFromString(pPosition->getCString()) : CCPointZero;
	
	return true;
}

CCAction * SFMoveTo::ccAction(void)
{
	return CCMoveTo::actionWithDuration(m_fDuration, m_tPosition);
}

#pragma mark SFMoveBy

CCAction * SFMoveBy::ccAction(void)
{
	return CCMoveBy::actionWithDuration(m_fDuration, m_tPosition);
}

#pragma mark SFSkewTo

bool SFSkewTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pSkewX = (CCString *)pDict->objectForKey("SkewX");
	m_fSkewX = pSkewX ? pSkewX->floatValue() : 0.0f;
	
	CCString * pSkewY = (CCString *)pDict->objectForKey("SkewY");
	m_fSkewY = pSkewY ? pSkewY->floatValue() : 0.0f;
	
	return true;
}

CCAction * SFSkewTo::ccAction(void)
{
	return CCSkewTo::actionWithDuration(m_fDuration, m_fSkewX, m_fSkewY);
}

#pragma mark SFSkewBy

CCAction * SFSkewBy::ccAction(void)
{
	return CCSkewBy::actionWithDuration(m_fDuration, m_fSkewX, m_fSkewY);
}

#pragma mark SFJumpTo

bool SFJumpTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	m_tPosition = pPosition ? CCPointFromString(pPosition->getCString()) : CCPointZero;
	
	CCString * pHeight = (CCString *)pDict->objectForKey("Height");
	m_fHeight = pHeight ? pHeight->floatValue() : 0.0f;
	
	CCString * pJumps = (CCString *)pDict->objectForKey("Jumps");
	m_iJumps = pJumps ? pJumps->intValue() : 0;
	
	return true;
}

CCAction * SFJumpTo::ccAction(void)
{
	return CCJumpTo::actionWithDuration(m_fDuration, m_tPosition, m_fHeight, m_iJumps);
}

#pragma mark SFJumpBy

CCAction * SFJumpBy::ccAction(void)
{
	return CCJumpBy::actionWithDuration(m_fDuration, m_tPosition, m_fHeight, m_iJumps);
}

#pragma mark SFBezierTo

bool SFBezierTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pEndPosition = (CCString *)pDict->objectForKey("EndPosition");
	m_tBezierConfig.endPosition = pEndPosition ? CCPointFromString(pEndPosition->getCString()) : CCPointZero;
	
	CCString * pControlPoint1 = (CCString *)pDict->objectForKey("ControlPoint1");
	m_tBezierConfig.controlPoint_1 = pControlPoint1 ? CCPointFromString(pControlPoint1->getCString()) : CCPointZero;
	
	CCString * pControlPoint2 = (CCString *)pDict->objectForKey("ControlPoint2");
	m_tBezierConfig.controlPoint_2 = pControlPoint2 ? CCPointFromString(pControlPoint2->getCString()) : CCPointZero;
	
	
	return true;
}

CCAction * SFBezierTo::ccAction(void)
{
	return CCBezierTo::actionWithDuration(m_fDuration, m_tBezierConfig);
}

#pragma mark SFBezierBy

CCAction * SFBezierBy::ccAction(void)
{
	return CCBezierBy::actionWithDuration(m_fDuration, m_tBezierConfig);
}

#pragma mark SFScaleTo

bool SFScaleTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pScale = (CCString *)pDict->objectForKey("Scale");
	if (pScale)
	{
		m_fScaleX = m_fScaleY = pScale->floatValue();
		return true;
	}
	
	CCString * pScaleX = (CCString *)pDict->objectForKey("ScaleX");
	m_fScaleX = pScaleX ? pScaleX->floatValue() : 1.0f;
	
	CCString * pScaleY = (CCString *)pDict->objectForKey("ScaleY");
	m_fScaleY = pScaleY ? pScaleY->floatValue() : 1.0f;
	
	return true;
}

CCAction * SFScaleTo::ccAction(void)
{
	return CCScaleTo::actionWithDuration(m_fDuration, m_fScaleX, m_fScaleY);
}

#pragma mark SFScaleBy

CCAction * SFScaleBy::ccAction(void)
{
	return CCScaleBy::actionWithDuration(m_fDuration, m_fScaleX, m_fScaleY);
}

#pragma mark SFBlink

bool SFBlink::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pTimes = (CCString *)pDict->objectForKey("Times");
	m_iTimes = pTimes ? pTimes->intValue() : 0;
	
	return true;
}

CCAction * SFBlink::ccAction(void)
{
	return CCBlink::actionWithDuration(m_fDuration, m_iTimes);
}

#pragma mark SFFadeIn

CCAction * SFFadeIn::ccAction(void)
{
	return CCFadeIn::actionWithDuration(m_fDuration);
}

#pragma mark SFFadeOut

CCAction * SFFadeOut::ccAction(void)
{
	return CCFadeOut::actionWithDuration(m_fDuration);
}

#pragma mark SFFadeTo

bool SFFadeTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pOpacity = (CCString *)pDict->objectForKey("Opacity");
	m_iOpacity = pOpacity ? pOpacity->intValue() : 0;
	
	return true;
}

CCAction * SFFadeTo::ccAction(void)
{
	return CCFadeTo::actionWithDuration(m_fDuration, m_iOpacity);
}

#pragma mark SFTintTo

bool SFTintTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pRed = (CCString *)pDict->objectForKey("Red");
	m_iRed = pRed ? pRed->intValue() : 0;
	
	CCString * pGreen = (CCString *)pDict->objectForKey("Green");
	m_iGreen = pGreen ? pGreen->intValue() : 0;
	
	CCString * pBlue = (CCString *)pDict->objectForKey("Blue");
	m_iBlue = pBlue ? pBlue->intValue() : 0;
	
	return true;
}

CCAction * SFTintTo::ccAction(void)
{
	return CCTintTo::actionWithDuration(m_fDuration, m_iRed, m_iGreen, m_iBlue);
}

#pragma mark SFTintBy

CCAction * SFTintBy::ccAction(void)
{
	return CCTintBy::actionWithDuration(m_fDuration, m_iRed, m_iGreen, m_iBlue);
}

#pragma mark SFDelayTime

CCAction * SFDelayTime::ccAction(void)
{
	return CCDelayTime::actionWithDuration(m_fDuration);
}

#pragma mark SFReverseTime

SFReverseTime::SFReverseTime(void)
: SFActionInterval()
, m_pAction(NULL)
{
	
}

SFReverseTime::~SFReverseTime(void)
{
	setAction(NULL);
}

bool SFReverseTime::init(void)
{
	setAction(NULL);
	return true;
}

bool SFReverseTime::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCAction * pAction = SFRepeat::subActionFromDictionary(pDict);
	setAction(dynamic_cast<CCFiniteTimeAction *>(pAction));
	
	return true;
}

CCAction * SFReverseTime::ccAction(void)
{
	if (!m_pAction)
	{
		CNLog("error");
		return NULL;
	}
	return CCReverseTime::actionWithAction(m_pAction);
}

#pragma mark SFMaskTo

bool SFMaskTo::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pRect = (CCString *)pDict->objectForKey("Rect");
	m_tRect = pRect ? CCRectFromString(pRect->getCString()) : CCRectZero;
	
	return true;
}

CCAction * SFMaskTo::ccAction(void)
{
	return CCMaskTo::actionWithDuration(m_fDuration, m_tRect);
}

#pragma mark SFMaskBy

CCAction * SFMaskBy::ccAction(void)
{
	return CCMaskBy::actionWithDuration(m_fDuration, m_tRect);
}

#pragma mark SFAnimate

SFAnimate::SFAnimate(void)
: SFActionInterval()
, m_pFrames(NULL)
, m_fDelay(0)
, m_bRestoreOriginalFrame(false)
{
	
}

SFAnimate::~SFAnimate(void)
{
	setFrames(NULL);
}

bool SFAnimate::init(void)
{
	setFrames(NULL);
	setDelay(0);
	setRestoreOriginalFrame(false);
	return true;
}

bool SFAnimate::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCArray * pFrames = CNDictionary::arrayForKey("Frames", pDict);
	setFrames(pFrames);
	
	CCString * pDelay = (CCString *)pDict->objectForKey("Delay");
	m_fDelay = pDelay ? pDelay->floatValue() : 0;
	
	CCString * pLoops = (CCString *)pDict->objectForKey("Loops");
	m_iLoops = pLoops ? pLoops->intValue() : 1;
	
	CCString * pRestoreOriginalFrame = (CCString *)pDict->objectForKey("RestoreOriginalFrame");
	m_bRestoreOriginalFrame = pRestoreOriginalFrame ? pRestoreOriginalFrame->boolValue() : false;
	
	return true;
}

CCAction * SFAnimate::ccAction(void)
{
	if (!m_pFrames || m_pFrames->count() == 0)
	{
		CNLog("Error: no frames");
		return NULL;
	}
	
	CCFloat fDelayTime = m_fDuration ? m_fDuration / m_pFrames->count() : m_fDelay;
	CCAnimation * pAnimcation = SFAnimation::animation(m_pFrames, fDelayTime);
	if (!pAnimcation)
	{
		CNLog("failed to create animation");
		return NULL;
	}
	pAnimcation->setLoops(m_iLoops);
	pAnimcation->setRestoreOriginalFrame(m_bRestoreOriginalFrame);
	return CCAnimate::actionWithAnimation(pAnimcation);
}

NS_SF_END
