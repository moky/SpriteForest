//
//  SFActionProgressTimer.m
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionProgressTimer.h"


@implementation SFProgressTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		percent_ = [[dict objectForKey:@"Percent"] floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCProgressTo actionWithDuration:duration_ percent:percent_];
}

@end


@implementation SFProgressFromTo

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict]))
	{
		fromPercent_ = [[dict objectForKey:@"FromPercent"] floatValue];
		toPercent_ = [[dict objectForKey:@"ToPercent"] floatValue];
	}
	return self;
}

- (CCAction *) ccAction
{
	return [CCProgressFromTo actionWithDuration:duration_ from:fromPercent_ to:toPercent_];
}

@end

