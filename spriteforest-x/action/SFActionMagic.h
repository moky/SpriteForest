//
//  SFActionMagic.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFActionMagic_h
#define SpriteForest_X_SFActionMagic_h

#include "SFAction.h"

NS_SF_BEGIN

#define SFMAGIC_CLASS(name) SFACTION_DECLARE_CCACTION_CLASS(SFAction##name, SFActionMagic)
#define SFMAGIC_RUNTIME_ACTION(name) SF_RUNTIME_ACTION(SFAction##name)

// SFActionMagic
class SFActionMagic : public SFAction
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pDict, Dict);
	
public:
	SFActionMagic(void);
	virtual ~SFActionMagic(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFActionMagic);
};

#pragma mark -

// magic
SFMAGIC_CLASS(Audio);
SFMAGIC_CLASS(Video);
SFMAGIC_CLASS(Particle);
SFMAGIC_CLASS(Web);
SFMAGIC_CLASS(Alert);
SFMAGIC_CLASS(AddChild);
SFMAGIC_CLASS(RemoveFromParent);
SFMAGIC_CLASS(StopAllActions);
// magic slow
SFMAGIC_CLASS(LoadingIndicator);
SFMAGIC_CLASS(Forest);
SFMAGIC_CLASS(Scene);


#pragma mark - Run-Time Type Identification

SFMAGIC_RUNTIME_ACTION(Magic);
// magic
SFMAGIC_RUNTIME_ACTION(Audio);
SFMAGIC_RUNTIME_ACTION(Video);
SFMAGIC_RUNTIME_ACTION(Particle);
SFMAGIC_RUNTIME_ACTION(Web);
SFMAGIC_RUNTIME_ACTION(Alert);
SFMAGIC_RUNTIME_ACTION(AddChild);
SFMAGIC_RUNTIME_ACTION(RemoveFromParent);
SFMAGIC_RUNTIME_ACTION(StopAllActions);
// magic slow
SFMAGIC_RUNTIME_ACTION(LoadingIndicator);
SFMAGIC_RUNTIME_ACTION(Forest);
SFMAGIC_RUNTIME_ACTION(Scene);

NS_SF_END

#endif
