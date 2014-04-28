//
//  CNSpriteFrameDataTransformer.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNSpriteFrameDataTransformer_h
#define Coconut2D_X_CNSpriteFrameDataTransformer_h


#include "CNSpriteFrameData.h"

NS_CN_BEGIN

class CNSpriteFrameDataTransformer : public CNSpriteFrameData
{
public:
	virtual bool init(const std::string & sPath);
	virtual bool init(cocos2d::CCDictionary * pDict);
};

NS_CN_END

#endif
