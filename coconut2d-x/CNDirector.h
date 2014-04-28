//
//  CNDirector.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-20.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNDirector_h
#define Coconut2D_X_CNDirector_h

#include "cnMacros.h"

NS_CN_BEGIN

class CN_DLL CNDirector : public cocos2d::CCObject
{
	CC_SYNTHESIZE(cocos2d::CCSize, m_tWinSize, WinSize);
	
public:
    CNDirector(void);
    virtual ~CNDirector(void);
	virtual bool init(void);
	
	static CNDirector * sharedDirector(void);
};

NS_CN_END

#endif // Coconut2D_X_CNDirector_h
