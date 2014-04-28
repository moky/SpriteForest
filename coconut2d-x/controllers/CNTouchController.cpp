//
//  CNTouchController.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNTouchController.h"

#include "../CNNode.h"
#include "../CNScene.h"

NS_CN_BEGIN

USING_NS_CC;

CNTouchController::CNTouchController(void)
: CCObject()
, m_pNode(NULL)
, m_pDelegate(NULL)
, m_tTouchBeganPoint(CCPointZero)
, m_tTouchPoint(CCPointZero)
, m_tTouchEndedPoint(CCPointZero)
, m_tStatus(TouchNodeNormal)
, m_bDragEnabled(false)
, m_tOriginalPosition(CCPointZero)
{
	
}

CNTouchController::~CNTouchController(void)
{
	setDelegate(NULL);
	setNode(NULL);
}

bool CNTouchController::init(void)
{
	setNode(NULL);
	setDelegate(NULL);
	
	setTouchBeganPoint(CCPointZero);
	setTouchPoint(CCPointZero);
	setTouchEndedPoint(CCPointZero);
	
	m_tStatus = TouchNodeNormal;
	
	setDragEnabled(false);
	m_tOriginalPosition = CCPointZero;
	
	return true;
}

CCNode * CNTouchController::getNode(void)
{
	return m_pNode;
}

void CNTouchController::setNode(CCNode * pNode)
{
    if (m_pNode != pNode)
    {
		if (m_pNode)
		{
			CCScene * pScene = CNNode::ancestorScene(m_pNode);
			if (CNScene * scene = dynamic_cast<CNScene *>(pScene))
			{
				scene->removeTouchNode(m_pNode);
			}
		}
        CC_SAFE_RETAIN(pNode);
        CC_SAFE_RELEASE(m_pNode);
        m_pNode = pNode;
		if (m_pNode)
		{
			CCScene * pScene = CNNode::ancestorScene(m_pNode);
			if (CNScene * scene = dynamic_cast<CNScene *>(pScene))
			{
				int iMaxTouches = m_bDragEnabled ? 1 : -1;
				scene->addTouchNode(m_pNode, this, iMaxTouches);
			}
		}
    }
}

bool CNTouchController::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	if (!CNNode::containsTouchLocation(m_pNode, pTouch))
	{
		return false;
	}
	
	// touch points
	CCPoint tPoint = m_pNode->convertTouchToNodeSpace(pTouch);
	setTouchBeganPoint(tPoint);
	setTouchPoint(tPoint);
	setTouchEndedPoint(tPoint);
	
	if (m_bDragEnabled)
	{
		tPoint = m_pNode->convertToWorldSpace(tPoint);
		setTouchBeganPoint(tPoint);
		setTouchPoint(tPoint);
		setTouchEndedPoint(tPoint);
		
		m_tOriginalPosition = m_pNode->getPosition();
		return m_pDelegate ? m_pDelegate->onDragStart(m_pNode) : true;
	}
	
	// button delegate
	m_tStatus = TouchNodeActivie;
	if (m_pDelegate) m_pDelegate->onFingerDown(m_pNode);
	if (m_pDelegate) m_pDelegate->onFingerOver(m_pNode);
	return true;
}

void CNTouchController::ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	// touch points
	CCPoint tPoint = m_pNode->convertTouchToNodeSpace(pTouch);
	setTouchPoint(tPoint);
	
	if (m_bDragEnabled)
	{
		tPoint = m_pNode->convertToWorldSpace(tPoint);
		setTouchPoint(tPoint);
		
		CCPoint tDelta = ccpSub(tPoint, m_tTouchBeganPoint);
		
		CCNode * pParent = m_pNode->getParent();
		if (!pParent)
		{
			CNLog("could not happen!");
			return;
		}
		
		CCPoint tOldPosition = m_pNode->getPosition();
		CCPoint tNewPosition = pParent->convertToWorldSpace(m_tOriginalPosition);
		tNewPosition = ccpAdd(tNewPosition, tDelta);
		tNewPosition = pParent->convertToNodeSpace(tNewPosition);
		// try to move to new position
		m_pNode->setPosition(tNewPosition);
		if (m_pDelegate && !m_pDelegate->onDrag(m_pNode))
		{
			m_pNode->setPosition(tOldPosition);
		}
		return;
	}
	
	// button delegate
	if (CNNode::containsTouchLocation(m_pNode, pTouch))
	{
		if (m_tStatus == TouchNodeNormal)
		{
			m_tStatus = TouchNodeActivie;
			if (m_pDelegate) m_pDelegate->onFingerOver(m_pNode);
		}
		else
		{
			if (m_pDelegate) m_pDelegate->onFingerMove(m_pNode);
		}
	}
	else
	{
		if (m_tStatus == TouchNodeActivie)
		{
			m_tStatus = TouchNodeNormal;
			if (m_pDelegate) m_pDelegate->onFingerOut(m_pNode);
		}
	}
}

void CNTouchController::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	// touch points
	CCPoint tPoint = m_pNode->convertTouchToNodeSpace(pTouch);
	setTouchPoint(tPoint);
	setTouchEndedPoint(tPoint);
	
	if (m_bDragEnabled)
	{
		tPoint = m_pNode->convertToWorldSpace(tPoint);
		setTouchPoint(tPoint);
		setTouchEndedPoint(tPoint);
		
		if (m_pDelegate && !m_pDelegate->onDragEnd(m_pNode))
		{
			CCActionInterval * moveTo = CCMoveTo::actionWithDuration(0.2f, m_tOriginalPosition);
			moveTo = CCEaseInOut::actionWithAction(moveTo, 2.0f);
			m_pNode->runAction(moveTo);
		}
		return;
	}
	
	// button delegate
	m_tStatus = TouchNodeNormal;
	if (CNNode::containsTouchLocation(m_pNode, pTouch))
	{
		if (m_pDelegate) m_pDelegate->onFingerUp(m_pNode);
	}
	if (m_pDelegate) m_pDelegate->onFingerOut(m_pNode);
	
	// guesture delegate
	CCPoint d = ccpSub(m_tTouchEndedPoint, m_tTouchBeganPoint);
	CCFloat quantum = 100.0f;
	if (d.x > - quantum && d.x < quantum)
	{
		if (d.y > quantum)
		{
			if (m_pDelegate) m_pDelegate->onSwipeUp(m_pNode);
			return;
		}
		else if (d.y < - quantum)
		{
			if (m_pDelegate) m_pDelegate->onSwipeDown(m_pNode);
			return;
		}
	}
	else if (d.y > - quantum && d.y < quantum)
	{
		if (d.x > quantum)
		{
			if (m_pDelegate) m_pDelegate->onSwipeRight(m_pNode);
			return;
		}
		else if (d.x < - quantum)
		{
			if (m_pDelegate) m_pDelegate->onSwipeLeft(m_pNode);
			return;
		}
	}
	
	// click delegate
	if (CNNode::containsTouchLocation(m_pNode, pTouch))
	{
		if (m_pDelegate) m_pDelegate->onClick(m_pNode);
	}
}

void CNTouchController::ccTouchCancelled(CCTouch * pTouch, CCEvent * pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

NS_CN_END
