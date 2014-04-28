//
//  SFActionMagic.m
//  SpriteForest2
//
//  Created by Moky on 12-10-30.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionMagic.h"

#import "cnMacros.h"
#import "CCMagic.h"

@implementation SFActionMagic

@synthesize dict = dict_;

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		self.dict = dict;
	}
	return self;
}

- (void) dealloc
{
	[dict_ release];
	[super dealloc];
}

- (CCAction *) ccAction
{
	if (![dict_ isKindOfClass:[NSDictionary class]])
	{
		CNLog(@"Error: dict = %@", dict_);
		return [super ccAction];
	}
	return [CCMagic actionWithDictionary:dict_];
}

@end
