//
//  CNScene+Touch.h
//  Coconut2D
//
//  Created by Moky on 12-11-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScene.h"

@interface CNTouchObject : NSObject
{
	int count_;
	
	int maxTouches_;
	NSMutableSet * claimedTouches_;
	id<CCTargetedTouchDelegate> delegate_;
}

@property(nonatomic, readwrite) int count;
@property(nonatomic, readwrite) int maxTouches;
@property(nonatomic, retain) NSMutableSet * claimedTouches;
@property(nonatomic, retain) id<CCTargetedTouchDelegate> delegate;

@end

@interface CNScene (Touch)

- (void) addTouchNode:(CCNode *)node withDelegate:(id<CCTargetedTouchDelegate>)delegate;
- (void) addTouchNode:(CCNode *)node withDelegate:(id<CCTargetedTouchDelegate>)delegate maxTouches:(int)count;
- (void) removeTouchNode:(CCNode *)node;

@end
