//
//  SFActionProgressTimer.h
//  SpriteForest2
//
//  Created by Moky on 12-10-2.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFActionInterval.h"


@interface SFProgressTo : SFActionInterval
{
	CGFloat percent_;
}

@end


@interface SFProgressFromTo : SFActionInterval
{
	CGFloat fromPercent_;
	CGFloat toPercent_;
}

@end

