//
//  SFAnimation.m
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFAnimation.h"

@implementation SFAnimation

+ (id) animationWithFrames:(NSArray*)frames delay:(float)delay
{
	NSString * resourcePath = [[NSBundle mainBundle] resourcePath];
	NSFileManager * fileManager = [NSFileManager defaultManager];
	CCTextureCache * textureCache = [CCTextureCache sharedTextureCache];
	CCSpriteFrameCache * spriteFrameCache = [CCSpriteFrameCache sharedSpriteFrameCache];
	
	NSString * filename;
	CCSpriteFrame * frame;
	CCTexture2D * texture;
	NSMutableArray * ma = [NSMutableArray arrayWithCapacity:[frames count]];
	for (id item in frames)
	{
		// get filename
		if ([item isKindOfClass:[NSString class]])
		{
			filename = (NSString *)item;
			filename = [resourcePath stringByAppendingPathComponent:filename];
		}
		else if ([item isKindOfClass:[NSDictionary class]])
		{
			NSDictionary * dict = (NSDictionary *)item;
			filename = [dict objectForKey:@"File"];
			if (![filename isKindOfClass:[NSString class]])
			{
				CNLog(@"invalid frame, dict = %@", dict);
				continue;
			}
		}
		else
		{
			CNLog(@"error frame item: %@", item);
			continue;
		}
		
		// get frame
		frame = nil;
		if ([fileManager fileExistsAtPath:filename])
		{
			texture = [textureCache addImage:filename];
			CGSize size = texture.contentSize;
			CGRect rect = CGRectMake(0, 0, size.width, size.height);
			frame = [CCSpriteFrame frameWithTexture:texture rect:rect];
		}
		else
		{
			filename = [filename lastPathComponent];
			frame = [spriteFrameCache spriteFrameByName:filename];
		}
		if ([frame isKindOfClass:[CCSpriteFrame class]])
		{
			[ma addObject:frame];
		}
	}
	if ([ma count] == 0)
	{
		CNLog(@"no valid frames");
		return nil;
	}
	
	return [CCAnimation animationWithFrames:ma delay:delay];
}

@end
