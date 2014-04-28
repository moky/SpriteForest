//
//  SFTouchSprite.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-27.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFTouchSprite_h
#define SpriteForest_X_SFTouchSprite_h

#include "../base/SFSprite.h"
#include "../base/SFEventHandler.h"

NS_SF_BEGIN

#pragma mark SFTouchSprite

class SF_DLL SFTouchSprite : public SFSprite
{
	CC_SYNTHESIZE_RETAIN(coconut2d::CNTouchController *, m_pController, Controller);
	CC_SYNTHESIZE(bool, m_bIrregular, Irregular);
	CC_SYNTHESIZE(cocos2d::CCRect, m_tTouchBounds, TouchBounds);
	
public:
	SFTouchSprite(void);
	virtual ~SFTouchSprite(void);
	virtual bool init(void);
	
	virtual void appointHandler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	
	virtual void onEnter();
	virtual void onExit();
	
	// CNNode extensions
	virtual bool containsNodeSpacePoint(const cocos2d::CCPoint & tPoint);
	bool containsTouchLocation(cocos2d::CCTouch * pTouch);
	virtual bool setAttributes(cocos2d::CCDictionary * pDict);
	// CNSprite factories
	CNSPRITE_FACTORIES(SFTouchSprite);
};

#pragma mark - SFTouchHandler

class SF_DLL SFTouchHandler : public SFEventHandler, public coconut2d::CNTouchDelegate
{
public:
	static SFTouchHandler * handler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	// CNTouchDelegate
	// button
	virtual void onFingerDown(cocos2d::CCNode * pNode);
	virtual void onFingerUp(cocos2d::CCNode * pNode);
	virtual void onFingerOver(cocos2d::CCNode * pNode);
	virtual void onFingerOut(cocos2d::CCNode * pNode);
	virtual void onFingerMove(cocos2d::CCNode * pNode);
	virtual void onClick(cocos2d::CCNode * pNode);
	virtual void onDoubleClick(cocos2d::CCNode * pNode);
	// guesture
	virtual void onSwipeLeft(cocos2d::CCNode * pNode);
	virtual void onSwipeRight(cocos2d::CCNode * pNode);
	virtual void onSwipeUp(cocos2d::CCNode * pNode);
	virtual void onSwipeDown(cocos2d::CCNode * pNode);
};

#pragma mark Run-Time Type Identification

SF_RUNTIME_SPRITE(SFTouchSprite);

NS_SF_END

#endif
