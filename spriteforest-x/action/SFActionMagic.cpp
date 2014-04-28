//
//  SFActionMagic.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFActionMagic.h"

#include "CCActionMagic.h"
#include "CCActionMagicSlow.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#define SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(action_name) /* ccAction: actionWithDictionary(pDict) begin */ \
CCAction * SFAction##action_name::ccAction(void) { \
	CCDictionary * pDict = getDict(); \
	return CCAction##action_name::actionWithDictionary(pDict); \
} /* ccAction - actionWithDictionary(pDict) end */

SFActionMagic::SFActionMagic(void)
: SFAction()
, m_pDict(NULL)
{
	
}

SFActionMagic::~SFActionMagic(void)
{
	setDict(NULL);
}

bool SFActionMagic::init(void)
{
	setDict(NULL);
	return true;
}

bool SFActionMagic::initWithDictionary(CCDictionary * pDict)
{
	if (!SFAction::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	setDict(pDict);
	return true;
}

SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Magic);

#pragma mark -

// magic
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Audio);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Video);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Particle);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Web);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Alert);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(AddChild);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(RemoveFromParent);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(StopAllActions);
// magic slow
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(LoadingIndicator);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Forest);
SF_IMPLEMENT_CCACTION_WITH_DICTIONARY(Scene);


NS_SF_END
