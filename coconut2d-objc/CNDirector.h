//
//  CNDirector.h
//  Coconut2D
//
//  Created by Moky on 12-10-27.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNDirector : NSObject
{
	CGSize winSize_;
}

@property(nonatomic, readwrite) CGSize winSize;

+ (CNDirector *) sharedDirector;

@end
