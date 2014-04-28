//
//  SFEventHandler.h
//  SpriteForest2
//
//  Created by Moky on 12-9-30.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "coconut2d.h"


@protocol SFEventDelegate <NSObject>

- (BOOL) doEvent:(NSString *)event node:(CCNode *)node;
- (BOOL) doAction:(NSString *)action node:(CCNode *)node;

@end

@interface SFEventHandler : NSObject<SFEventDelegate>
{
	NSDictionary * eventTree_;
	NSDictionary * actionTree_;
}

@property(nonatomic, retain) NSDictionary * eventTree;
@property(nonatomic, retain) NSDictionary * actionTree;

+ (id) handlerWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree;

- (id) initWithEventTree:(NSDictionary *)eTree actionTree:(NSDictionary *)aTree;
- (id) init;

@end
