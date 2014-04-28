//
//  CNArray.h
//  Coconut2D-X
//
//  Created by Moky on 13-7-13.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNArray_h
#define Coconut2D_X_CNArray_h

#include "../cnMacros.h"

NS_CN_BEGIN

class CNArray
{
public:
	static cocos2d::CCArray * randomArray(cocos2d::CCArray * pArray, const unsigned int iMaxCount);
	static inline cocos2d::CCArray * randomArray(cocos2d::CCArray * pArray) {
		return pArray ? randomArray(pArray, pArray->count()) : NULL;
	}
};

NS_CN_END

#endif
