//
//  SFProgressTimer.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFProgressTimer_h
#define SpriteForest_X_SFProgressTimer_h

#include "../base/SFSprite.h"

NS_SF_BEGIN

class SFProgressTimer : public SFSprite
{
	CC_PROPERTY(cocos2d::CCProgressTimer *, m_pMask, Mask);
	CC_SYNTHESIZE(cocos2d::CCProgressTimerType, m_iType, Type);
	CC_SYNTHESIZE(std::string, m_sTarget, Target);
	
public:
	SFProgressTimer(void);
	virtual ~SFProgressTimer(void);
	virtual bool init(void);
	
	virtual bool setAttributes(cocos2d::CCDictionary * pDict);
	
	virtual void setType(const char * pszType);
	virtual void setPercentage(const cocos2d::CCFloat fPercentage);
	
	virtual void showProgress(void);
	virtual void hideProgress(void);
};

NS_SF_END

#endif
