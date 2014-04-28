//
//  CCMagic.h
//  SpriteForest2
//
//  Created by Moky on 12-10-30.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CCMagic : CCActionInstant<NSCopying>
{
	NSDictionary * dict_;
}

@property(nonatomic, retain) NSDictionary * dict;

/** creates the action with the callback */
+ (id) actionWithDictionary:(NSDictionary *)dict;
/** initializes the action with the callback */
- (id) initWithDictionary:(NSDictionary *)dict;
/** exeuctes the callback */
- (void) execute;

@end
