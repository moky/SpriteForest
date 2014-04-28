//
//  CNScaleLayerController.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNScaleLayerController : NSObject<CCStandardTouchDelegate>
{
	CCLayer * layer_;
}

@property(nonatomic, retain) CCLayer * layer;

@end
