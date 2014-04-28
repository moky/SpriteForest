//
//  CNFiniteLayer.h
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNFiniteLayer_h
#define Coconut2D_X_CNFiniteLayer_h

#include "CNLayer.h"

NS_CN_BEGIN

class CNFiniteLayer : public CNLayer
{
public:
	static cocos2d::CCPoint limitPosition(cocos2d::CCNode * node,
							  const cocos2d::CCPoint & position,
							  const cocos2d::CCRect & rect);
	
	virtual void setPosition(const cocos2d::CCPoint & tPosition);
};

NS_CN_END

#endif
