//
//  SFForest.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFScene.h"

@interface SFForest : NSObject
{
	NSString * path_;
	
	NSDictionary * scenes_;
	NSString * defaultScene_;
}

@property(nonatomic, retain) NSString * path;
@property(nonatomic, retain) NSDictionary * scenes;
@property(nonatomic, retain) NSString * defaultScene;

+ (id) forest:(NSString *)path;
- (id) initWithPath:(NSString *)path;

- (SFScene *) scene:(NSString *)name;

@end
