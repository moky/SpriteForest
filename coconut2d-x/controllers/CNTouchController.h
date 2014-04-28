//
//  CNTouchController.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNTouchController_h
#define Coconut2D_X_CNTouchController_h

#include "../cnMacros.h"
#include "CNTouchDelegate.h"

NS_CN_BEGIN

typedef enum {
	TouchNodeNormal,
	TouchNodeActivie,
} CNTouchStatus;

class CN_DLL CNTouchController : public cocos2d::CCObject, public cocos2d::CCTargetedTouchDelegate
{
	CC_PROPERTY(cocos2d::CCNode *, m_pNode, Node);
	CN_SYNTHESIZE_RETAIN(CNTouchDelegate *, m_pDelegate, Delegate);
	
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tTouchBeganPoint, TouchBeganPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tTouchPoint, TouchPoint);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tTouchEndedPoint, TouchEndedPoint);
	
	CNTouchStatus m_tStatus;
	
	CC_SYNTHESIZE(bool, m_bDragEnabled, DragEnabled);
	cocos2d::CCPoint m_tOriginalPosition; // save drag start position
	
public:
	CNTouchController(void);
	virtual ~CNTouchController(void);
	virtual bool init(void);
	
	// CCTargetedTouchDelegate
	virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
};

NS_CN_END

#endif
