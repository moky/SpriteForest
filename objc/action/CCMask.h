//
//  CCMaskTo.h
//  SpriteForest
//
//  Created by Moky on 11-12-26.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CCMaskTo : CCActionInterval<NSCopying>
{
	CGRect endRect_;
	CGRect startRect_;
	CGRect delta_;
}

+ (id) actionWithDuration:(ccTime)duration rect:(CGRect)rect;
- (id) initWithDuration:(ccTime)duration rect:(CGRect)rect;

@end


@interface CCMaskBy : CCMaskTo

@end
