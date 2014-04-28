//
//  SFAction.h
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"


@interface SFAction : NSObject

+ (id) getInstance:(NSDictionary *)dict;

- (id) initWithDictionary:(NSDictionary *)dict;
- (CCAction *) ccAction;

+ (CCAction *) subActionFromDictionary:(NSDictionary *)dict;
+ (NSArray *) subActionsFromDictionary:(NSDictionary *)dict;

@end


#pragma mark -


@interface SFFiniteTimeAction : SFAction
{
	ccTime duration_;
}

@end


@interface SFRepeatForever : SFAction
{
	CCActionInterval * action_;
}
@property(nonatomic, retain) CCActionInterval * action;

@end


@interface SFSpeed : SFAction
{
	CCActionInterval * action_;
	CGFloat rate_;
}
@property(nonatomic, retain) CCActionInterval * action;

@end


@interface SFFollow : SFAction
{
	id target_;
	id followedNode_;
	CGRect rect_;
}
@property(nonatomic, readwrite, retain) id target;
@property(nonatomic, readwrite, retain) id followedNode;
@property(nonatomic, readwrite) CGRect rect;

@end

