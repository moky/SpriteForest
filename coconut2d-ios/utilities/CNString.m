//
//  CNString.m
//  Coconut2D
//
//  Created by Moky on 12-7-15.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNString.h"

#import "CNClient.h"


@implementation NSString (Capitalized)

- (NSString *) capitalizedString
{
	if ([self length] <= 0)
	{
		return self;
	}
	unichar c = [self characterAtIndex:0];
	if (c >= 'a' && c <= 'z')
	{
		c += 'A' - 'a';
	}
	else
	{
		return self;
	}
	return [NSString stringWithFormat:@"%c%@", c, [self substringFromIndex:1]];
}

- (NSString *) uncapitalizedString
{
	if ([self length] <= 0)
	{
		return self;
	}
	unichar c = [self characterAtIndex:0];
	if (c >= 'A' && c <= 'Z')
	{
		c -= 'A' - 'a';
	}
	else
	{
		return self;
	}
	return [NSString stringWithFormat:@"%c%@", c, [self substringFromIndex:1]];
}

- (NSString *) shiftCapitalizedString
{
	if ([self length] <= 0)
	{
		return self;
	}
	unichar c = [self characterAtIndex:0];
	if (c >= 'a' && c <= 'z')
	{
		c += 'A' - 'a';
	}
	else if (c >= 'A' && c <= 'Z')
	{
		c -= 'A' - 'a';
	}
	else
	{
		return self;
	}
	return [NSString stringWithFormat:@"%c%@", c, [self substringFromIndex:1]];
}

@end


@implementation NSString (URLRequest)

+ (NSString *) parameterValueForKey:(NSString *)name withURL:(NSURL *)url
{
	if (![name isKindOfClass:[NSString class]])
	{
		return nil;
	}
	if (![url isKindOfClass:[NSURL class]])
	{
		return nil;
	}
	
	NSString * query = [url query];
	if ([query isKindOfClass:[NSString class]])
	{
		NSArray * pairs = [query componentsSeparatedByString:@"&"];
		for (NSString * pair in pairs)
		{
			NSRange range = [pair rangeOfString:@"="];
			if (range.location == NSNotFound)
			{
				continue;
			}
			NSString * key = [pair substringToIndex:range.location];
			if ([name caseInsensitiveCompare:key] == NSOrderedSame)
			{
				NSString * value = [pair substringFromIndex:range.location+1];
				return [value stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
			}
		}
	}
	return nil;
}

- (NSString *) parameterValueForKey:(NSString *)name
{
	NSURL * url = [NSURL URLWithString:self];
	return [[self class] parameterValueForKey:name withURL:url];
}


- (NSString *) stringByAppendingClientParameters
{
	NSString * clientParameters = [CNClient getClientParameters];
	// check whether already append
	NSRange range = [self rangeOfString:clientParameters];
	if (range.location != NSNotFound)
	{
		return self;
	}
	
	NSString * urlString = nil;
	NSString * fragment = nil;
	
	// save fragment
	range = [self rangeOfString:@"#"];
	if (range.location != NSNotFound)
	{
		urlString = [self substringToIndex:range.location];
		fragment = [self substringFromIndex:range.location + 1];
	}
	else
	{
		urlString = self;
	}
	
	// append client paramegers
	range = [urlString rangeOfString:@"?"];
	if (range.location != NSNotFound)
	{
		urlString = [urlString stringByAppendingFormat:@"&%@", clientParameters];
	}
	else
	{
		urlString = [urlString stringByAppendingFormat:@"?%@", clientParameters];
	}
	
	// append fragment
	if (fragment)
	{
		urlString = [urlString stringByAppendingFormat:@"#%@", fragment];
	}
	
	return urlString;
}

- (BOOL) isDynamicURLString
{
	NSString * lowercaseString = [self lowercaseString];
	if ([lowercaseString hasPrefix:@"file://"])
	{
		return NO;
	}
	if ([lowercaseString hasPrefix:@"/"])
	{
		return NO;
	}
	NSRange range = [lowercaseString rangeOfString:@"://"];
	if (range.location == NSNotFound)
	{
		return NO;
	}
	
	range = [lowercaseString rangeOfString:@"cgi-bin"];
	if (range.location == NSNotFound)
	{
		return NO;
	}
	
	return YES;
}

- (NSString *) dynamicURLString
{
	if ([self isDynamicURLString])
	{
		return [self stringByAppendingClientParameters];
	}
	else
	{
		return self;
	}
}

@end