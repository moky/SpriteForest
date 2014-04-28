//
//  SFAudio.m
//  SpriteForest
//
//  Created by Moky on 11-12-28.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "SFAudio.h"

#import "SimpleAudioEngine.h"


@implementation SFAudio

+ (BOOL) perform:(NSDictionary *)dict
{
	if (![dict isKindOfClass:[NSDictionary class]])
	{
		NSLog(@"SFAudio: Invalid audio=%@", dict);
		return NO;
	}
	
	NSString * filename = (NSString *)[dict objectForKey:@"File"];
	NSString * task = (NSString *)[dict objectForKey:@"Task"];
	NSLog(@"SFAudio: ******************************** %@", task);
	
	// background music
	if (!task)
	{
		NSLog(@"SFAudio: Invalid audio task=%@", dict);
		return NO;
	}
	else if ([task caseInsensitiveCompare:@"preloadBackgroundMusic"] == NSOrderedSame)
	{
		if (![[NSFileManager defaultManager] fileExistsAtPath:filename])
		{
			NSLog(@"SFAudio: Invalid audio task=%@", dict);
			return NO;
		}
		[[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:filename];
	}
	else if ([task caseInsensitiveCompare:@"playBackgroundMusic"] == NSOrderedSame)
	{
		if (![[NSFileManager defaultManager] fileExistsAtPath:filename])
		{
			NSLog(@"SFAudio: Invalid audio task=%@", dict);
			return NO;
		}
		NSInteger loop = [[dict objectForKey:@"Loop"] intValue];
       
            [[SimpleAudioEngine sharedEngine] playBackgroundMusic:filename loop:loop];
        
	}
	else if ([task caseInsensitiveCompare:@"stopBackgroundMusic"] == NSOrderedSame)
	{
		[[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
	}
	else if ([task caseInsensitiveCompare:@"pauseBackgroundMusic"] == NSOrderedSame)
	{
		[[SimpleAudioEngine sharedEngine] pauseBackgroundMusic];
	}
	else if ([task caseInsensitiveCompare:@"resumeBackgroundMusic"] == NSOrderedSame)
	{
		[[SimpleAudioEngine sharedEngine] resumeBackgroundMusic];
	}
	else if ([task caseInsensitiveCompare:@"rewindBackgroundMusic"] == NSOrderedSame)
	{
		[[SimpleAudioEngine sharedEngine] rewindBackgroundMusic];
	}
	// effect
	else if ([task caseInsensitiveCompare:@"preloadEffect"] == NSOrderedSame)
	{
		if (![[NSFileManager defaultManager] fileExistsAtPath:filename])
		{
			NSLog(@"SFAudio: Invalid audio task=%@", dict);
			return NO;
		}
		[[SimpleAudioEngine sharedEngine] preloadEffect:filename];
	}
	else if ([task caseInsensitiveCompare:@"playEffect"] == NSOrderedSame)
	{
		if (![[NSFileManager defaultManager] fileExistsAtPath:filename])
		{
			NSLog(@"SFAudio: Invalid audio task=%@", dict);
			return NO;
		}
		[[SimpleAudioEngine sharedEngine] playEffect:filename];
	}
	else
	{
		NSLog(@"SFAudio: Unknown task '%@'", task);
		return NO;
	}
	
	return YES;
}

+ (void) stopAll
{
    if ([[SimpleAudioEngine sharedEngine] isBackgroundMusicPlaying])
	{
        [[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
    }
}

@end
