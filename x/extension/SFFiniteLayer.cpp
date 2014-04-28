//
//  SFFiniteLayer.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFFiniteLayer.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

void SFFiniteLayer::setPosition(const CCPoint & tPosition)
{
	CCPoint position = tPosition;
	CCNode * parent = this->getParent();
	if (parent)
	{
		CCSize winSize = parent->getContentSize();
		CCRect rect = CCRect(0, 0, winSize.width, winSize.height);
		position = CNFiniteLayer::limitPosition(this, position, rect);
	}
	CNLayer::setPosition(position);
}

NS_SF_END
