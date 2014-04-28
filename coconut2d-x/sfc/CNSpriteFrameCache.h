//
//  CNSpriteFrameCache.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNSpriteFrameCache_h
#define Coconut2D_X_CNSpriteFrameCache_h

#include "../cnMacros.h"

NS_CN_BEGIN

class CNSpriteFrameCache : public cocos2d::CCSpriteFrameCache
{
public:
	static cocos2d::CCTexture2D * loadTextureAndSprites(const std::string & sPath);
};

NS_CN_END

#endif
