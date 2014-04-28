//
//  CNClient.m
//  Coconut2D
//
//  Created by Moky on 12-10-29.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <ifaddrs.h>

#import "CNClient.h"

#import "cnMacros.h"

@implementation CNClient

+ (CGSize) getScreenSize
{
	CGRect rect = [[UIScreen mainScreen] bounds];
	return rect.size;
}

+ (CGFloat) getScreenScale
{
	UIScreen * screen = [UIScreen mainScreen];
	if ([screen respondsToSelector:@selector(scale)])
	{
		return [screen scale];
	}
	else
	{
		return 1.0f;
	}
}

+ (CGSize) getWindowSize
{
	CGRect rect = [[UIScreen mainScreen] applicationFrame];
	return rect.size;
}

+ (NSString *) getHardware
{
	size_t size;
	sysctlbyname("hw.machine", NULL, &size, NULL, 0);
	char * machine = malloc(size);
	sysctlbyname("hw.machine", machine, &size, NULL, 0);
	NSString * platform = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
	free(machine);
	return platform;
}

+ (NSString *) getDeviceIdentifier
{
	return [[UIDevice currentDevice] uniqueIdentifier];
}

+ (NSString *) getDeviceModel
{
	return [[UIDevice currentDevice] model];
}

+ (NSString *) getSystemName
{
	return [[UIDevice currentDevice] systemName];
}

+ (NSString *) getSystemVersion
{
	return [[UIDevice currentDevice] systemVersion];
}

+ (NSString *) getBundleVersion
{
	return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
}

+ (void) disableIdleTimer
{
	[[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

#pragma mark -

+ (NSString *) getClientParameters
{
	// client-version
	NSString * clientVersion = [self getBundleVersion];
	// imei
	NSString * imei = [self getDeviceIdentifier];
	// device
	NSString * model = [self getDeviceModel];
	NSString * hardware = [self getHardware];
	NSString * device = [NSString stringWithFormat:@"%@/%@",
						 [model stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding],
						 [hardware stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
	// os
	NSString * systemName = [self getSystemName];
	NSString * systemVersion = [self getSystemVersion];
	NSString * os = [NSString stringWithFormat:@"%@/%@",
					 [systemName stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding],
					 [systemVersion stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
	// screen
	CGSize size = [self getScreenSize];
	CGFloat scale = [self getScreenScale];
	NSString * screen = [NSString stringWithFormat:@"%.0fx%.0f@%.1f",
						 size.width, size.height, scale];
	
	return [NSString stringWithFormat:@"client-version=%@&screen=%@&os=%@&device=%@&imei=%@",
			clientVersion, screen, os, device, imei];
}

+ (BOOL) openURL:(NSString *)urlString
{
	if (![urlString isKindOfClass:[NSString class]])
	{
		CNLog(@"invalid url: %@", urlString);
		return NO;
	}
	
	NSRange range;
	range = [urlString rangeOfString:@":"];
	if (range.location == NSNotFound)
	{
		CNLog(@"invalid scheme in url: %@", urlString);
		return NO;
	}
	
	// check whether can open
	NSURL * url = [NSURL URLWithString:urlString];
	if ([[UIApplication sharedApplication] canOpenURL:url])
	{
		CNLog(@"opening url: [%@]", urlString);
		[[UIApplication sharedApplication] openURL:url]; // open it!
		return YES;
	}
	
	// cannot open, try the next fragment
	CNLog(@"the app is not installed, url = %@", urlString);
	range = [urlString rangeOfString:@"#"];
	if (range.location == NSNotFound)
	{
		CNLog(@"no other fragment in url: %@", urlString);
		return NO;
	}
	urlString = [urlString substringFromIndex:range.location+1];
	
	CNLog(@"continue trying url: %@", urlString);
	return [self openURL:urlString];
}


@end
