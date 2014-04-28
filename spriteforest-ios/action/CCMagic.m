//
//  CCMagic.m
//  SpriteForest2
//
//  Created by Moky on 12-10-30.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CCMagic.h"

#import "SFSprite.h"
#import "SpriteForest.h"
#import "SFAudio.h"
#import "SFParticleSystem.h"
#import "SFWebBrowser.h"
#import "SFNodeFileParser.h"

@implementation CCMagic

@synthesize dict = dict_;

+ (id) actionWithDictionary:(NSDictionary *)dict
{
	return [[[self alloc] initWithDictionary:dict] autorelease];
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [self init]))
	{
		self.dict = dict;
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.dict = nil;
	}
	return self;
}

- (void) dealloc
{
	[dict_ release];
	[super dealloc];
}

- (NSString *) description
{
	return [NSString stringWithFormat:@"<%@ = %8@ | Tag = %i | dict = %@>",
			[self class],
			self,
			tag_,
			dict_
			];
}

- (id) copyWithZone: (NSZone*) zone
{
	CCActionInstant * copy = [[[self class] allocWithZone:zone] initWithDictionary:dict_];
	return copy;
}

- (void) startWithTarget:(id)aTarget
{
	[super startWithTarget:aTarget];
	[self execute];
}

#pragma mark -

- (CCNode *) getTarget
{
	if (![dict_ isKindOfClass:[NSDictionary class]])
	{
		return target_;
	}
	return [target_ getTarget:[dict_ objectForKey:@"Target"]];
}

- (void) execute
{
	NSString * actionName = [dict_ objectForKey:@"Name"];
	if (![actionName isKindOfClass:[NSString class]])
	{
		CNLog(@"invalid action, dict = %@", dict_);
		return;
	}
	
	SEL selector = NSSelectorFromString([@"do" stringByAppendingString:actionName]);
	if (selector && [self respondsToSelector:selector])
	{
		[self performSelector:selector];
		return;
	}
	
	CCNode * target = [self getTarget];
	if ([target isKindOfClass:[SFSprite class]])
	{
		SFEventHandler * worker = [(SFSprite *)target eventHandler];
		if ([worker doEvent:actionName node:target])
		{
			//CNLog(@"target = %@, actionName = %@", target, actionName);
		}
		else if ([worker doAction:actionName node:target])
		{
			//CNLog(@"target = %@, action dict = %@", target, dict_);
		}
		else
		{
			CNLog(@"no such action: %@", actionName);
		}
	}
}

#pragma mark loading indicator

- (void) doLoadingIndicator
{
	NSString * hidden = [dict_ objectForKey:@"Hidden"];
	if (hidden == nil)
	{
		CNLog(@"invalid dict = %@", dict_);
		return;
	}
	if ([hidden boolValue])
	{
		[self doHideIndicator];
	}
	else
	{
		[self doShowIndicator];
	}
}

- (void) doShowIndicator
{
	[[ForestLord sharedLord] showLoadingIndicator];
}

- (void) doHideIndicator
{
	[[ForestLord sharedLord] hideLoadingIndicator];
}

#pragma mark forest

- (void) performForestWithDictonary:(NSDictionary *)dict
{
	NSString * history = [dict objectForKey:@"History"];
	if ([history isKindOfClass:[NSString class]])
	{
		if ([history caseInsensitiveCompare:@"goBack()"] == NSOrderedSame)
		{
			if ([[ForestLord sharedLord] goBack])
			{
				CNLog(@"back to previous forest/scene.");
			}
			else
			{
				CNLog(@"failed to go back");
			}
		}
		else
		{
			CNLog(@"unrecognized history: %@", history);
		}
		return;
	}
	
	NSString * path = [dict objectForKey:@"File"];
	id scene = [dict objectForKey:@"Scene"];
	
	if ([path isKindOfClass:[NSString class]])
	{
		if ([[ForestLord sharedLord] runIntoForest:path withScene:scene])
		{
			CNLog(@"OK");
		}
		else
		{
			CNLog(@"invalid forest, dict = %@", dict);
		}
	}
	else if (scene)
	{
		if ([[ForestLord sharedLord] performScene:scene])
		{
			CNLog(@"OK");
		}
		else
		{
			CNLog(@"failed to perform scene: %@", scene);
		}
	}
	else
	{
		CNLog(@"ERROR: dict = %@", dict);
	}
}

- (void) performForestWithDictonary:(NSDictionary *)dict showIndicator:(NSString *)showIndicator
{
	BOOL allowShowIndicator = YES;
	// show indicator ?
	if (showIndicator != nil)
	{
		allowShowIndicator = [showIndicator boolValue];
	}
	
	if (allowShowIndicator)
	{
		[self doShowIndicator];
		[self performSelector:@selector(performForestWithDictonary:) withObject:dict afterDelay:SF_PERFORM_FOREST_DELAY];
		[self performSelector:@selector(doHideIndicator) withObject:nil afterDelay:SF_HIDE_INDICATOR_DELAY];
	}
	else
	{
		[self performForestWithDictonary:dict];
	}
}

- (void) doForest
{
	id showIndicator = [dict_ objectForKey:@"ShowIndicator"];
	[self performForestWithDictonary:dict_ showIndicator:showIndicator];
}

- (void) doScene
{
	if (!dict_)
	{
		CNLog(@"could not happen!");
		return;
	}
	// this is a 'Scene' action info, transform it to a 'Forest' action info
	NSDictionary * dict = [NSDictionary dictionaryWithObject:dict_ forKey:@"Scene"];
	id showIndicator = [dict_ objectForKey:@"ShowIndicator"];
	[self performForestWithDictonary:dict showIndicator:showIndicator];
}

#pragma mark media

- (void) doAudio
{
	if (![SFAudio perform:dict_])
	{
		CNLog(@"invalid audio, dict = %@", dict_);
	}
}

- (void) doParticle
{
	CCNode * target = [self getTarget];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"could not happen!");
		return;
	}
	
	@try
	{
		[[SFParticleSystem particle:dict_] runWithNode:target];
	}
	@catch (NSException * exception)
	{
		CNLog(@"Exception: %@", [exception debugDescription]);
	}
	@finally
	{
		CNLog(@"Particle OK");
	}
}

- (void) doWeb
{
	NSString * url = [dict_ objectForKey:@"URL"];
	if ([url isKindOfClass:[NSString class]])
	{
		NSString * frame = [dict_ objectForKey:@"Frame"];
		if ([frame isKindOfClass:[NSString class]])
		{
			NSString * closeButton = [dict_ objectForKey:@"CloseButton"];
			if ([closeButton isKindOfClass:[NSDictionary class]])
			{
				closeButton = [(NSDictionary *)closeButton objectForKey:@"File"];
			}
			if ([closeButton isKindOfClass:[NSString class]])
			{
				CNLog(@"open web: %@ , in frame: %@, with close button: %@", url, frame, closeButton);
				[SFWebBrowser openURL:url inFrame:CGRectFromString(frame) closeButton:closeButton];
			}
			else
			{
				CNLog(@"open web: %@ , in frame: %@", url, frame);
				[SFWebBrowser openURL:url inFrame:CGRectFromString(frame)];
			}
		}
		else
		{
			CNLog(@"open URL: %@", url);
			[SFWebBrowser openURL:url];
		}
	}
	else
	{
		CNLog(@"no URL to open, dict = %@", dict_);
	}
}

- (void) doAlert
{
	NSString * title = [dict_ objectForKey:@"Title"];
	NSString * message = [dict_ objectForKey:@"Message"];
	UIAlertView * alert = [[UIAlertView alloc] initWithTitle:title
													 message:message
													delegate:nil
										   cancelButtonTitle:@"OK"
										   otherButtonTitles:nil];
	[alert show];
	[alert release];
}

#pragma mark relationship

- (void) doAddChild
{
	CCNode * target = [self getTarget];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"could not happen!");
		return;
	}
	
	NSString * filename = [dict_ objectForKey:@"File"];
	if (![filename isKindOfClass:[NSString class]])
	{
		CNLog(@"invalid action, dict = %@", dict_);
		return;
	}
	
	CNLog(@"adding child from %@", filename);
	SFNodeFileParser * parser = [SFNodeFileParser parser:filename];
	NSDictionary * dict = [parser node];
	if ([dict isKindOfClass:[NSDictionary class]])
	{
		NSInteger zOrder = [[dict objectForKey:@"ZOrder"] intValue];
		CCNode * child = [SFSprite nodeWithDictionary:dict];
		if ([child isKindOfClass:[CCNode class]])
		{
			[target addChild:child z:zOrder];
		}
	}
}

- (void) doRemoveFromParent
{
	CCNode * target = [self getTarget];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"could not happen!");
		return;
	}
	
	BOOL cleanup = YES;
	id value = [dict_ objectForKey:@"Cleanup"];
	if (value)
	{
		cleanup = [value intValue];
	}
	[target removeFromParentAndCleanup:cleanup];
}

- (void) doStopAllActions
{
	CCNode * target = [self getTarget];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"could not happen!");
		return;
	}
	
	[target stopAllActions];
}

#pragma mark Notification Center

- (void) doNotification
{
	CCNode * target = [self getTarget];
	if (![target isKindOfClass:[CCNode class]])
	{
		CNLog(@"could not happen!");
		return;
	}
	
	NSString * eventName = [dict_ objectForKey:@"Event"];
	if (!eventName)
	{
		CNLog(@"invalid action: %@, target: %@", dict_, target);
		return;
	}
	
	CNLog(@"postNotificationName: %@, object: %@, userInfo: %@", eventName, target, dict_);
	NSNotificationCenter * center = [NSNotificationCenter defaultCenter];
	[center postNotificationName:eventName object:target userInfo:dict_];
}

@end
