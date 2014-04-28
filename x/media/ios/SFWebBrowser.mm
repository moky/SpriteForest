//
//  SFWebBrowser.mm
//  SpriteForest-X
//
//  Created by Moky on 13-7-23.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#include "EAGLView.h"

#include "../SFWebBrowser.h"

@interface SFWebBrowserCloser : NSObject

@end

@implementation SFWebBrowserCloser

+ (void) close
{
	EAGLView * glView = [EAGLView sharedEGLView];
	NSArray * subViews = [glView subviews];
	for (UIView * view in subViews)
	{
		if ([view isKindOfClass:[UIWebView class]])
		{
			[view removeFromSuperview];
		}
	}
	[glView resignFirstResponder];
}

@end

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#define SF_WEB_BROWSER_CLOSE_BUTTON   "web_close.png"

bool SFWebBrowser_openURL(std::string & sURL)
{
	std::size_t pos = sURL.find(":");
	if (pos == std::string::npos)
	{
		CNLog("invalid scheme in url: [%s]", sURL.c_str());
		return false;
	}
	
	// check whether can open
	NSURL * url = [NSURL URLWithString:[NSString stringWithCString:sURL.c_str() encoding:NSUTF8StringEncoding]];
	if ([[UIApplication sharedApplication] canOpenURL:url])
	{
		CNLog("opening url: [%s]", sURL.c_str());
		[[UIApplication sharedApplication] openURL:url]; // open it!
		return YES;
	}
	
	// cannot open, try the next fragment
	CNLog("the app is not installed: [%s]", sURL.c_str());
	
	pos = sURL.find("#");
	if (pos == std::string::npos)
	{
		CNLog("no other fragment in url: %s", sURL.c_str());
		return false;
	}
	sURL = sURL.substr(pos + 1);
	
	CNLog("continue trying url: [%s]", sURL.c_str());
	return SFWebBrowser_openURL(sURL);
}


void SFWebBrowser::openURL(const char *pszURL)
{
	if (!pszURL)
	{
		CNLog("error");
		return;
	}
	std::string sURL(pszURL);
	if (CNString::isDynamicURLString(sURL))
	{
		sURL = CNString::stringByAddingClientParameters(sURL);
	}
	
	SFWebBrowser_openURL(sURL);
}

void SFWebBrowser::openURL(const char *pszURL, cocos2d::CCRect frame)
{
	openURL(pszURL, frame, SF_WEB_BROWSER_CLOSE_BUTTON);
}

void SFWebBrowser::openURL(const char *pszURL, cocos2d::CCRect frame, const char *pszButtonImage)
{
	// close();
	if (!pszURL)
	{
		CNLog("error");
		return;
	}
	std::string sURL(pszURL);
	if (CNString::isDynamicURLString(sURL))
	{
		sURL = CNString::stringByAddingClientParameters(sURL);
	}
	
	CCDirector * director = CCDirector::sharedDirector();
	CCSize winSize = director->getWinSize();
	
	bool isFullScreen = false;
	
	// get frame
	if (CCRect::CCRectEqualToRect(frame, CCRectZero))
	{
		frame = CCRectMake(0, 0, winSize.width, winSize.height);
		isFullScreen = true;
	}
	else
	{
		// TODO: scale it
	}
	
	CGRect bounds = CGRectMake(frame.origin.x,
							   winSize.height - (frame.origin.y + frame.size.height),
							   frame.size.width,
							   frame.size.height);
	NSString * urlString = [NSString stringWithCString:sURL.c_str() encoding:NSUTF8StringEncoding];
	CNLog("Open Web: %s , frame size: (%.2f, %.2f)", sURL.c_str(), frame.size.width, frame.size.height);
	
	// open it
	NSURL * url = [NSURL URLWithString:urlString];
	NSMutableURLRequest * request = [NSMutableURLRequest requestWithURL:url];
	request.cachePolicy = NSURLRequestReturnCacheDataElseLoad;
	[request addValue:NSStringFromCGSize(bounds.size) forHTTPHeaderField:@"Window-Size"];
	
	UIWebView * webView = [[[UIWebView alloc] initWithFrame:bounds] autorelease];
	webView.scalesPageToFit = YES;
	[webView loadRequest:request];
	
	UIView * openGLView = [EAGLView sharedEGLView];
	[openGLView addSubview:webView];
	
	// close button
	UIImage * image = NULL;
	if (CNString::isAbsolutePath(pszButtonImage))
	{
		NSString * imageFile = [NSString stringWithCString:pszButtonImage encoding:NSUTF8StringEncoding];
		image = [UIImage imageWithContentsOfFile:imageFile];
	}
	else
	{
		NSString * imageFile = [NSString stringWithCString:pszButtonImage encoding:NSUTF8StringEncoding];
		image = [UIImage imageNamed:imageFile];
	}
	
	if (image)
	{
		CGFloat width = image.size.width;
		CGFloat height = image.size.height;
		UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];
		[button setImage:image forState:UIControlStateNormal];
		button.bounds = CGRectMake(0, 0, width, height);
		button.center = CGPointMake(width * 0.5, height * 0.5);
		[webView addSubview:button];
		[button addTarget:[SFWebBrowserCloser class] action:@selector(close) forControlEvents:UIControlEventTouchUpInside];
	}
}

NS_SF_END
