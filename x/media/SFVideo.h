//
//  SFVideo.h
//  SpriteForest-X
//
//  Created by Moky on 13-7-24.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFVideo_h
#define SpriteForest_X_SFVideo_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFVideo : public cocos2d::CCObject
{
public:
	static bool perform(cocos2d::CCDictionary * pDict, cocos2d::CCNode * pTarget);
	static void stopAll(void);
};

NS_SF_END

#endif
