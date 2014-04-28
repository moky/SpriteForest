//
//  SFDragSprite.h
//  SpriteForest2
//
//  Created by Moky on 12-10-3.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFTouchSprite.h"
#import "SFEventHandler.h"


@interface SFDragSprite : SFTouchSprite
{
	CGRect dragRange_;
	BOOL dragTied_; // whether fly back to began point after drag end
}

@property(nonatomic, readwrite) CGRect dragRange;
@property(nonatomic, readwrite) BOOL dragTied;

@end

