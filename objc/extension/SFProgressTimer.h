//
//  SFProgressTimer.h
//  SpriteForest2
//
//  Created by Moky on 12-10-8.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFSprite.h"


@interface SFProgressTimer : SFSprite
{
	CCSprite * snapshot_;
	CCProgressTimer * mask_;
	CCProgressTimerType type_;
	
	NSString * target_;
}

@property(nonatomic, retain) CCSprite * snapshot;
@property(nonatomic, retain) CCProgressTimer * mask;
@property(nonatomic, readwrite) CCProgressTimerType type;
@property(nonatomic, retain) NSString * target;

- (void) setTypeByString:(NSString *)type;

@end


#pragma mark - avoid crash caused by 'ProgressTo/FromTo' action


@interface CCNode (ProgressTimer)

- (void) setPercentage:(float)percentage;

@end
