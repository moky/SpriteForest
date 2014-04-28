//
//  SFVideo.mm
//  SpriteForest-X
//
//  Created by Moky on 13-7-30.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
#include "EAGLView.h"
#include "coconut2d.h"

USING_NS_CC;

@interface VideoPlayer : NSObject

+ (void) initPlayerWithFrame:(CGRect)frame;
+ (void) playMovie:(NSString *)filename;
+ (void) stopMovie;

+ (void) moviePlayBackDidFinish:(NSNotification *) notification;

@end

@implementation VideoPlayer

static MPMoviePlayerController * s_pSharedMoviePlayer = NULL;

+ (void) initPlayerWithFrame:(CGRect)frame
{
	if (!s_pSharedMoviePlayer)
	{
		s_pSharedMoviePlayer = [[MPMoviePlayerController alloc] init];
		s_pSharedMoviePlayer.controlStyle = MPMovieControlStyleNone;
		s_pSharedMoviePlayer.fullscreen = YES;
		s_pSharedMoviePlayer.shouldAutoplay = YES;
		s_pSharedMoviePlayer.scalingMode = MPMovieScalingModeAspectFit;
		s_pSharedMoviePlayer.movieSourceType = MPMovieSourceTypeFile;
		
		s_pSharedMoviePlayer.view.backgroundColor = [UIColor blackColor];
	}
	
	[s_pSharedMoviePlayer.view setHidden:YES];
	
	CNLog("video player at: {{%.2f, %.2f}, {%.2f, %.2f}}", frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
	s_pSharedMoviePlayer.view.frame = frame;
}

+ (void) playMovie:(NSString *)filename
{
	[self stopMovie];
	
	// addObserver
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(moviePlayBackDidFinish:)
												 name:MPMoviePlayerPlaybackDidFinishNotification
											   object:nil];
	
	
	if (!s_pSharedMoviePlayer)
	{
		[self initPlayerWithFrame:[[UIScreen mainScreen] bounds]];
	}
	
	if (![s_pSharedMoviePlayer.view superview])
	{
		UIView * view = [[EAGLView sharedEGLView] superview];
		if (!view)
		{
			view = [EAGLView sharedEGLView];
		}
		[view addSubview:s_pSharedMoviePlayer.view];
	}
	[s_pSharedMoviePlayer.view setHidden:NO];
	s_pSharedMoviePlayer.contentURL = [NSURL fileURLWithPath:filename];
	[s_pSharedMoviePlayer prepareToPlay];
	[s_pSharedMoviePlayer play];
	CNLog("playing movie: %s", [filename cStringUsingEncoding:NSUTF8StringEncoding]);
}

+ (void) stopMovie
{
	// removeObserver
	[[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:nil];
	
	if (!s_pSharedMoviePlayer)
	{
		return;
	}
	if ([s_pSharedMoviePlayer playbackState] == MPMoviePlaybackStatePlaying)
	{
		[s_pSharedMoviePlayer stop];
	}
	
	[s_pSharedMoviePlayer.view setHidden:YES];
//	[s_pSharedMoviePlayer.view removeFromSuperview];
//	
//	[s_pSharedMoviePlayer release];
//	s_pSharedMoviePlayer = NULL;
}

+ (void) moviePlayBackDidFinish:(NSNotification *)notification
{
	[self stopMovie];
	CNLog("DONE");
}

@end

void SFVideo_initPlayer(const float x, const float y, const float width, const float height)
{
	CNLog("video player at: {{%.2f, %.2f}, {%.2f, %.2f}}", x, y, width, height);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int y_ = winSize.height - y - height;
	CGRect frame = CGRectMake(x, y_, width, height);
	[VideoPlayer initPlayerWithFrame:frame];
}

void SFVideo_playMovie(const char * pszFile)
{
	if (!pszFile || strlen(pszFile) == 0)
	{
		return;
	}
	[VideoPlayer playMovie:[NSString stringWithCString:pszFile encoding:NSUTF8StringEncoding]];
}

void SFVideo_stopMovie(void)
{
	[VideoPlayer stopMovie];
}
