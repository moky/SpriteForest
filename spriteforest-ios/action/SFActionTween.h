//
//  SFActionTween.h
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionInterval.h"


@interface SFActionTween : SFActionInterval
{
	NSString * key_;
	float from_;
	float to_;
}
@property(nonatomic, retain) NSString * key;

@end
