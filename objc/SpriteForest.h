//
//  SpriteForest.h
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFForest.h"

#define SF_PERFORM_FOREST_DELAY 0.001f
#define SF_HIDE_INDICATOR_DELAY 0.000f


@interface SpriteForest : SFForest

- (BOOL) performScene:(id)data;

@end


#pragma mark - Forest Lord


@interface ForestLord : NSObject
{
	SpriteForest * currentForest_;
	
	NSMutableArray * history_;
	
	// for loading indicator
	UIView * loadingView_;
	UIActivityIndicatorView * loadingIndicator_;
	NSInteger loadingIndicatorRetainCount_;
}

@property(nonatomic, retain) SpriteForest * currentForest;
@property(nonatomic, retain) NSMutableArray * history;

+ (ForestLord *) sharedLord;

+ (BOOL) forestExistsAtPath:(NSString *)path;

- (BOOL) runIntoForest:(NSString *)path;
- (BOOL) runIntoForest:(NSString *)path withScene:(id)data;
- (BOOL) performScene:(id)data;

- (BOOL) goBack;

// for loading indicator
- (void) showLoadingIndicator;
- (void) hideLoadingIndicator;

@end