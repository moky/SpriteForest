//
//  CNFiniteLayer.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNFiniteLayer.h"

#import "cnMacros.h"
#import "CNDirector.h"

#define SCALE_LAYER_MAX_SCALE 2.0f

@implementation CNFiniteLayer

- (CGPoint) limitPosition:(CGPoint)position size:(CGSize)size
{
	CGSize winSize = [[CCDirector sharedDirector] winSize];
	
	CGPoint bottomLeft = [parent_ convertToNodeSpace:CGPointZero];
	CGPoint topRight = [parent_ convertToNodeSpace:ccpFromSize(winSize)];
	
	CGPoint anchor = ccpCompMult(ccpFromSize(size), anchorPoint_);
	
	CGFloat minX = topRight.x - (size.width - anchor.x);
	CGFloat minY = topRight.y - (size.height - anchor.y);
	CGFloat maxX = bottomLeft.x + anchor.x;
	CGFloat maxY = bottomLeft.y + anchor.y;
	
	if (minX > maxX) {
	} else if (position.x < minX) {
		position.x = minX;
	} else if (position.x > maxX) {
		position.x = maxX;
	}
	
	if (minY > maxY) {
	} else if (position.y < minY) {
		position.y = minY;
	} else if (position.y > maxY) {
		position.y = maxY;
	}
	return position;
}

- (void) setPosition:(CGPoint)position
{
	CGSize size = contentSize_;
	size.width *= scaleX_;
	size.height *= scaleY_;
	position = [self limitPosition:position size:size];
	[super setPosition:position];
}



- (void) correctPositionAndScale
{
	CGSize winSize = [[CNDirector sharedDirector] winSize];
	CGSize size = self.contentSize;
	
	// check scale
	CGFloat scaleX = DIV(winSize.width, size.width);
	CGFloat scaleY = DIV(winSize.height, size.height);
	
	CGFloat minScale = MAX(scaleX, scaleY);
	CGFloat maxScale = SCALE_LAYER_MAX_SCALE;
	
	CGFloat newScale = self.scale;
	
	if (newScale < minScale) {
		newScale = minScale;
	} else if (newScale > maxScale) {
		newScale = maxScale;
	}
	
	// check position
	CGPoint center = ccpMult(ccpFromSize(winSize), 0.5f);
	CGPoint delta = ccpSub(center, self.position);
	delta = ccpMult(delta, 1.0f - DIV(newScale, self.scale));
	
	CGPoint newPosition = self.position;
	newPosition = ccpAdd(newPosition, delta);
	newPosition = [self limitPosition:newPosition size:CGSizeMake(size.width * newScale, size.height * newScale)];
	
	CCActionInterval * scaleTo = [CCScaleTo actionWithDuration:0.2f scale:newScale];
	CCActionInterval * moveTo = [CCMoveTo actionWithDuration:0.2f position:newPosition];
	scaleTo = [CCEaseInOut actionWithAction:scaleTo rate:2.0f];
	moveTo = [CCEaseInOut actionWithAction:moveTo rate:2.0f];
	[self runAction:[CCSpawn actions:scaleTo, moveTo, nil]];
}


- (void) onEnter
{
	[super onEnter];
	
	CGPoint center = CGPointMake(contentSize_.width / 2, contentSize_.height / 2);
	
	[self focus:center];
}

@end
