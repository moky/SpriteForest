//
//  CCMask.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CCMask.h"

NS_CC_BEGIN

#pragma mark CCMaskTo

CCMaskTo * CCMaskTo::actionWithDuration(ccTime tDuration, const CCRect & tRect)
{
	CCMaskTo * pAction = new CCMaskTo();
	if (pAction && pAction->initWithDuration(tDuration, tRect))
	{
		pAction->autorelease();
		return pAction;
	}
	CC_SAFE_DELETE(pAction);
	return NULL;
}

bool CCMaskTo::initWithDuration(ccTime tDuration, const CCRect & tRect)
{
	if (!CCActionInterval::initWithDuration(tDuration))
	{
		return false;
	}
	m_tEndRect = CC_RECT_PIXELS_TO_POINTS(tRect);
	return true;
}

CCObject * CCMaskTo::copyWithZone(CCZone * pZone)
{
	CCZone * pNewZone = NULL;
	CCMaskTo * pCopy = NULL;
	if (pZone && pZone->m_pCopyObject)
	{
		// incase of being called at sub class
		pCopy = (CCMaskTo *)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCMaskTo();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCActionInterval::copyWithZone(pZone);
	
	pCopy->initWithDuration(m_fDuration, m_tEndRect);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCMaskTo::startWithTarget(CCNode * pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	
	CCSprite * pSprite = dynamic_cast<CCSprite *>(m_pTarget);
	if (!pSprite)
	{
		return;
	}
	m_tStartRect = pSprite->getTextureRect();
	
	CCPoint deltaXY = ccpSub(m_tEndRect.origin, m_tStartRect.origin);
	CCPoint deltaWH = ccpSub(ccpFromSize(m_tEndRect.size), ccpFromSize(m_tStartRect.size));
	
	m_tDelta = CCRectMake(deltaXY.x, deltaXY.y, deltaWH.x, deltaWH.y);
}

void CCMaskTo::update(ccTime tTime)
{
	CCSprite * pSprite = dynamic_cast<CCSprite *>(m_pTarget);
	if (!pSprite)
	{
		return;
	}
	
	CCRect tTextureRect = CCRectMake(m_tStartRect.origin.x + m_tDelta.origin.x * tTime,
									 m_tStartRect.origin.y + m_tDelta.origin.y * tTime,
									 m_tStartRect.size.width + m_tDelta.size.width * tTime,
									 m_tStartRect.size.height + m_tDelta.size.height * tTime);
	pSprite->setTextureRect(tTextureRect);
}

#pragma mark CCMaskBy

CCMaskBy * CCMaskBy::actionWithDuration(ccTime tDuration, const CCRect & tRect)
{
	CCMaskBy * pAction = new CCMaskBy();
	if (pAction && pAction->initWithDuration(tDuration, tRect))
	{
		pAction->autorelease();
		return pAction;
	}
	CC_SAFE_DELETE(pAction);
	return NULL;
}

void CCMaskBy::startWithTarget(CCNode * pTarget)
{
	CCMaskTo::startWithTarget(pTarget);
	
	m_tDelta = m_tEndRect;
	m_tDelta.size = CCSizeZero;
}

NS_CC_END
