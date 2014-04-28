//
//  CNSpriteBatchNode.h
//  Coconut2D
//
//  Created by Moky on 12-10-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"

@interface CNSpriteBatchNode : CCSpriteBatchNode

+ (id) batchNodeWithFile:(NSString *)fileImage;

- (id) initWithFile:(NSString *)fileImage;

@end
