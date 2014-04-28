//
//  CNScrollLayerController.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNScrollLayerController.h"

#include "CNNode.h"

NS_CN_BEGIN

USING_NS_CC;

CNScrollLayerController::CNScrollLayerController(void)
: CNTouchController()
, m_pCurrentAction(NULL)
, m_tSwingBeganPoint(CCPointZero)
, m_fSwingBeganTime(0)
{
	
}

CNScrollLayerController::~CNScrollLayerController(void)
{
	setCurrentAction(NULL);
}

bool CNScrollLayerController::init(void)
{
	setCurrentAction(NULL);
	setSwingBeganPoint(CCPointZero);
	setSwingBeganTime(0.0);
	return true;
}

void CNScrollLayerController_handleSwingGesture(CNScrollLayerController * pController, CCTouch * pTouch)
{
	CCNode * pNode = pController->getNode();
	CCPoint tLocation = pNode->convertTouchToNodeSpace(pTouch);
	tLocation = pNode->convertToWorldSpace(tLocation);
	
	CCPoint tDeltaDistance = ccpSub(tLocation, pController->getSwingBeganPoint());
	tDeltaDistance = ccpMult(tDeltaDistance, 10);
	CCFloat len = ccpLength(tDeltaDistance);
	if (len < 1)
	{
		len = 1;
	}
	
	time_t now = time(NULL);
	long deltaTime = (now - pController->getSwingBeganTime()) / 1000;
	
	CCFloat v = deltaTime > 0 ? len / deltaTime : INFINITY;
	
	ccTime duration = v > 0 ? 1000 / v : INFINITY;
	if (duration > 10)
	{
		return;
	}
	else if (duration < 0.1)
	{
		duration = 0.1;
	}
	
	CCPoint newPosition = ccpAdd(pNode->getPosition(), tDeltaDistance);
	
	CCActionInterval * pAction = CCMoveTo::actionWithDuration(duration, newPosition);
	pAction = CCEaseExponentialOut::actionWithAction(pAction);
	pNode->runAction(pAction);
	
	pController->setCurrentAction(pAction);
}

bool CNScrollLayerController::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	CCPoint tLocation = m_pNode->convertTouchToNodeSpace(pTouch);
	m_tSwingBeganPoint = m_pNode->convertToWorldSpace(tLocation);
	m_fSwingBeganTime = time(NULL);
	
	if (m_pCurrentAction)
	{
		m_pCurrentAction->stop();
	}
	return CNTouchController::ccTouchBegan(pTouch, pEvent);
}

void CNScrollLayerController::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	CNTouchController::ccTouchEnded(pTouch, pEvent);
	
//	CNScrollLayerController_handleSwingGesture(this, pTouch);
}

NS_CN_END
