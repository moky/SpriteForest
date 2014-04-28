//
//  SFTouchSprite.h
//  SpriteForest2
//
//  Created by Moky on 12-10-3.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFSprite.h"
#import "SFEventHandler.h"


@interface SFTouchSprite : SFSprite
{
	CNTouchController * controller_;
	BOOL irregular_; // if it's polygon sprite, check visible pixel for touch
	CGRect touchBounds_;
}

@property(nonatomic, retain) CNTouchController * controller;
@property(nonatomic, readwrite) BOOL irregular;
@property(nonatomic, readwrite) CGRect touchBounds;

@end


@interface SFTouchHandler : SFEventHandler<CNTouchDelegate, CNDragDelegate>

@end
