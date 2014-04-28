//
//  SFTextSprite.h
//  SpriteForest-X
//
//  Created by Moky on 13-7-8.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFTextSprite_h
#define SpriteForest_X_SFTextSprite_h

#include "../base/SFSprite.h"

NS_SF_BEGIN

class SF_DLL SFTextSprite : public SFSprite
{
	CC_SYNTHESIZE_RETAIN(coconut2d::CNLabel *, m_pLabel, Label);
	
public:
	SFTextSprite(void);
	virtual ~SFTextSprite(void);
	virtual bool init(void);
	
	virtual bool setAttributes(cocos2d::CCDictionary * pDict);
	
	const char * getText(void);
	void setText(const char * pszText);
	
	// CNSprite factories
	CNSPRITE_FACTORIES(SFTextSprite);
};

#pragma mark Run-Time Type Identification

SF_RUNTIME_SPRITE(SFTextSprite);

NS_SF_END

#endif
