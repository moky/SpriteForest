//
//  spriteforest.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_spriteforest_h
#define SpriteForest_X_spriteforest_h

#include "sfMacros.h"

#include "base/SFNode.h"
#include "base/SFSprite.h"
#include "base/SFLayer.h"
#include "base/SFScene.h"
#include "base/SFForest.h"
#include "base/SFEventHandler.h"
#include "base/SFNodeFileParser.h"
#include "base/SFLord.h"

#include "action/CCActionMagic.h"
#include "action/CCActionMagicSlow.h"
#include "action/SFAction.h"
#include "action/SFActionInstant.h"
#include "action/SFActionInterval.h"
#include "action/SFActionEase.h"
#include "action/SFActionMagic.h"
#include "action/SFAnimation.h"

#include "extension/SFSpriteBatchNode.h"
#include "extension/SFTouchSprite.h"
#include "extension/SFDragSprite.h"
#include "extension/SFFiniteLayer.h"
#include "extension/SFScrollLayer.h"
#include "extension/SFProgressTimer.h"
#include "extension/SFTextSprite.h"

#include "media/SFAudio.h"
#include "media/SFParticleSystem.h"
#include "media/SFWebBrowser.h"

#include "transition/SFTransitionScene.h"

NS_SF_BEGIN

#define SpriteForest SFForest
#define ForestLord   SFLord

const char * version(void);

NS_SF_END

#endif
