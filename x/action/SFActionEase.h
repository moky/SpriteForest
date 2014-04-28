//
//  SFActionEase.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFActionEase_h
#define SpriteForest_X_SFActionEase_h

#include "SFActionInterval.h"

NS_SF_BEGIN

// SFActionEase
class SFActionEase : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCActionInterval *, m_pAction, Action);
public:
	SFActionEase(void);
	virtual ~SFActionEase(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFActionEase);
};

#pragma mark - Action Ease Rate

// SFEaseRateAction
class SFEaseRateAction : public SFActionEase
{
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fRate, Rate);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFEaseRateAction);
};

// SFEaseIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseIn, SFEaseRateAction);

// SFEaseOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseOut, SFEaseRateAction);

// SFEaseInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseInOut, SFEaseRateAction);

#pragma mark - Action Ease Exponential

// SFEaseExponentialIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseExponentialIn, SFActionEase);

// SFEaseExponentialOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseExponentialOut, SFActionEase);

// SFEaseExponentialInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseExponentialInOut, SFActionEase);

#pragma mark - Action Ease Sine

// SFEaseSineIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseSineIn, SFActionEase);

// SFEaseSineOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseSineOut, SFActionEase);

// SFEaseSineInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseSineInOut, SFActionEase);

#pragma mark - Action Ease Elastic

// SFEaseElastic
SFACTION_DECLARE_CCACTION_CLASS(SFEaseElastic, SFActionEase);

// SFEaseElasticIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseElasticIn, SFEaseElastic);

// SFEaseElasticOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseElasticOut, SFEaseElastic);

// SFEaseElasticInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseElasticInOut, SFEaseElastic);

#pragma mark - Action Ease Bounce

// SFEaseBounce
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBounce, SFActionEase);

// SFEaseBounceIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBounceIn, SFEaseBounce);

// SFEaseBounceOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBounceOut, SFEaseBounce);

// SFEaseBounceInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBounceInOut, SFEaseBounce);

#pragma mark - Action Ease Back

// SFEaseBackIn
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBackIn, SFActionEase);

// SFEaseBackOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBackOut, SFActionEase);

// SFEaseBackInOut
SFACTION_DECLARE_CCACTION_CLASS(SFEaseBackInOut, SFActionEase);


#pragma mark - Run-Time Type Identification

SF_RUNTIME_ACTION(SFActionEase);
SF_RUNTIME_ACTION(SFEaseRateAction);

SF_RUNTIME_ACTION(SFEaseIn);
SF_RUNTIME_ACTION(SFEaseOut);
SF_RUNTIME_ACTION(SFEaseInOut);

SF_RUNTIME_ACTION(SFEaseExponentialIn);
SF_RUNTIME_ACTION(SFEaseExponentialOut);
SF_RUNTIME_ACTION(SFEaseExponentialInOut);

SF_RUNTIME_ACTION(SFEaseSineIn);
SF_RUNTIME_ACTION(SFEaseSineOut);
SF_RUNTIME_ACTION(SFEaseSineInOut);

SF_RUNTIME_ACTION(SFEaseElastic);
SF_RUNTIME_ACTION(SFEaseElasticIn);
SF_RUNTIME_ACTION(SFEaseElasticOut);
SF_RUNTIME_ACTION(SFEaseElasticInOut);

SF_RUNTIME_ACTION(SFEaseBounce);
SF_RUNTIME_ACTION(SFEaseBounceIn);
SF_RUNTIME_ACTION(SFEaseBounceOut);
SF_RUNTIME_ACTION(SFEaseBounceInOut);

SF_RUNTIME_ACTION(SFEaseBackIn);
SF_RUNTIME_ACTION(SFEaseBackOut);
SF_RUNTIME_ACTION(SFEaseBackInOut);

NS_SF_END

#endif
