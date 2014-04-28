//
//  sfMacros.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_sfMacros_h
#define SpriteForest_X_sfMacros_h

#include "coconut2d.h"



#define SF_USE_OUTPUT_FILE    0
#define SF_AUTO_TRANSFORM_PBF 0



#define SF_DLL          CN_DLL

// namespace spriteforest {}
#ifdef __cplusplus
#	define NS_SF_BEGIN  namespace spriteforest {
#	define NS_SF_END    }
#	define USING_NS_SF  using namespace spriteforest
#else
#	define NS_SF_BEGIN
#	define NS_SF_END
#	define USING_NS_SF
#endif

#endif
