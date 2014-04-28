//
//  SFActionInterval.h
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFAction.h"


@interface SFActionInterval : SFFiniteTimeAction

@end


@interface SFSequence : SFActionInterval
{
	NSArray * actions_;
}
@property(nonatomic, retain) NSArray * actions;

@end


@interface SFRepeat : SFActionInterval
{
	CCFiniteTimeAction * action_;
	NSUInteger times_;
}
@property(nonatomic, retain) CCFiniteTimeAction * action;

@end


@interface SFSpawn : SFActionInterval
{
	NSArray * actions_;
}
@property(nonatomic, retain) NSArray * actions;

@end


@interface SFRotateTo : SFActionInterval
{
	float angle_;
}

@end


@interface SFRotateBy : SFRotateTo

@end


@interface SFMoveTo : SFActionInterval
{
	CGPoint position_;
}

@end


@interface SFMoveBy : SFMoveTo

@end


@interface SFSkewTo : SFActionInterval
{
	CGFloat skewX_;
	CGFloat skewY_;
}

@end


@interface SFSkewBy : SFSkewTo

@end


@interface SFJumpTo : SFActionInterval
{
	CGPoint position_;
	ccTime height_;
	NSUInteger jumps_;
}

@end


@interface SFJumpBy : SFJumpTo

@end


@interface SFBezierTo : SFActionInterval
{
	ccBezierConfig bezierConfig_;
}

@end


@interface SFBezierBy : SFBezierTo

@end


@interface SFScaleTo : SFActionInterval
{
	CGFloat scaleX_;
	CGFloat scaleY_;
}

@end


@interface SFScaleBy : SFScaleTo

@end


@interface SFBlink : SFActionInterval
{
	NSUInteger times_;
}

@end


@interface SFFadeIn : SFActionInterval

@end


@interface SFFadeOut : SFActionInterval

@end


@interface SFFadeTo : SFActionInterval
{
	GLubyte opacity_;
}

@end


@interface SFTintTo : SFActionInterval
{
	GLubyte red_;
	GLubyte green_;
	GLubyte blue_;
}

@end


@interface SFTintBy : SFTintTo

@end


@interface SFDelayTime : SFActionInterval

@end


@interface SFReverseTime : SFActionInterval
{
	CCFiniteTimeAction * action_;
}
@property(nonatomic, retain) CCFiniteTimeAction * action;

@end


@interface SFMaskTo : SFActionInterval
{
	CGRect rect_;
}

@end


@interface SFMaskBy : SFMaskTo

@end


@interface SFAnimate : SFActionInterval
{
	NSArray * frames_;
	CGFloat delay_;
	BOOL restoreOriginalFrame_;
}
@property(nonatomic, retain) NSArray * frames;

@end



