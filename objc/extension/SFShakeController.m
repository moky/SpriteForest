//
//  SFShakeController.m
//  SpriteForest2
//
//  Created by Moky on 12-10-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFShakeController.h"

#define SF_SHAKE_UPDATE_INTERVAL 0.5f

#define SF_SHAKE_INTENSITY_MAX 1.732f
#define SF_SHAKE_INTENSITY_MIN 1.414f

#define SF_SHAKE_CHANGE_TIME 1.0f


@implementation SFShakeController

@synthesize delegate = delegate_;

// appointed initializing function
- (id) initWithInterval:(NSTimeInterval)interval minIntensity:(double)minIn maxIntensity:(double)maxIn
{
	if ((self = [super init]))
	{
		self.delegate = nil;
		isShaking_ = NO;
		minIntensity_ = minIn;
		maxIntensity_ = maxIn;
		
		UIAccelerometer * accelerometer = [UIAccelerometer sharedAccelerometer];
		accelerometer.delegate = self;
		accelerometer.updateInterval = interval;
	}
	return self;
}

- (id) init
{
	return [self initWithInterval:SF_SHAKE_UPDATE_INTERVAL
					 minIntensity:SF_SHAKE_INTENSITY_MIN
					 maxIntensity:SF_SHAKE_INTENSITY_MAX];
}

- (void) dealloc
{
	UIAccelerometer * accelerometer = [UIAccelerometer sharedAccelerometer];
	accelerometer.delegate = nil;
	
	[delegate_ release];
	
	[super dealloc];
}

#pragma mark -

- (double) accelerationIntensity:(UIAcceleration *)a
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

- (void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	time_t now;
	time(&now);
	
	int distance = (int)difftime(now, lastChangeTime_);
	double intensity = [self accelerationIntensity:acceleration];
	
	if (!isShaking_)
	{
		if (intensity > maxIntensity_ && distance > SF_SHAKE_CHANGE_TIME)
		{
			isShaking_ = YES;
			lastChangeTime_ = now;
			if ([delegate_ respondsToSelector:@selector(onShakeStart:)])
			{
				[delegate_ onShakeStart:acceleration];
			}
		}
	}
	else if (intensity < minIntensity_ && distance > SF_SHAKE_CHANGE_TIME)
	{
		if ([delegate_ respondsToSelector:@selector(onShakeEnd:)])
		{
			[delegate_ onShakeEnd:acceleration];
		}
		isShaking_ = NO;
		lastChangeTime_ = now;
	}
	else
	{
		if ([delegate_ respondsToSelector:@selector(onShake:)])
		{
			[delegate_ onShake:acceleration];
		}
	}
}

@end
