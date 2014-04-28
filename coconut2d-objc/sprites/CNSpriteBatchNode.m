//
//  CNSpriteBatchNode.m
//  Coconut2D
//
//  Created by Moky on 12-10-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNSpriteBatchNode.h"

@implementation CNSpriteBatchNode

+ (id) batchNodeWithFile:(NSString *)fileImage
{
	return [[self alloc] initWithFile:fileImage];
}

- (id) initWithFile:(NSString *)fileImage
{
	NSAssert([[NSFileManager defaultManager] fileExistsAtPath:fileImage],
			 @"SFSpriteBatchNode > image file: %@", fileImage);
	if ((self = [super initWithFile:fileImage capacity:29]))
	{
		self.anchorPoint = CGPointZero;
		self.position = CGPointZero;
	}
	return self;
}

@end
