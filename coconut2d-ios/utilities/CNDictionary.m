//
//  CNDictionary.m
//  Coconut2D
//
//  Created by Moky on 12-7-15.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNDictionary.h"

#import "CNString.h"


@implementation NSDictionary (CaseInsensitive)

- (id) objectForKeyCaseInsensitive:(NSString *)key
{
	id value = [self objectForKey:key];
	
	// shift capitalized key
	if (!value)	value = [self objectForKey:[key shiftCapitalizedString]];
	
	// lowercase key
	if (!value) value = [self objectForKey:[key lowercaseString]];
	
	// uppercase key
	if (!value) value = [self objectForKey:[key uppercaseString]];
	
	return value;
}

@end
