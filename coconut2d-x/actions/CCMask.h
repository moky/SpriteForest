//
//  CCMask.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CCMask_h
#define Coconut2D_X_CCMask_h

#include "cocos2d.h"

NS_CC_BEGIN

#pragma mark CCMaskTo

class CC_DLL CCMaskTo : public CCActionInterval
{
public:
	static CCMaskTo * actionWithDuration(ccTime tDuration, const CCRect & tRect);
	
	virtual bool initWithDuration(ccTime tDuration, const CCRect & tRect);
	
	virtual CCObject * copyWithZone(CCZone * pZone);
	virtual void startWithTarget(CCNode * pTarget);
	virtual void update(ccTime tTime);
	
protected:
    CCRect m_tEndRect;
    CCRect m_tStartRect;
    CCRect m_tDelta;
};

#pragma mark CCMaskBy

class CC_DLL CCMaskBy : public CCMaskTo
{
public:
	static CCMaskBy * actionWithDuration(ccTime tDuration, const CCRect & tRect);
	
	virtual void startWithTarget(CCNode * pTarget);
};

NS_CC_END

#endif
