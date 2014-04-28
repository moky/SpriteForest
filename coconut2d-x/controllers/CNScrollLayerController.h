//
//  CNScrollLayerController.h
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNScrollLayerController_h
#define Coconut2D_X_CNScrollLayerController_h

#include "CNTouchController.h"

NS_CN_BEGIN

class CNScrollLayerController : public CNTouchController
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, m_pCurrentAction, CurrentAction);
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCPoint, m_tSwingBeganPoint, SwingBeganPoint);
	CC_SYNTHESIZE(time_t, m_fSwingBeganTime, SwingBeganTime);
	
public:
	CNScrollLayerController(void);
	virtual ~CNScrollLayerController(void);
	virtual bool init(void);
	
	// CCTargetedTouchDelegate
	virtual bool ccTouchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent);
};

NS_CN_END

#endif
