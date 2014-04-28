//
//  SFShakeSprite.h
//  SpriteForest2
//
//  Created by Moky on 12-10-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFSprite.h"
#import "SFEventHandler.h"
#import "SFShakeController.h"


@interface SFShakeSprite : SFSprite
{
	SFShakeController * shakeController_;
}

@property(nonatomic, retain) SFShakeController * shakeController;

@end


@interface SFShakeHandler : SFEventHandler<SFShakeDelegate>
{
	SFSprite * sprite_;
}

@property(nonatomic, retain) SFSprite * sprite;

@end
