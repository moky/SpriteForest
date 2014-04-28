//
//  SFShakeController.h
//  SpriteForest2
//
//  Created by Moky on 12-10-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol SFShakeDelegate <NSObject>

@optional

- (void) onShakeStart:(UIAcceleration *)acceleration;
- (void) onShake:(UIAcceleration *)acceleration;
- (void) onShakeEnd:(UIAcceleration *)acceleration;

@end



@interface SFShakeController : NSObject<UIAccelerometerDelegate>
{
	id<SFShakeDelegate> delegate_;
	
@protected
	BOOL isShaking_;
	time_t lastChangeTime_;
	
	double minIntensity_;
	double maxIntensity_;
}

@property(nonatomic, retain) id<SFShakeDelegate> delegate;

// appointed initializing function
- (id) initWithInterval:(NSTimeInterval)interval minIntensity:(double)minIn maxIntensity:(double)maxIn;

@end
