//
//  SFActionEase.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFActionEase.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#define SF_IMPLEMENT_CCACTION_WITH_ACTION(action_name) /* ccAction: actionWithAction(pAction) begin */ \
CCAction * SF##action_name::ccAction(void) { \
	CCActionInterval * pAction = getAction(); \
	return pAction ? CC##action_name::actionWithAction(pAction) : NULL; \
} /* ccAction - actionWithAction(pAction) end */

#define SF_IMPLEMENT_CCACTION_WITH_ACTION_RATE(action_name) /* ccAction: actionWithAction(pAction, fRate) begin */ \
CCAction * SF##action_name::ccAction(void) { \
	CCActionInterval * pAction = getAction(); \
	return pAction ? CC##action_name::actionWithAction(pAction, m_fRate) : NULL; \
} /* ccAction - actionWithAction(pAction, fRate) end */

#define SF_IMPLEMENT_CCACTION_WITH_ACTION_DURATION(action_name) /* ccAction: actionWithAction(pAction, fRate) begin */ \
CCAction * SF##action_name::ccAction(void) { \
	CCActionInterval * pAction = getAction(); \
	return pAction ? CC##action_name::actionWithAction(pAction, m_fDuration) : NULL; \
} /* ccAction - actionWithAction(pAction, fRate) end */



// SFActionEase
SFActionEase::SFActionEase(void)
: SFActionInterval()
, m_pAction(NULL)
{
	
}

SFActionEase::~SFActionEase(void)
{
	setAction(NULL);
}

bool SFActionEase::init(void)
{
	setAction(NULL);
	return true;
}

bool SFActionEase::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInterval::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCAction * pAction = SFActionEase::subActionFromDictionary(pDict);
	setAction(dynamic_cast<CCActionInterval *>(pAction));
	
	return true;
}

SF_IMPLEMENT_CCACTION_WITH_ACTION(ActionEase);

#pragma mark - Action Ease Rate

// SFEaseRateAction
bool SFEaseRateAction::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionEase::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	CCString * pRate = (CCString *)pDict->objectForKey("Rate");
	m_fRate = pRate ? pRate->floatValue() : 0;
	
	return true;
}

SF_IMPLEMENT_CCACTION_WITH_ACTION_RATE(EaseRateAction);

// SFEaseIn
SF_IMPLEMENT_CCACTION_WITH_ACTION_RATE(EaseIn);

// SFEaseOut
SF_IMPLEMENT_CCACTION_WITH_ACTION_RATE(EaseOut);

// SFEaseInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION_RATE(EaseInOut);

#pragma mark - Action Ease Exponential

// SFEaseExponentialIn
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseExponentialIn);

// SFEaseExponentialOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseExponentialOut);

// SFEaseExponentialInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseExponentialInOut);

#pragma mark - Action Ease Sine

// SFEaseSineIn
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseSineIn);

// SFEaseSineOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseSineOut);

// SFEaseSineInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseSineInOut);

#pragma mark - Action Ease Elastic

// SFEaseElastic
SF_IMPLEMENT_CCACTION_WITH_ACTION_DURATION(EaseElastic);

// SFEaseElasticIn
SF_IMPLEMENT_CCACTION_WITH_ACTION_DURATION(EaseElasticIn);

// SFEaseElasticOut
SF_IMPLEMENT_CCACTION_WITH_ACTION_DURATION(EaseElasticOut);

// SFEaseElasticInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION_DURATION(EaseElasticInOut);

#pragma mark - Action Ease Bounce

// SFEaseBounce
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBounce);

// SFEaseBounceIn
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBounceIn);

// SFEaseBounceOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBounceOut);

// SFEaseBounceInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBounceInOut);

#pragma mark - Action Ease Back

// SFEaseBackIn
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBackIn);

// SFEaseBackOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBackOut);

// SFEaseBackInOut
SF_IMPLEMENT_CCACTION_WITH_ACTION(EaseBackInOut);


NS_SF_END
