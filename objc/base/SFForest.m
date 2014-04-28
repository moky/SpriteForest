//
//  SFForest.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFForest.h"

#import "SFNodeFileParser.h"

@implementation SFForest

@synthesize path = path_;

@synthesize scenes = scenes_;
@synthesize defaultScene = defaultScene_;

+ (id) forest:(NSString *)path
{
	return [[[self alloc] initWithPath:path] autorelease];
}

- (id) initWithPath:(NSString *)path
{
	if ((self = [self init]))
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		
		// path
		NSString * ext = [[path pathExtension] lowercaseString];
		if (![[NSArray arrayWithObjects:@"plist", @"js", @"json", nil] containsObject:ext])
		{
			path = [path stringByAppendingPathComponent:@"main.plist"];
		}
		self.path = [path stringByDeletingLastPathComponent];
		
		// parse it
		SFNodeFileParser * parser = [SFNodeFileParser parser:path];
		NSDictionary * dict = [parser node];
		if ([dict isKindOfClass:[NSDictionary class]])
		{
			// default scene
			self.defaultScene = [dict objectForKey:@"DefaultScene"];
			if (![defaultScene_ isKindOfClass:[NSString class]])
			{
				self.defaultScene = @"default";
			}
			
			// scenes
			self.scenes = [dict objectForKey:@"Scenes"];
			if (![scenes_ isKindOfClass:[NSDictionary class]])
			{
				CNLog(@"parse error! dict = %@", dict);
				self.scenes = nil;
			}
			else
			{
				// check default scene
				NSArray * keys = [scenes_ allKeys];
				if (![keys containsObject:defaultScene_])
				{
					CNLog(@"WARNING: cannot find the default scene '%@'", defaultScene_);
					if ([keys count] > 0)
					{
						self.defaultScene = [keys objectAtIndex:0];
					}
				}
			}
			CNLog(@"default scene = %@", defaultScene_);
		} // EOF 'if ([dict isKindOfClass:[NSDictionary class]])'
		
		[pool release];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.path = nil;
		
		self.scenes = nil;
		self.defaultScene = nil;
	}
	return self;
}

- (void) dealloc
{
	[path_ release];
	
	[scenes_ release];
	[defaultScene_ release];
	
	[super dealloc];
}

#pragma mark -

- (SFScene *) scene:(NSString *)name
{
	if (![name isKindOfClass:[NSString class]])
	{
		name = defaultScene_;
	}
	CNLog(@"scene name = %@", name);
	
	// get scene filename
	NSString * filename = [scenes_ objectForKey:name];
	if (![filename isKindOfClass:[NSString class]])
	{
		CNLog(@"no such scene, name = %@", name);
		return nil;
	}
	
	// load scene data by filename
	filename = [path_ stringByAppendingPathComponent:filename];
	if (![[NSFileManager defaultManager] fileExistsAtPath:filename])
	{
		CNLog(@"'%@' not exists", filename);
		return nil;
	}
	
	CNLog(@"loading scene from '%@'", filename);
	SFNodeFileParser * parser = [SFNodeFileParser parser:filename];
	NSDictionary * dict = [parser node];
	if (![dict isKindOfClass:[NSDictionary class]])
	{
		CNLog(@"Error scene data, dict = %@", dict);
		return nil;
	}
	
	SFScene * scene = [SFScene nodeWithDictionary:dict];
	if (![scene isKindOfClass:[CCScene class]])
	{
		CNLog(@"not a CCScene, dict = %@", dict);
		return nil;
	}
	
	return scene;
}

@end
