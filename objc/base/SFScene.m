//
//  SFScene.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFScene.h"

#import "SFLayer.h"


@implementation SFScene

@synthesize textures = textures_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [self init])) 
	{
		CGSize winSize = CGSizeZero;
		// get window size
		NSString * windowSize = [dict objectForKey:@"WindowSize"];
		if ([windowSize isKindOfClass:[NSString class]])
		{
			winSize = CGSizeFromString(windowSize);
		}
		if (winSize.width == 0 || winSize.height == 0)
		{
			winSize = CGSizeMake(SF_DEFAULT_WINDOW_WIDTH, SF_DEFAULT_WINDOW_HEIGHT);
		}
		[[CNDirector sharedDirector] setWinSize:winSize]; // update window size
		
		
		// load textures
		NSArray * textures = [dict objectForKey:@"Textures"];
		if ([textures isKindOfClass:[NSArray class]])
		{
			self.textures = [SFScene loadTextures:textures];
		}
		
		// create layers
		NSArray * layers = [dict objectForKey:@"Layers"];
		[self addLayers:layers];
		
		
		// N-Screen support
		CGSize realWinSize = [[CCDirector sharedDirector] winSize];
		CCNode * child;
		CCARRAY_FOREACH([self children], child)
		{
			if (![child isKindOfClass:[CCNode class]])
			{
				continue;
			}
			[child setScaleX:child.scaleX * realWinSize.width / winSize.width];
			[child setScaleY:child.scaleY * realWinSize.height / winSize.height];
		}
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.textures = nil;
	}
	return self;
}

- (void) dealloc
{
	self.textures = nil;
	[super dealloc];
}

- (void) setTextures:(NSArray *)textures
{
	if (textures != textures_)
	{
		CNLog(@"cleaning textures: %@", textures_);
		[SFScene cleanTextures:textures_];
		[textures_ release];
		textures_ = [textures retain];
	}
}

#pragma mark -

// copy from 'CCSpriteFrameCache.m'
+ (CCTexture2D *) loadTextureWithPlistPath:(NSString *)plist
{
	NSString *path = [CCFileUtils fullPathFromRelativePath:plist];
    NSDictionary *dict = [NSDictionary dictionaryWithContentsOfFile:path];
	
    NSString *texturePath = nil;
    NSDictionary *metadataDict = [dict objectForKey:@"metadata"];
    if( metadataDict ) {
        texturePath = [metadataDict objectForKey:@"textureFileName"];
	}
	
    if( texturePath ) {
        NSString *textureBase = [plist stringByDeletingLastPathComponent];
        texturePath = [textureBase stringByAppendingPathComponent:texturePath];
    } else {
        texturePath = [plist stringByDeletingPathExtension];
        texturePath = [texturePath stringByAppendingPathExtension:@"png"];
    }
	
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:texturePath];
	
	if( texture ) {
		[[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithDictionary:dict texture:texture];
	}
	
	return texture;
}

+ (NSArray *) loadTextures:(NSArray *)textures
{
	NSMutableArray * mArray = nil;
	if (![textures isKindOfClass:[NSArray class]])
	{
		CNLog(@"no textures found.");
		return mArray;
	}
	mArray = [NSMutableArray arrayWithCapacity:[textures count]];
	
	NSString * res = [[NSBundle mainBundle] resourcePath];
	for (id item in textures)
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		
		NSString * filename = nil;
		if ([item isKindOfClass:[NSDictionary class]])
		{
			NSDictionary * dict = (NSDictionary *)item;
			filename = [dict objectForKey:@"File"];
		}
		else
		{
			filename = (NSString *)item;
			if (![filename isAbsolutePath])
			{
				filename = [res stringByAppendingPathComponent:filename];
			}
		}
		CNLog(@"filename = %@", filename);
		
		CCTexture2D *texture = [self loadTextureWithPlistPath:filename];
		if ([texture isKindOfClass:[CCTexture2D class]])
		{
			[mArray addObject:texture];
		}
		else
		{
			CNLog(@"could not happen!");
		}
		
		[pool release];
	}
	
	return mArray;
}

+ (void) cleanTextures:(NSArray *)textures
{
	if (![textures isKindOfClass:[NSArray class]])
	{
		CNLog(@"no textures found.");
		return ;
	}
	for (CCTexture2D * texture in textures)
	{
		if (![texture isKindOfClass:[CCTexture2D class]])
		{
			CNLog(@"error: texture = %@", texture);
			continue;
		}
		[[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFramesFromTexture:texture];
		[[CCTextureCache sharedTextureCache] removeTexture:texture];
	}
}

@end
