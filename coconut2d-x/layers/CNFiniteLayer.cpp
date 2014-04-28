//
//  CNFiniteLayer.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNFiniteLayer.h"

NS_CN_BEGIN

USING_NS_CC;

#define CN_SCALE_LAYER_MAX_SCALE 2.0f

cocos2d::CCPoint CNFiniteLayer::limitPosition(CCNode * node, const CCPoint & position, const CCRect & rect)
{
	CCPoint bottomLeft = rect.origin;
	CCPoint topRight = ccpFromSize(rect.size);
	
	CCSize size = node->getContentSize();
	size.width *= node->getScaleX();
	size.height *= node->getScaleY();
	
	CCPoint anchor = node->getAnchorPointInPoints();
	anchor.x *= node->getScaleX();
	anchor.y *= node->getScaleY();
	
	CCFloat minX = topRight.x - (size.width - anchor.x);
	CCFloat minY = topRight.y - (size.height - anchor.y);
	CCFloat maxX = bottomLeft.x + anchor.x;
	CCFloat maxY = bottomLeft.y + anchor.y;
	
	CCPoint newPosition = position;
	if (minX > maxX) {
		newPosition.x = position.x;
	} else if (position.x < minX) {
		newPosition.x = minX;
	} else if (position.x > maxX) {
		newPosition.x = maxX;
	}
	
	if (minY > maxY) {
		newPosition.y = position.y;
	} else if (position.y < minY) {
		newPosition.y = minY;
	} else if (position.y > maxY) {
		newPosition.y = maxY;
	}
	
	return newPosition;
}

void CNFiniteLayer::setPosition(const CCPoint & tPosition)
{
	CCPoint position = tPosition;
	CCNode * parent = this->getParent();
	if (parent)
	{
		CCSize winSize = parent->getContentSize();
		CCRect rect = CCRect(0, 0, winSize.width, winSize.height);
		position = limitPosition(this, position, rect);
	}
	CNLayer::setPosition(position);
}

NS_CN_END
