//
//  CCActionMagicSlow.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_CCActionMagicSlow_h
#define SpriteForest_X_CCActionMagicSlow_h

#include "CCActionMagic.h"

NS_SF_BEGIN

#pragma mark CCActionMagicSlow

class CC_DLL CCActionMagicSlow : public CCActionMagic
{
public:
	static void showIndicator(void);
	static void hideIndicator(void);
	
	// CCActionMagic factories
	SF_DECLARE_MAGIC_WITH_DICTIONARY(CCActionMagicSlow);
};

#define CCMAGIC_SLOW_CLASS(name) CCMAGIC_DECLARE_EXEC_CLASS(CCAction##name, CCActionMagicSlow)

CCMAGIC_SLOW_CLASS(LoadingIndicator);
CCMAGIC_SLOW_CLASS(Forest);
CCMAGIC_SLOW_CLASS(Scene);

NS_SF_END

#endif
