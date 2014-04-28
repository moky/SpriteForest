//
//  CNTouchController.h
//  Coconut2D
//
//  Created by Moky on 12-11-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"


/**
 *  convert cocos2d touch events to mouse-kind (finger) events
 */
@protocol CNTouchDelegate<NSObject>

@optional

//---- buttons
- (void) onFingerDown:(CCNode *)node;
- (void) onFingerUp:(CCNode *)node;
- (void) onFingerOver:(CCNode *)node;
- (void) onFingerOut:(CCNode *)node;
- (void) onFingerMove:(CCNode *)node;

- (void) onClick:(CCNode *)node;
- (void) onDoubleClick:(CCNode *)node;	// 慎用

//---- guestures
- (void) onSwipeLeft:(CCNode *)node;
- (void) onSwipeRight:(CCNode *)node;
- (void) onSwipeUp:(CCNode *)node;
- (void) onSwipeDown:(CCNode *)node;

@end


@protocol CNDragDelegate <NSObject>

@optional

//---- drag
// 如果当前条件下不允许拖放，则返回 NO；默认返回 YES
- (BOOL) onDragStart:(CCNode *)node;
// 如果到达了边界需要禁止移动，则返回 NO；默认返回 YES
- (BOOL) onDrag:(CCNode *)node;
// 如果松手后需要复原位置，则返回 NO；默认返回 YES
- (BOOL) onDragEnd:(CCNode *)node;

@end


typedef enum {
	kTouchNodeNormal,
	kTouchNodeActive,
} CNTouchStatus;


@interface CNTouchController : NSObject<CCTargetedTouchDelegate>
{
	CCNode * node_;
	id delegate_;
	
	CGPoint touchBeganPoint_;
	CGPoint touchPoint_;
	CGPoint touchEndedPoint_;
	
	CNTouchStatus status_;
	
	BOOL dragEnabled_;
	CGPoint originalPosition_; // save drag start position
}

@property(nonatomic, retain) CCNode * node;
@property(nonatomic, retain) id delegate;

@property(nonatomic, readwrite) CGPoint touchBeganPoint;
@property(nonatomic, readwrite) CGPoint touchPoint;
@property(nonatomic, readwrite) CGPoint touchEndedPoint;

@property(nonatomic, readwrite) BOOL dragEnabled;

@end
