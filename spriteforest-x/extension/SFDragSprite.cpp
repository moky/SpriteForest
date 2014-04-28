//
//  SFDragSprite.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-8.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFDragSprite.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFDragSprite::SFDragSprite(void)
: SFTouchSprite()
, m_tDragRange(CCRectZero)
, m_bDragTied(false)
{
	
}

SFDragSprite::~SFDragSprite(void)
{
	
}

bool SFDragSprite::init(void)
{
	if (!SFTouchSprite::init())
	{
		CNLog("error");
		return false;
	}
	
	CNTouchController * pController = getController();
	if (pController)
	{
		pController->setDragEnabled(true);
	}
	
	m_tDragRange = CCRectZero;
	m_bDragTied = false;
	
	return true;
}

bool SFDragSprite::setAttributes(CCDictionary * pDict)
{
	if (!SFTouchSprite::setAttributes(pDict))
	{
		CNLog("error");
		return false;
	}
	
	// DragRange
	CCString * pDragRange = (CCString *)pDict->objectForKey("DragRange");
	m_tDragRange = pDragRange ? CCRectFromString(pDragRange->getCString()) : CCRectZero;
	
	// DragTied
	CCString * pDragTied = (CCString *)pDict->objectForKey("DragTied");
	m_bDragTied = pDragTied ? pDragTied->boolValue() : false;
	
	return true;
}

void SFDragSprite::appointHandler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFDragHandler * pHandler = SFDragHandler::handler(pEventTree, pActionTree);
	setEventDelegate(pHandler);
}

#pragma mark - SFDragHandler

SFDragHandler * SFDragHandler::handler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFDragHandler * pHandler = new SFDragHandler();
	if (pHandler && pHandler->init(pEventTree, pActionTree))
	{
		pHandler->autorelease();
		return pHandler;
	}
	else
	{
		CC_SAFE_RELEASE(pHandler);
		return NULL;
	}
}

bool SFDragHandler::onDragStart(CCNode * pNode)
{
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	pm->push();
	doEvent("onDragStart", pNode);
	pm->pop();
	return true;
}

bool SFDragHandler::onDrag(CCNode * pNode)
{
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	pm->push();
	doEvent("onDrag", pNode);
	pm->pop();
	
	// check range
	SFDragSpriteProtocol * pDragSprite = dynamic_cast<SFDragSpriteProtocol *>(pNode);
	if (pDragSprite)
	{
		CCRect range = pDragSprite->getDragRange();
		if (!CCRect::CCRectEqualToRect(range, CCRectZero))
		{
			CCSize size = pNode->getContentSize();
			CCPoint anchor = pNode->getAnchorPointInPoints();
			CCPoint position = pNode->getPosition();
			CCPoint point = ccpSub(position, anchor);
			// x
			if (point.x < range.origin.x)
			{
				point.x = range.origin.x;
			}
			else if (point.x + size.width > range.origin.x + range.size.width)
			{
				point.x = range.origin.x + range.size.width - size.width;
			}
			// y
			if (point.y < range.origin.y)
			{
				point.y = range.origin.y;
			}
			else if (point.y + size.height > range.origin.y + range.size.height)
			{
				point.y = range.origin.y + range.size.height - size.height;
			}
			// limit position
			point = ccpAdd(point, anchor);
			if (!CCPoint::CCPointEqualToPoint(point, position))
			{
				pNode->setPosition(point);
			}
		}
	}
	
	return true;
}

bool SFDragHandler::onDragEnd(CCNode * pNode)
{
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	pm->push();
	doEvent("onDragEnd", pNode);
	pm->pop();
	
	SFDragSpriteProtocol * pDragSprite = dynamic_cast<SFDragSpriteProtocol *>(pNode);
	if (pDragSprite)
	{
		return !pDragSprite->getDragTied();
	}
	
	return true;
}

NS_SF_END
