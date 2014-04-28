//
//  CCActionMagic.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_CCActionMagic_h
#define SpriteForest_X_CCActionMagic_h

#include "../sfMacros.h"

NS_SF_BEGIN

#define SF_RUNTIME_MAGIC(name)                         CN_RUNTIME_CLASS_INIT(name, action)

#define SF_DECLARE_MAGIC_WITH_DICTIONARY(class_name)   CN_INLINE_FACTORY_VAR(class_name, actionWithDictionary, initWithDictionary, cocos2d::CCDictionary *)

#pragma mark CCActionMagic

class CC_DLL CCActionMagic : public cocos2d::CCActionInstant
{
	CN_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pDict, Dict);
	
public:
	CCActionMagic(void);
	virtual ~CCActionMagic(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCObject * copyWithZone(cocos2d::CCZone * pZone);
	
	cocos2d::CCNode * getTarget(void) const;
	
	void startWithTarget(cocos2d::CCNode * pTarget);
	virtual void execute(void) const;
	
	// CCActionMagic factories
	SF_DECLARE_MAGIC_WITH_DICTIONARY(CCActionMagic);
};

#pragma mark -

#define CCMAGIC_DECLARE_EXEC_CLASS(class_name, base_class) \
class CC_DLL class_name : public base_class { \
	SF_DECLARE_MAGIC_WITH_DICTIONARY(class_name); \
	virtual void execute(void) const; \
};

#define CCMAGIC_CLASS(name) CCMAGIC_DECLARE_EXEC_CLASS(CCAction##name, CCActionMagic)

CCMAGIC_CLASS(Audio);
CCMAGIC_CLASS(Video);
CCMAGIC_CLASS(Particle);
CCMAGIC_CLASS(Web);
CCMAGIC_CLASS(Alert);
CCMAGIC_CLASS(AddChild);
CCMAGIC_CLASS(RemoveFromParent);
CCMAGIC_CLASS(StopAllActions);

NS_SF_END

#endif
