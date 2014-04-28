//
//  SFSprite.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFNode.h"

#import "SFEventHandler.h"

@interface SFSprite : CNSprite
{
	NSArray * textures_;
	id<SFEventDelegate> eventHandler_;
}

@property(nonatomic, retain) NSArray * textures;
@property(nonatomic, retain) id<SFEventDelegate> eventHandler;

- (id) initWithDictionary:(NSDictionary *)dict;

- (void) appointHandlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree;

@end
