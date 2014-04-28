//
//  CNScrollLayerController.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNTouchController.h"

@interface CNScrollLayerController : CNTouchController
{
	CCAction * currentAction_;
	
	CGPoint swingBeganPoint_;
	clock_t swingBeganTime_;
}

@end
