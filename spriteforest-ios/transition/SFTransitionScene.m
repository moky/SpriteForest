//
//  SFTransitionScene.m
//  SpriteForest
//
//  Created by Moky on 11-12-28.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "SFTransitionScene.h"


@implementation SFTransitionScene

@synthesize name = name_;
@synthesize scene = scene_;
@synthesize duration = duration_;
@synthesize orientation = orientation_;
@synthesize color = color_;
@synthesize reverse = reverse_;

+ (SFTransitionScene *) dict:(NSDictionary *)dict
{
	return [[[self alloc] initWithDict:dict] autorelease];
}

- (SFTransitionScene *) initWithDict:(NSDictionary *)dict
{
	if (!dict || ![dict isKindOfClass:[NSDictionary class]])
	{
		NSLog(@"SFTransitionScene: Invalid transition='%@'", dict);
		return nil;
	}
	if (![dict objectForKey:@"Scene"] ||
		![[dict objectForKey:@"Scene"] isKindOfClass:[CCScene class]])
	{
		NSLog(@"SFTransitionScene: Invalid scene='%@'", dict);
		return nil;
	}
	
	if ((self = [super init]))
	{
		self.name = (NSString *)[dict objectForKey:@"Transition"];
		self.scene = (CCScene *)[dict objectForKey:@"Scene"];
		
		self.duration = [[dict objectForKey:@"Duration"] floatValue];
		self.orientation = [[dict objectForKey:@"Orientation"] intValue];
		self.color = ccc3(255, 255, 255);
		self.reverse = [[dict objectForKey:@"Reverse"] boolValue];
	}
	return self;
}

- (void) dealloc
{
	[name_ release];
    name_ = nil;
	[scene_ release];
	scene_ = nil;
	[super dealloc];
}

- (BOOL) isNamed:(NSString *)name
{
	if ([name_ isEqualToString:name])
	{
		return YES;
	}
	return NO;
}

#pragma mark -
#pragma mark Interface method

+ (CCScene *) transitionScene:(NSDictionary *)dict
{
	CCScene * scene = nil;
	
	SFTransitionScene * d = [SFTransitionScene dict:dict];
	if (!d)
	{
		NSLog(@"SFTransitionScene: Invalid transition=%@", dict);
	}
	else if (!d.name)
	{
		scene = d.scene;
	}
	else if ([d isNamed:@"TransitionScene"])
	{
		scene = [CCTransitionScene transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionSceneOriented"])
	{
		scene = [CCTransitionSceneOriented transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionRotoZoom"])
	{
		scene = [CCTransitionRotoZoom transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionJumpZoom"])
	{
		scene = [CCTransitionJumpZoom transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionMoveInL"])
	{
		scene = [CCTransitionMoveInL transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionMoveInR"])
	{
		scene = [CCTransitionMoveInR transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionMoveInT"])
	{
		scene = [CCTransitionMoveInT transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionMoveInB"])
	{
		scene = [CCTransitionMoveInB transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionSlideInL"])
	{
		scene = [CCTransitionSlideInL transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionSlideInR"])
	{
		scene = [CCTransitionSlideInR transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionSlideInB"])
	{
		scene = [CCTransitionSlideInB transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionSlideInT"])
	{
		scene = [CCTransitionSlideInT transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionShrinkGrow"])
	{
		scene = [CCTransitionShrinkGrow transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionFade"])
	{
		scene = [CCTransitionFade transitionWithDuration:d.duration scene:d.scene withColor:d.color];
	}
	else if ([d isNamed:@"TransitionCrossFade"])
	{
		scene = [CCTransitionCrossFade transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionTurnOffTiles"])
	{
		scene = [CCTransitionTurnOffTiles transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionSplitCols"])
	{
		scene = [CCTransitionSplitCols transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionSplitRows"])
	{
		scene = [CCTransitionSplitRows transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionRadialCCW"])
	{
		scene = [CCTransitionRadialCCW transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionRadialCW"])
	{
		scene = [CCTransitionRadialCW transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionFadeTR"])
	{
		scene = [CCTransitionFadeTR transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionFadeBL"])
	{
		scene = [CCTransitionFadeBL transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionFadeUp"])
	{
		scene = [CCTransitionFadeUp transitionWithDuration:d.duration scene:d.scene];
	}
	else if ([d isNamed:@"TransitionFadeDown"])
	{
		scene = [CCTransitionFadeDown transitionWithDuration:d.duration scene:d.scene];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionFlipX"])
	{
		scene = [CCTransitionFlipX transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	else if ([d isNamed:@"TransitionFlipY"])
	{
		scene = [CCTransitionFlipY transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	else if ([d isNamed:@"TransitionFlipAngular"])
	{
		scene = [CCTransitionFlipAngular transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionZoomFlipX"])
	{
		scene = [CCTransitionZoomFlipX transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	else if ([d isNamed:@"TransitionZoomFlipY"])
	{
		scene = [CCTransitionZoomFlipY transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	else if ([d isNamed:@"TransitionZoomFlipAngular"])
	{
		scene = [CCTransitionZoomFlipAngular transitionWithDuration:d.duration scene:d.scene orientation:d.orientation];
	}
	//------------------------------------------------------
	else if ([d isNamed:@"TransitionPageTurn"])
	{
		scene = [CCTransitionPageTurn transitionWithDuration:d.duration scene:d.scene backwards:d.reverse];
	}
	//------------------------------------------------------
	else
	{
		NSLog(@"SFTransitionScene: Invalid transition name '%@'!", d.name);
		scene = d.scene;
	}
	
	return scene;
}

@end
