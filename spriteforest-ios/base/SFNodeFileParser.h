//
//  SFNodeFileParser.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "coconut2d.h"

@interface SFNodeFileParser : NSObject
{
	NSString * path_;
	NSDictionary * root_;
}

@property (nonatomic, retain) NSString * path;
@property (nonatomic, retain) NSDictionary * root;

+ (id) parser:(NSString *)path;
- (id) initWithFile:(NSString *)path;

- (void) parse:(NSString *)path;
- (id) node;

@end
