//
//  SFNode.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFNode.h"

#import "SFScene.h"
#import "SFLayer.h"
#import "SFSprite.h"

@implementation CCNode (SpriteForest)

+ (id) nodeWithString:(NSString *)string
{
	if (![string isKindOfClass:[NSString class]])
	{
		CNLog(@"parameter error: %@", string);
		return nil;
	}
	
	NSString * className = [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	if ([[className lowercaseString] hasPrefix:@"include class=\""])
	{
		className = [className substringFromIndex:15];
		NSRange range = [className rangeOfString:@"\""];
		if (range.location == NSNotFound)
		{
			CNLog(@"parse error, string = %@", string);
			return nil;
		}
		range.length = range.location;
		range.location = 0;
		className = [className substringWithRange:range];
	}
	
	Class class = NSClassFromString(className);
	if (![class isSubclassOfClass:[CCNode class]])
	{
		CNLog(@"'%@' is NOT a sub class of 'CCNode', string = %@", className, string);
		return nil;
	}
	
	return [[[class alloc] init] autorelease];
}

+ (id) nodeWithDictionary:(NSDictionary *)dict
{
	if (![dict isKindOfClass:[NSDictionary class]])
	{
		CNLog(@"parameter error: %@", dict);
		return nil;
	}
	
	Class class = self;
	
	NSString * className = [dict objectForKey:@"Class"];
	if ([className isKindOfClass:[NSString class]])
	{
		class = NSClassFromString(className);
		if (![class isSubclassOfClass:[CCNode class]])
		{
			CNLog(@"'%@' is NOT a sub class of 'CCNode', dict = %@", className, dict);
			return nil;
		}
	}
	
	id node = [class alloc];
	
	if ([node respondsToSelector:@selector(initWithDictionary:)])
	{
		return [[node initWithDictionary:dict] autorelease];
	}
	else
	{
		return [[node init] autorelease];
	}
}

#pragma mark -

- (void) addChildren:(NSArray *)array type:(NSInteger)spriteOrLayer
{
	CCNode * node;
	NSInteger zOrder;
	
	for (id data in array)
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		node = nil;
		zOrder = 0;
		
        if ([data isKindOfClass:[NSString class]])
        {
            NSString * string = (NSString *)data;
			node = [CCNode nodeWithString:string];
			CNLog(@"node from a string: %@", string);
        }
		else if ([data isKindOfClass:[NSDictionary class]])
		{
			NSDictionary * dict = (NSDictionary *)data;
			node = (spriteOrLayer == 0) ? [SFSprite nodeWithDictionary:dict] : [SFLayer nodeWithDictionary:dict];
			zOrder = [[dict objectForKey:@"ZOrder"] intValue];
		}
		else
		{
			CNLog(@"unrecongnized node, data = %@", data);
			[pool release];
			continue;
		}
		
		if ([node isKindOfClass:[CCNode class]])
		{
			[self addChild:node z:zOrder];
		}
		[pool release];
	} // EOF 'for (id data in array)'
}

- (void) addSprites:(NSArray *)array
{
	if ([array isKindOfClass:[NSArray class]])
	{
		[self addChildren:array type:0];
	}
}

- (void) addLayers:(NSArray *)array
{
	if ([array isKindOfClass:[NSArray class]])
	{
		[self addChildren:array type:1];
	}
}

#pragma mark - Target

- (id) getTarget:(NSString *)target
{
	if (target == nil)
	{
		return self;
	}
	else if ([target isKindOfClass:[CCNode class]])
	{
		return target;
	}
	else if (![target isKindOfClass:[NSString class]])
	{
		CNLog(@"could not happen!");
		return nil;
	}
	else if ([target length] == 0)
	{
		return self;
	}
	
	// target by format: xxx.xxx.xxx
	NSRange range = [target rangeOfString:@"."];
	if (range.location != NSNotFound)
	{
		NSInteger index = range.location;
		NSString * str1 = [target substringToIndex:index];
		index++;
		NSString * str2 = [target substringFromIndex:index];
		return [[self getTarget:str1] getTarget:str2];
	}
	
	// target by simple name/tag
	if ([target caseInsensitiveCompare:@"scene"] == NSOrderedSame)
	{
		return [self scene];
	}
	else if ([target caseInsensitiveCompare:@"self"] == NSOrderedSame)
	{
		return self;
	}
	else if ([target caseInsensitiveCompare:@"parent"] == NSOrderedSame)
	{
		return self.parent;
	}
	else
	{
		// children sprite
		NSInteger tag = [target intValue];
		CCNode * child;
		CCARRAY_FOREACH([self children], child)
		{
			if (child.tag == tag)
			{
				return child;
			}
		}
	}
	
	CNLog(@"no such target: %@", target);
	return nil;
}

@end
