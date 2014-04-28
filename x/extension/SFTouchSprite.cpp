//
//  SFTouchSprite.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-27.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFTouchSprite.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#pragma mark SFTouchSprite

SFTouchSprite::SFTouchSprite(void)
: SFSprite()
, m_pController(NULL)
, m_bIrregular(false)
, m_tTouchBounds(CCRectZero)
{
}

SFTouchSprite::~SFTouchSprite(void)
{
	setController(NULL);
}

bool SFTouchSprite::init(void)
{
	if (!SFSprite::init())
	{
		CNLog("error");
		return false;
	}
	
	if (!m_pController) // no need to create the touch controller again
	{
		CNTouchController * pController = new CNTouchController();
		if (pController && pController->init())
		{
			setController(pController);
			CC_SAFE_RELEASE(pController);
		}
		else
		{
			CNLog("could not happen!");
			CC_SAFE_RELEASE(pController);
			return false;
		}
	}
	
	setIrregular(false);
	setTouchBounds(CCRectZero);
	
	return true;
}

void SFTouchSprite::appointHandler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFTouchHandler * pHandler = SFTouchHandler::handler(pEventTree, pActionTree);
	setEventDelegate(pHandler);
}

void SFTouchSprite::onEnter()
{
	SFSprite::onEnter();
	
	if (m_pController)
	{
		m_pController->setNode(this);
		m_pController->setDelegate(dynamic_cast<CNTouchDelegate *>(m_pEventDelegate));
	}
}

void SFTouchSprite::onExit()
{
	if (m_pController)
	{
		m_pController->setDelegate(NULL);
		m_pController->setNode(NULL);
	}
	
	SFSprite::onExit();
}

bool SFTouchSprite::containsNodeSpacePoint(const CCPoint & tPoint)
{
	if (!CCRect::CCRectEqualToRect(m_tTouchBounds, CCRectZero) &&
		!CCRect::CCRectContainsPoint(m_tTouchBounds, tPoint))
	{
		return false;
	}
	return SFSprite::containsNodeSpacePoint(tPoint);
}

bool SFTouchSprite::containsTouchLocation(CCTouch * pTouch)
{
	return CNSprite::containsTouchLocation(pTouch, m_bIrregular);
}

bool SFTouchSprite::setAttributes(CCDictionary * pDict)
{
	if (!SFSprite::setAttributes(pDict))
	{
		CNLog("error");
		return false;
	}
	
	// Irregular
	CCString * pIrregular = (CCString *)pDict->objectForKey("Irregular");
	m_bIrregular = pIrregular ? pIrregular->boolValue() : false;
	
	// TouchBounds
	CCString * pTouchBounds = (CCString *)pDict->objectForKey("TouchBounds");
	m_tTouchBounds = pTouchBounds ? CCRectFromString(pTouchBounds->getCString()) : CCRectZero;
	
	return true;
}

#pragma mark - SFTouchHandler

SFTouchHandler * SFTouchHandler::handler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFTouchHandler * pHandler = new SFTouchHandler();
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

void SFTouchHandler::onFingerDown(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onFingerDown", pNode);
	doEvent("onMouseDown", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onFingerUp(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onFingerUp", pNode);
	doEvent("onMouseUp", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onFingerOver(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onFingerOver", pNode);
	doEvent("onMouseOver", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onFingerOut(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onFingerOut", pNode);
	doEvent("onMouseOut", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onFingerMove(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onFingerMove", pNode);
	doEvent("onMouseMove", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

// click
void SFTouchHandler::onClick(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onClick", pNode);
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onDoubleClick(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onDoubleClick", pNode); // deprecated
	CCPoolManager::sharedPoolManager()->pop();
}

// guestures
void SFTouchHandler::onSwipeLeft(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onSwipeLeft", pNode);
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onSwipeRight(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onSwipeRight", pNode);
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onSwipeUp(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onSwipeUp", pNode);
	CCPoolManager::sharedPoolManager()->pop();
}

void SFTouchHandler::onSwipeDown(CCNode * pNode)
{
	CCPoolManager::sharedPoolManager()->push();
	doEvent("onSwipeDown", pNode);
	CCPoolManager::sharedPoolManager()->pop();
}

NS_SF_END
