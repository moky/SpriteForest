//
//  CNTouchDelegate.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-23.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNTouchDelegate_h
#define Coconut2D_X_CNTouchDelegate_h

#include "../cnMacros.h"

NS_CN_BEGIN

class CN_DLL CNTouchDelegate
{
public:
	// button
	virtual void onFingerDown(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerUp(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerOver(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerOut(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerMove(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	
	virtual void onClick(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onDoubleClick(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	
	// guesture
	virtual void onSwipeLeft(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeRight(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeUp(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeDown(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	
	// drag
	virtual bool onDragStart(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
	virtual bool onDrag(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
	virtual bool onDragEnd(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
};

#pragma mark Button Delegate

/**
 *  convert cocos2d touch events to mouse-kind (finger) events
 */
class CN_DLL CNButtonDelegate : public CNTouchDelegate
{
public:
	virtual void onFingerDown(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerUp(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerOver(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerOut(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onFingerMove(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	
	virtual void onClick(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onDoubleClick(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);} // 慎用
};

#pragma mark Guesture Delegate

class CN_DLL CNGuestureDelegate : public CNTouchDelegate
{
public:
	virtual void onSwipeLeft(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeRight(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeUp(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
	virtual void onSwipeDown(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode);}
};

#pragma mark Drag Delegate

class CN_DLL CNDragDelegate : public CNTouchDelegate
{
public:
	// 如果当前条件下不允许拖放，则返回 NO；默认返回 YES
	virtual bool onDragStart(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
	// 如果到达了边界需要禁止移动，则返回 NO；默认返回 YES
	virtual bool onDrag(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
	// 如果松手后需要复原位置，则返回 NO；默认返回 YES
	virtual bool onDragEnd(cocos2d::CCNode * pNode) {CC_UNUSED_PARAM(pNode); return true;}
};

NS_CN_END

#endif
