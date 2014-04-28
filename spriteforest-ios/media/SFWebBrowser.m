//
//  WebBrowser.m
//  SpriteForest2
//
//  Created by Moky on 12-10-7.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFWebBrowser.h"

#import "coconut2d.h"

@implementation SFWebBrowser

+ (void) openURL:(NSString *)urlString
{
	[CNClient openURL:[urlString dynamicURLString]];
}

+ (void) openURL:(NSString *)urlString inFrame:(CGRect)frame
{
	[self openURL:urlString inFrame:frame closeButton:SF_WEB_BROWSER_CLOSE_BUTTON];
}

+ (void) openURL:(NSString *)urlString inFrame:(CGRect)frame closeButton:(NSString *)imageFile
{
	[self close];
	
	CCDirector * director = [CCDirector sharedDirector];
	CGSize winSize = director.winSize;
	
	BOOL fullScreen = NO;
	
	// get frame
	if (CGRectEqualToRect(frame, CGRectZero))
	{
		frame = CGRectMake(0, 0, winSize.width, winSize.height);
		fullScreen = YES;
	}
	else
	{
		// scale it
		CCArray * array = [director.runningScene children];
		if ([array isKindOfClass:[CCArray class]] && [array count] > 0)
		{
			CCNode * layer = [array objectAtIndex:0];
			if ([layer isKindOfClass:[CCNode class]])
			{
				CGFloat scaleX = layer.scaleX;
				CGFloat scaleY = layer.scaleY;
				CNLog(@"scale: x = %f, y = %f", scaleX, scaleY);
				if (scaleX != 1.0f)
				{
					frame.origin.x *= scaleX;
					frame.size.width *= scaleX;
				}
				if (scaleY != 1.0f)
				{
					frame.origin.y *= scaleY;
					frame.size.height *= scaleY;
				}
			}
		}
	}
	
	CGRect bounds = CGRectMake(frame.origin.x,
							   winSize.height - (frame.origin.y + frame.size.height),
							   frame.size.width,
							   frame.size.height);
	
	// open it
	urlString = [urlString dynamicURLString];
	CNLog(@"Open Web: %@ , frame size: (%.2f, %.2f)", urlString, frame.size.width, frame.size.height);
	NSURL * url = [NSURL URLWithString:urlString];
	NSMutableURLRequest * request = [NSMutableURLRequest requestWithURL:url];
	request.cachePolicy = NSURLRequestReturnCacheDataElseLoad;
	[request addValue:NSStringFromCGSize(bounds.size) forHTTPHeaderField:@"Window-Size"];
	
	UIWebView * webView = [[UIWebView alloc] initWithFrame:bounds];
	[webView loadRequest:request];
	
	UIView * openGLView = [director openGLView];
	[openGLView addSubview:webView];
	
	// close button
	UIImage * image = [imageFile isAbsolutePath] ? [UIImage imageWithContentsOfFile:imageFile] : [UIImage imageNamed:imageFile];
	if (image)
	{
		UIButton * button = [UIButton buttonWithType:UIButtonTypeCustom];
		button.frame = CGRectMake(0, 0, image.size.width, image.size.height);
		[button setImage:image forState:UIControlStateNormal];
		[webView addSubview:button];
		[button addTarget:self action:@selector(close) forControlEvents:UIControlEventTouchUpInside];
	}
	
	if (fullScreen)
	{
		CATransition *animation = [CATransition animation];
		animation.duration = 0.2f; //动画时长
		animation.timingFunction = UIViewAnimationCurveEaseInOut;
		animation.fillMode = kCAFillModeForwards;
		animation.type = @"pageUnCurl"; //过度效果
		if ([[UIApplication sharedApplication] statusBarOrientation] == UIInterfaceOrientationLandscapeLeft)
		{
			animation.subtype = kCATransitionFromLeft;
		}
		else
		{
			animation.subtype = kCATransitionFromRight;
		}
		animation.startProgress = 0.0f; //动画开始起点(在整体动画的百分比)
		animation.endProgress = 1.0f;  //动画停止终点(在整体动画的百分比)
		animation.removedOnCompletion = NO;
		[openGLView.layer addAnimation:animation forKey:@"pageCurl"];
	}
}

+ (void) close
{
	NSArray * subViews = [[[CCDirector sharedDirector] openGLView] subviews];
	for (UIView * view in subViews)
	{
		if ([view isKindOfClass:[UIWebView class]])
		{
			[view removeFromSuperview];
		}
	}
	
	CCDirector * director = [CCDirector sharedDirector];
	UIView * openGLView = [director openGLView];
	if ([openGLView.layer.animationKeys count] > 0)
	{
		CATransition *animation = [CATransition animation];
		animation.duration = 0.2f; //动画时长
		animation.timingFunction = UIViewAnimationCurveEaseInOut;
		animation.fillMode = kCAFillModeForwards;
		animation.type = @"pageCurl"; //过度效果
		if ([[UIApplication sharedApplication] statusBarOrientation] == UIInterfaceOrientationLandscapeLeft)
		{
			animation.subtype = kCATransitionFromLeft;
		}
		else
		{
			animation.subtype = kCATransitionFromRight;
		}
		animation.startProgress = 0.0f; //动画开始起点(在整体动画的百分比)
		animation.endProgress = 1.0f;  //动画停止终点(在整体动画的百分比)
		[openGLView.layer addAnimation:animation forKey:nil];
	}
}

@end
