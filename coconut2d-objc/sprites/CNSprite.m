//
//  CNSprite.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNSprite.h"

#import "cnMacros.h"
#import "cnProtocol.h"
#import "CNDictionary.h"
#import "CNString.h"
#import "CNClient.h"
#import "CNNode.h"


@implementation CNSprite

+ (id) spriteWithFile:(NSString *)filename
{
	return [[[self alloc] initWithFile:filename] autorelease];
}

+ (id) spriteWithDictionary:(NSDictionary *)dict
{
	return [[[self alloc] initWithDictionary:dict] autorelease];
}

- (id) initWithFile:(NSString *)filename
{
	if ((self = [self init]))
	{
		[self replaceImageWithFile:filename];
	}
	return self;
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [self init]))
	{
		NSString * filename = [dict objectForKeyCaseInsensitive:SPRITE_FILE_TAG];
		[self replaceImageWithFile:filename];
		[self setAttributes:dict];
	}
	return self;
}


#pragma mark -


- (void) addChild:(CCNode *)child
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child z:z];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z tag:(NSInteger)tag
{
	if (child == nil || child.parent != nil)
	{
		return ;
	}
	[super addChild:child z:z tag:tag];
}

#pragma mark -

+ (NSArray *) createSprites:(NSArray *)filenames
{
	NSMutableArray * array = [[NSMutableArray alloc] initWithCapacity:[filenames count]];
	CNSprite * sprite;
	for (NSString * filename in filenames)
	{
		sprite = [[CNSprite alloc] initWithFile:filename];
		[sprite.texture setAliasTexParameters];
		[array addObject:sprite];
		[sprite release];
	}
	return [array autorelease];
}

- (void) replaceImageWithFile:(NSString *)filename
{
	if (filename == nil)
	{
		return ;
	}
	
	CGRect rect = CGRectZero;
	CCTexture2D * texture = [[CCTextureCache sharedTextureCache] addImage:filename];
	if (!texture)
	{
		UIImage * image = [[self class] getUIImageWithPath:filename];
		if ([image isKindOfClass:[UIImage class]])
		{
			texture = [[[CCTexture2D alloc] initWithImage:image] autorelease];
		}
	}
	
	if (texture)
	{
		rect.size = texture.contentSize;
	}
	else
	{
		NSString * frameName = [filename lastPathComponent];
		if (frameName == nil)
		{
			frameName = filename;
		}
		
		CCSpriteFrameCache * cache = [CCSpriteFrameCache sharedSpriteFrameCache];
		CCSpriteFrame * spriteFrame = [cache spriteFrameByName:frameName];
		if (spriteFrame)
		{
			texture = spriteFrame.texture;
			rect = spriteFrame.rect;
		}
	}
	
	if (texture && !CGRectEqualToRect(rect, CGRectZero))
	{
		[self setTexture:texture];
		[self setTextureRect:rect];
	}
}

+ (UIImage *) getUIImageWithPath:(NSString *)imagePath
{
	NSRange range = [imagePath rangeOfString:@"://"];
	if (range.location != NSNotFound)
	{
		// this is a URL
		NSURL * url = [NSURL URLWithString:[imagePath dynamicURLString]];
		NSData * imageData = [NSData dataWithContentsOfURL:url];
		if ([imageData isKindOfClass:[NSData class]])
		{
			@try
			{
				return [UIImage imageWithData:imageData];
			}
			@catch (NSException * exception)
			{
				CNLog(@"Exception: %@", [exception debugDescription]);
			}
		}
	}
	else if ([[NSFileManager defaultManager] fileExistsAtPath:imagePath])
	{
		// this is a local path
		return [UIImage imageWithContentsOfFile:imagePath];
	}
	else
	{
		if ([imagePath isAbsolutePath])
		{
			imagePath = [imagePath lastPathComponent];
		}
		// this is an app bundle file
		imagePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:imagePath];
		if ([[NSFileManager defaultManager] fileExistsAtPath:imagePath])
		{
			return [UIImage imageWithContentsOfFile:imagePath];
		}
	}
	
	return nil;
}

@end
