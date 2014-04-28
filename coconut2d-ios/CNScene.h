//
//  CNScene.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNScene : CCScene<CCStandardTouchDelegate>
{
	NSMutableDictionary * touchNodes_;
	NSMutableSet * allClaimedKeys_;
}

// CCDirector: runWithScene or replaceScene
+ (void) perform:(CCScene *)scene;
- (void) perform;	// perform self

+ (UIImage *) snapshot;	// get snapshot image
- (void) snapshot;	// save snapshot image into the photos album

@end
