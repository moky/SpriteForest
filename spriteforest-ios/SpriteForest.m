//
//  SpriteForest.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SpriteForest.h"

#import "SFTransitionScene.h"

@implementation SpriteForest

- (BOOL) performScene:(id)data;
{
	id scene = nil;
	
	if ([data isKindOfClass:[NSString class]])
	{
		scene = [self scene:data];
	}
	else if ([data isKindOfClass:[NSDictionary class]])
	{
		NSDictionary * dict = (NSDictionary *)data;
		scene = [dict objectForKey:@"Scene"];
		if ([scene isKindOfClass:[NSString class]])
		{
			scene = [self scene:scene];
		}
		if (![scene isKindOfClass:[CCScene class]])
		{
			CNLog(@"failed to create scene, dict = %@", scene);
			return NO;
		}
		
		// transit the scene
		NSMutableDictionary * md = [NSMutableDictionary dictionaryWithDictionary:dict];
		[md setObject:scene forKey:@"Scene"];
		scene = [SFTransitionScene transitionScene:md];
	}
	else
	{
		CNLog(@"perform default scene");
		scene = [self scene:nil];
	}
	
	if (![scene isKindOfClass:[CCScene class]])
	{
		CNLog(@"failed to create scene, data = %@", data);
		return NO;
	}
	
	[SFScene perform:scene];
	return YES;
}

@end


#pragma mark - Forest Lord


@implementation ForestLord

@synthesize currentForest = currentForest_;
@synthesize history = history_;

static ForestLord * _sharedLord = nil;

+ (ForestLord *) sharedLord
{
	@synchronized(_sharedLord)
	{
		if (!_sharedLord)
		{
			_sharedLord = [[self alloc] init];
		}
	}
	return _sharedLord;
}

+ (id) alloc
{
	NSAssert(_sharedLord == nil, @"It's illegal to have more than ONE lord!");
	return [super alloc];
}

- (id) init
{
	if ((self = [super init]))
	{
		self.currentForest = nil;
		self.history = [NSMutableArray arrayWithCapacity:29];
		
		// for loading indicator
		[loadingIndicator_ removeFromSuperview];
		[loadingIndicator_ release];
		loadingIndicator_ = nil;
		[loadingView_ removeFromSuperview];
		[loadingView_ release];
		loadingView_ = nil;
		loadingIndicatorRetainCount_ = 0;
	}
	return self;
}

- (void) dealloc
{
	// for loading indicator
	[loadingIndicator_ release];
	[loadingView_ release];
	
	[currentForest_ release];
	[history_ release];
	[super dealloc];
}

#pragma mark -

+ (BOOL) forestExistsAtPath:(NSString *)path
{
	if ([path isKindOfClass:[NSString class]])
	{
		NSString * ext = [[path pathExtension] lowercaseString];
		if (![[NSArray arrayWithObjects:@"plist", @"js", @"json", nil] containsObject:ext])
		{
			path = [path stringByAppendingPathComponent:@"main.plist"];
		}
		return [[NSFileManager defaultManager] fileExistsAtPath:path];
	}
	return NO;
}

- (BOOL) runIntoForest:(NSString *)path withScene:(id)data
{
	if (![[self class] forestExistsAtPath:path])
	{
		CNLog(@"forest not exists at path: %@", path);
		return NO;
	}
	
	[history_ addObject:[NSDictionary dictionaryWithObject:path forKey:@"File"]];
	
	CNLog(@"running into forest: %@", path);
	self.currentForest = [SpriteForest forest:path];
	return [self performScene:data];
}

- (BOOL) runIntoForest:(NSString *)path
{
	return [self runIntoForest:path withScene:nil];
}

- (BOOL) performScene:(id)data;
{
	id scene;
	if ([data isKindOfClass:[NSDictionary class]])
	{
		scene = [data objectForKey:@"Scene"];
	}
	else if (data)
	{
		scene = data;
	}
	else
	{
		scene = [NSNull null];
	}
	[history_ addObject:[NSDictionary dictionaryWithObject:scene forKey:@"Scene"]];
	CNLog(@"data = %@, history: %@", data, history_);
	
	return [currentForest_ performScene:data];
}


//////////////////////////////////
//
//  history stack:
//
//        (0)   File : "/path/to/forest/root/default.bundle/main.plist"
//        (1)   Scene: [NSNull null]
//        (2)   Scene: "scene2"
//        (x)   ...
//        (x+1) File : "/path/to/forest/root/forest2.bundle/main.plist"
//        (x+2) Scene: [NSNull null]
//
- (BOOL) goBack
{
	@synchronized(history_)
	{
		if ([history_ count] <= 2)
		{
			CNLog(@"reach the first scene");
			return NO;
		}
		[history_ removeLastObject];
		
		NSDictionary * last = [history_ lastObject];
		if (![last isKindOfClass:[NSDictionary class]])
		{
			CNLog(@"ERROR: could not happen, dict = %@", last);
			[history_ removeLastObject];
			return NO;
		}
		
		NSString * path = nil;
		if ([[last objectForKey:@"File"] isKindOfClass:[NSString class]])
		{
			// it's the bounds of anthor forest
			[history_ removeLastObject];
			
			// searching the previous forest's path
			for (int pos = [history_ count] - 1; pos >= 0; pos--)
			{
				NSDictionary * dict = [history_ objectAtIndex:pos];
				if (![dict isKindOfClass:[NSDictionary class]])
				{
					CNLog(@"ERROR: could not happen, dict = %@", dict);
					continue;
				}
				path = [dict objectForKey:@"File"];
				if ([path isKindOfClass:[NSString class]])
				{
					CNLog(@"path = %@", path);
					break;
				}
			}
		}
		
		id data = nil;
		last = [history_ lastObject];
		if ([last isKindOfClass:[NSDictionary class]])
		{
			data = [last objectForKey:@"Scene"];
		}
		
		[path retain];
		[data retain];
		[history_ removeLastObject];
		
		if (path)
		{
			[self runIntoForest:path withScene:data];
			if ([history_ count] > 2)
			{
				// remove duplicated 'File' record
				[history_ removeObjectAtIndex:[history_ count] - 2];
			}
		}
		else
		{
			[self performScene:data];
		}
		
		[path release];
		[data release];
		
	} // EOF @synchronized(history_)
	
	return YES;
}

#pragma mark Loading indicator

- (void) removeLoadingIndicator
{
	if (loadingIndicator_)
	{
		if ([loadingIndicator_ isAnimating])
		{
			[loadingIndicator_ stopAnimating];
		}
		[loadingIndicator_ removeFromSuperview];
		[loadingIndicator_ release];
		loadingIndicator_ = nil;
		CNLog(@"OK");
	}
	if (loadingView_)
	{
		NSArray * subviews = loadingView_.subviews;
		for (UIView * view in subviews)
		{
			[view removeFromSuperview];
		}
		[loadingView_ removeFromSuperview];
		[loadingView_ release];
		loadingView_ = nil;
		CNLog(@"OK");
	}
}

- (void) addLoadingIndicator
{
	[self removeLoadingIndicator];
	
	CCDirector * director = [CCDirector sharedDirector];
	CGSize winSize = [director winSize];
	CGRect frame = CGRectMake(0, 0, winSize.width, winSize.height);
	loadingView_ = [[UIView alloc] initWithFrame:frame];
	
	// gray layer
	UIView * grayView = [[[UIView alloc] initWithFrame:frame] autorelease];
	grayView.backgroundColor = [UIColor blackColor];
	grayView.alpha = 0.7f;
	[loadingView_ addSubview:grayView];
	
	// indicator
	loadingIndicator_ = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	loadingIndicator_.center = CGPointMake(winSize.width / 2, winSize.height / 2);
	[loadingIndicator_ startAnimating];
	[loadingView_ addSubview:loadingIndicator_];
	
	[director.openGLView addSubview:loadingView_];
	CNLog(@"OK");
}

- (void) showLoadingIndicator
{
	CNLog(@"oooo +++++++++++++++++++++++++++++++++++++++");
	loadingIndicatorRetainCount_++;
	if (loadingIndicatorRetainCount_ > 1)
	{
		CNLog(@"indicator already shown, retain count = %d", loadingIndicatorRetainCount_);
		return;
	}
//	if ([loadingView_ isKindOfClass:[UIView class]] && [loadingIndicator_ isKindOfClass:[UIActivityIndicatorView class]])
//	{
//		[loadingView_ setHidden:NO];
//		[loadingIndicator_ startAnimating];
//		CNLog(@"indicator shown");
//		return;
//	}
	
//	[self addLoadingIndicator];
	[self performSelectorOnMainThread:@selector(addLoadingIndicator) withObject:nil waitUntilDone:YES];
}

- (void) hideLoadingIndicator
{
	CNLog(@"oooo ---------------------------------------");
	loadingIndicatorRetainCount_--;
	if (loadingIndicatorRetainCount_ > 0)
	{
		CNLog(@"indicator retain count = %d", loadingIndicatorRetainCount_);
		return;
	}
	else if (loadingIndicatorRetainCount_ < 0)
	{
		CNLog(@"Error: indicator retain count = %d", loadingIndicatorRetainCount_);
		loadingIndicatorRetainCount_ = 0;
	}
//	if ([loadingIndicator_ isKindOfClass:[UIActivityIndicatorView class]])
//	{
//		[loadingIndicator_ stopAnimating];
//		CNLog(@"indicator hidden");
//	}
//	if ([loadingView_ isKindOfClass:[UIView class]])
//	{
//		[loadingView_ setHidden:YES];
//	}
	
	[self removeLoadingIndicator];
}

@end
