//
//  SFSprite.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFSprite.h"

#import "SFScene.h"


@implementation SFSprite

@synthesize textures = textures_;
@synthesize eventHandler = eventHandler_;

+ (id) nodeWithDictionary:(NSDictionary *)dict
{
	NSString * className = [dict objectForKey:@"Class"];
	if (![className isKindOfClass:[NSString class]])
	{
		dict = [NSMutableDictionary dictionaryWithDictionary:dict];
		// extend touch sprite
		if ([[dict objectForKey:@"TouchEnabled"] boolValue])
		{
			[(NSMutableDictionary *)dict setObject:@"SFTouchSprite" forKey:@"Class"];
		}
		// extend drag sprite
		else if ([[dict objectForKey:@"DragEnabled"] boolValue])
		{
			[(NSMutableDictionary *)dict setObject:@"SFDragSprite" forKey:@"Class"];
		}
	}
	return [super nodeWithDictionary:dict];
}

- (id) initWithDictionary:(NSDictionary *)dict
{
	if ((self = [super initWithDictionary:dict])) 
	{
		NSDictionary * eTree = [dict objectForKey:@"EventTree"];
		NSDictionary * aTree = [dict objectForKey:@"ActionTree"];
		[self appointHandlerWithEventTree:eTree actionTree:aTree];
		
		// load textures
		NSArray * textures = [dict objectForKey:@"Textures"];
		if ([textures isKindOfClass:[NSArray class]])
		{
			self.textures = [SFScene loadTextures:textures];
		}
		
		// create sub layers
		// WARNING: For simplify reason, I hope you should never use it! -- Moky @ 2012.10.08
		NSArray * layers = [dict objectForKey:@"Layers"];
		[self addLayers:layers];
		
		// create sub sprites
		NSArray * sprites = [dict objectForKey:@"Sprites"];
		[self addSprites:sprites];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.textures = nil;
		self.eventHandler = nil;
	}
	return self;
}

- (void) dealloc
{
	self.textures = nil;
	[eventHandler_ release];
	
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

#pragma  mark -

- (void) appointHandlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree
{
	SFEventHandler * handler = [SFEventHandler handlerWithEventTree:eTree actionTree:aTree];
	self.eventHandler = handler;
}

- (void) onEnter
{
	[super onEnter];
	
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[eventHandler_ doEvent:@"onEnter" node:self];
	[pool release];
}

- (void) onEnterTransitionDidFinish
{
	[super onEnterTransitionDidFinish];
	
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[eventHandler_ doEvent:@"onEnterTransitionDidFinish" node:self];
	[pool release];
}

- (void) onExit
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[eventHandler_ doEvent:@"onExit" node:self];
	[pool release];
	
	[super onExit];
}

//#pragma mark - test
//
//- (void) draw
//{
//	[super draw];
//	
//	if (border_ > 0)
//	{
//		CGFloat width = self.contentSize.width;
//		CGFloat height = self.contentSize.height;
//		
//		CGPoint pBL = ccp(0, 0);
//		CGPoint pTL = ccp(0, height);
//		CGPoint pTR = ccp(width, height);
//		CGPoint pBR = ccp(width, 0);
//		
//		glColor4ub(255, 255, 255, 255);
//		glLineWidth(border_);
//		//glEnable(GL_LINE_SMOOTH);
//		
//		ccDrawLine(pBL, pTL);
//		ccDrawLine(pTL, pTR);
//		ccDrawLine(pTR, pBR);
//		ccDrawLine(pBR, pBL);
//		
//		CGPoint aPoint = ccp(width * anchorPoint_.x, height * anchorPoint_.y);
//		CGPoint dX = ccp(10, 0);
//		CGPoint dY = ccp(0, 10);
//		ccDrawLine(ccpSub(aPoint, dX), ccpAdd(aPoint, dX));
//		ccDrawLine(ccpSub(aPoint, dY), ccpAdd(aPoint, dY));
//	}
//}

@end
