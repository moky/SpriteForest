//
//  CCMaskTo.m
//  SpriteForest
//
//  Created by Moky on 11-12-26.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "CCMask.h"


@implementation CCMaskTo

+ (id) actionWithDuration:(ccTime)t rect:(CGRect)r
{
	return [[[self alloc] initWithDuration:t rect:r] autorelease];
}

- (id) initWithDuration:(ccTime)t rect:(CGRect)r
{
	if ((self = [super initWithDuration:t]))
	{
		endRect_ = CC_RECT_PIXELS_TO_POINTS(r);
	}
	return self;
}

- (void) startWithTarget:(id)aTarget
{
	[super startWithTarget:aTarget];
	
	startRect_ = [target_ textureRect];
	CGPoint endXY = ccp(endRect_.origin.x, endRect_.origin.y);
	CGPoint endWH = ccp(endRect_.size.width, endRect_.size.height);
	
	CGPoint startXY = ccp(startRect_.origin.x, startRect_.origin.y);
	CGPoint startWH = ccp(startRect_.size.width, startRect_.size.height);
	
	CGPoint deltaXY = ccpSub(endXY, startXY);
	CGPoint deltaWH = ccpSub(endWH, startWH);
	delta_ = CGRectMake(deltaXY.x, deltaXY.y, deltaWH.x, deltaWH.y);
}

- (id) copyWithZone:(NSZone *)zone
{
	CCAction *copy = [[[self class] allocWithZone:zone] initWithDuration:[self duration] rect:endRect_];
	return copy;
}

- (void) update:(ccTime)t 
{
	CGRect newTextureRect = CGRectMake((startRect_.origin.x + delta_.origin.x * t),
									   (startRect_.origin.y + delta_.origin.y * t),
									   (startRect_.size.width + delta_.size.width * t),
									   (startRect_.size.height + delta_.size.height * t));
	[target_ setTextureRect:newTextureRect];
}


@end


@implementation CCMaskBy

+ (id) actionWithDuration:(ccTime)t rect:(CGRect)r
{
	return [[[self alloc] initWithDuration:t rect:r] autorelease];
}

- (void) startWithTarget:(id)aTarget
{
	[super startWithTarget:aTarget];
	
	startRect_ = [target_ textureRect];
	endRect_ = CGRectMake(startRect_.origin.x + endRect_.origin.x,
						 startRect_.origin.y + endRect_.origin.y,
						 endRect_.size.width, endRect_.size.height);
	
	CGPoint endXY = ccp(endRect_.origin.x, endRect_.origin.y);
	CGPoint endWH = ccp(endRect_.size.width, endRect_.size.height);
	
	CGPoint startXY = ccp(startRect_.origin.x, startRect_.origin.y);
	CGPoint startWH = ccp(startRect_.size.width, startRect_.size.height);
	
	CGPoint deltaXY = ccpSub(endXY, startXY);
	CGPoint deltaWH = ccpSub(endWH, startWH);
	delta_ = CGRectMake(deltaXY.x, deltaXY.y, deltaWH.x, deltaWH.y);
}

@end

