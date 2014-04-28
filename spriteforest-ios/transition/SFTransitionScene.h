//
//  SFTransitionScene.h
//  SpriteForest
//
//  Created by Moky on 11-12-28.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"


#pragma mark TransitionScene

@interface SFTransitionScene : NSObject
{
	NSString * name_;
	
	// value
	CCScene * scene_;
	CGFloat duration_;
	tOrientation orientation_;
	ccColor3B color_;
	BOOL reverse_;
}

#pragma mark -
#pragma mark Properties for TransitionScene

@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) CCScene * scene;
@property (nonatomic, readwrite) CGFloat duration;
@property (nonatomic, readwrite) tOrientation orientation;
@property (nonatomic, readwrite) ccColor3B color;
@property (nonatomic, readwrite) BOOL reverse;

+ (SFTransitionScene *) dict:(NSDictionary *)dict;
- (SFTransitionScene *) initWithDict:(NSDictionary *)dict;

- (BOOL) isNamed:(NSString *)name;

#pragma mark -
#pragma mark Interface method

+ (CCScene *) transitionScene:(NSDictionary *)dict;
/*
#pragma mark -
#pragma mark Inherited from TransitionScene

+ (CCTransitionSceneOriented *) transitionSceneOriented:(NSDictionary *)dict;

+ (CCTransitionRotoZoom *) transitionRotoZoom:(NSDictionary *)dict;
+ (CCTransitionJumpZoom *) transitionJumpZoom:(NSDictionary *)dict;

+ (CCTransitionMoveInL *) transitionMoveInL:(NSDictionary *)dict;
+ (CCTransitionMoveInR *) transitionMoveInR:(NSDictionary *)dict;
+ (CCTransitionMoveInT *) transitionMoveInT:(NSDictionary *)dict;
+ (CCTransitionMoveInB *) transitionMoveInB:(NSDictionary *)dict;

+ (CCTransitionSlideInL *) transitionSlideInL:(NSDictionary *)dict;
+ (CCTransitionSlideInR *) transitionSlideInR:(NSDictionary *)dict;
+ (CCTransitionSlideInB *) transitionSlideInB:(NSDictionary *)dict;
+ (CCTransitionSlideInT *) transitionSlideInT:(NSDictionary *)dict;

+ (CCTransitionShrinkGrow *) transitionShrinkGrow:(NSDictionary *)dict;

+ (CCTransitionFade *) transitionFade:(NSDictionary *)dict;
+ (CCTransitionCrossFade *) transitionCrossFade:(NSDictionary *)dict;
+ (CCTransitionTurnOffTiles *) transitionTurnOffTiles:(NSDictionary *)dict;

+ (CCTransitionSplitCols *) transitionSplitCols:(NSDictionary *)dict;
+ (CCTransitionSplitRows *) transitionSplitRows:(NSDictionary *)dict;

+ (CCTransitionFadeTR *) transitionFadeTR:(NSDictionary *)dict;
+ (CCTransitionFadeBL *) transitionFadeBL:(NSDictionary *)dict;
+ (CCTransitionFadeUp *) transitionFadeUp:(NSDictionary *)dict;
+ (CCTransitionFadeDown *) transitionFadeDown:(NSDictionary *)dict;

#pragma mark -
#pragma mark Inherited from TransitionSceneOriented

+ (CCTransitionFlipX *) transitionFlipX:(NSDictionary *)dict;
+ (CCTransitionFlipY *) transitionFlipY:(NSDictionary *)dict;
+ (CCTransitionFlipAngular *) transitionFlipAngular:(NSDictionary *)dict;
+ (CCTransitionZoomFlipX *) transitionZoomFlipX:(NSDictionary *)dict;
+ (CCTransitionZoomFlipY *) transitionZoomFlipY:(NSDictionary *)dict;
+ (CCTransitionZoomFlipAngular *) transitionZoomFlipAngular:(NSDictionary *)dict;
*/
@end
