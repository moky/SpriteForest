//
//  SFActionTween.m
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionTween.h"

#import "cnMacros.h"


@implementation SFActionTween

@synthesize key = key_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		id key = [dict objectForKey:@"Key"];
		if ([key isKindOfClass:[NSString class]])
		{
			self.key = key;
		}
		
		from_ = [[dict objectForKey:@"From"] floatValue];
		to_ = [[dict objectForKey:@"To"] floatValue];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.key = nil;
	}
	return self;
}

- (void) dealloc
{
	[key_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![key_ isKindOfClass:[NSString class]])
	{
		CNLog(@"Error: key = %@", key_);
		return [super ccAction];
	}
	return [CCActionTween actionWithDuration:duration_ key:key_ from:from_ to:to_];
}

@end
