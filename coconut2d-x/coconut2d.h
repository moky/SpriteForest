//
//  coconut2d.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-21.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_coconut2d_h
#define Coconut2D_X_coconut2d_h

#include "cnMacros.h"
#include "CNDirector.h"
#include "CNNode.h"
#include "CNScene.h"
// cocoa extensions
#include "cocoa/CNSelector.h"
#include "cocoa/CNString.h"
#include "cocoa/CNDictionary.h"
#include "cocoa/CNArray.h"
#include "cocoa/CNRuntimeClass.h"
#include "cocoa/CNFileManager.h"
#include "cocoa/CNClient.h"
// actions
#include "actions/CCMask.h"
// controllers
#include "controllers/CNTouchDelegate.h"
#include "controllers/CNTouchController.h"
#include "controllers/CNScrollLayerController.h"
// sprites
#include "sprites/CNSprite.h"
#include "sprites/CNSpriteBatchNode.h"
#include "sprites/CNLabel.h"
// layers
#include "layers/CNFiniteLayer.h"
#include "layers/CNLayer.h"
#include "layers/CNScrollLayer.h"
// sprite frame cache
#include "sfc/CNSpriteFrameData.h"
#include "sfc/CNSpriteFrameDataReader.h"
#include "sfc/CNSpriteFrameDataTransformer.h"
#include "sfc/CNSpriteFrameCache.h"
// data ( plist binary file )
#include "data/CNData.h"
#include "data/CNDataReader.h"
#include "data/CNDataTransformer.h"

NS_CN_BEGIN

const char * version(void);

NS_CN_END

#endif
