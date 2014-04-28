//
//  CNLayer.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNLayer.h"

#include "../CNDirector.h"
#include "../CNNode.h"
#include "../sprites/CNSprite.h"

NS_CN_BEGIN

USING_NS_CC;

CNLayer::~CNLayer()
{
	CNLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ dealloc");
}

bool CNLayer::init(void)
{
	if (!CCLayer::init())
	{
		CNLog("error");
		return false;
	}
	setAnchorPoint(CCPointZero);
	setIsRelativeAnchorPoint(true);
	setPosition(CCPointZero);
	return true;
}

bool CNLayer::initWithFile(const char * pszFilename)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	CCNode * pBackground = CNSprite::spriteWithFile(pszFilename);
	pBackground->setAnchorPoint(CCPointZero);
	pBackground->setPosition(CCPointZero);
	return initWithNode(pBackground);
}

bool CNLayer::initWithNode(CCNode * pNode)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	CCSize tSize = pNode->getContentSize();
	CCPoint tAnchor = pNode->getAnchorPointInPoints();
	CCPoint tOrigin = ccpSub(pNode->getPosition(), tAnchor);
	
	CCRect tFrame = CCRectZero;
	tFrame.size = tSize;
	tFrame.origin = tOrigin;
	if (!initWithFrame(tFrame))
	{
		CNLog("error");
		return false;
	}
	pNode->setAnchorPoint(CCPointZero);
	pNode->setPosition(CCPointZero);
	addChild(pNode);
	return true;
}

bool CNLayer::initWithFrame(const CCRect & tFrame)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	setContentSize(tFrame.size);
	setPosition(tFrame.origin);
	return true;
}

bool CNLayer::initWithDictionary(CCDictionary * pDict)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	return setAttributes(pDict);
}

void CNLayer::focus(const CCPoint & tPoint)
{
	CCSize tWinSize = CNDirector::sharedDirector()->getWinSize();
	CCPoint tCenter = ccpMult(ccpFromSize(tWinSize), 0.5f);
	CCPoint tAnchor = getAnchorPointInPoints();
	CCPoint tDistance = ccpSub(tAnchor, tPoint);
	CCPoint tNewPosition = ccpAdd(tCenter, tDistance);
	setPosition(tNewPosition);
}

CCPoint CNLayer::focus(void)
{
	CCSize tWinSize = CNDirector::sharedDirector()->getWinSize();
	CCPoint tCenter = ccpMult(ccpFromSize(tWinSize), 0.5f);
	return ccpSub(tCenter, getPosition());
}

NS_CN_END
