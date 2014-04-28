//
//  CNScrollLayer.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNFiniteLayer.h"

#import "CNScrollLayerController.h"

@interface CNScrollLayer : CNFiniteLayer
{
	CNScrollLayerController * scrollController_;
}

@end
