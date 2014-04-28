//
//  SFAudio.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-5.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFAudio_h
#define SpriteForest_X_SFAudio_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFAudio : public cocos2d::CCObject
{
public:
	static bool perform(cocos2d::CCDictionary * pDict);
	static void stopAll(void);
};

NS_SF_END

#endif
