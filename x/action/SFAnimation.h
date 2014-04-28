//
//  SFAnimation.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-6.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFAnimation_h
#define SpriteForest_X_SFAnimation_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFAnimation : public cocos2d::CCObject
{
public:
	static cocos2d::CCAnimation * animation(cocos2d::CCArray * pFrames, const cocos2d::CCFloat fDelay);
};

NS_SF_END

#endif
