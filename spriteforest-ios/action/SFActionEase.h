//
//  SFActionEase.h
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionInterval.h"


@interface SFActionEase : SFActionInterval
{
	CCActionInterval * action_;
}
@property(nonatomic, retain) CCActionInterval * action;

@end


#pragma mark - Action Ease Rate


@interface SFEaseRateAction : SFActionEase
{
	float rate_;
}

@end


@interface SFEaseIn : SFEaseRateAction

@end


@interface SFEaseOut : SFEaseRateAction

@end


@interface SFEaseInOut : SFEaseRateAction

@end


#pragma mark - Action Ease Exponential


@interface SFEaseExponentialIn : SFActionEase

@end


@interface SFEaseExponentialOut : SFActionEase

@end


@interface SFEaseExponentialInOut : SFActionEase

@end


#pragma mark - Action Ease Sine


@interface SFEaseSineIn : SFActionEase

@end


@interface SFEaseSineOut : SFActionEase

@end


@interface SFEaseSineInOut : SFActionEase

@end


#pragma mark - Action Ease Elastic


@interface SFEaseElastic : SFActionEase

@end


@interface SFEaseElasticIn : SFEaseElastic

@end


@interface SFEaseElasticOut : SFEaseElastic

@end


@interface SFEaseElasticInOut : SFEaseElastic

@end


#pragma mark - Action Ease Bounce


@interface SFEaseBounce : SFActionEase

@end


@interface SFEaseBounceIn : SFEaseBounce

@end


@interface SFEaseBounceOut : SFEaseBounce

@end


@interface SFEaseBounceInOut : SFEaseBounce

@end


#pragma mark - Action Ease Back


@interface SFEaseBackIn : SFActionEase

@end


@interface SFEaseBackOut : SFActionEase

@end


@interface SFEaseBackInOut : SFActionEase

@end
