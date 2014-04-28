//
//  SFLayer.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFNode.h"

@interface SFLayer : CNLayer
{
	NSArray * textures_;
}

@property(nonatomic, retain) NSArray * textures;

- (id) initWithDictionary:(NSDictionary *)dict;

@end
