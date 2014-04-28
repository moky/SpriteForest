//
//  SFAction.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFAction_h
#define SpriteForest_X_SFAction_h

#include "../sfMacros.h"

NS_SF_BEGIN

#define SF_RUNTIME_ACTION(name)                         CN_RUNTIME_CLASS_INIT(name, action)

#define SF_ACTION_FACTORY(class_name)                   CN_INLINE_FACTORY(class_name, action, init)

#define SFACTION_DECLARE_CCACTION_CLASS(class_name, base_name) \
class class_name : public base_name { \
	SF_ACTION_FACTORY(class_name); \
	virtual cocos2d::CCAction * ccAction(void); \
};

// SFAction
class SFAction : public cocos2d::CCObject
{
public:
	SFAction(void);
	virtual ~SFAction(void);
	virtual bool init(void);
	
	static SFAction * getInstance(cocos2d::CCDictionary * pDict);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	static cocos2d::CCAction * subActionFromDictionary(cocos2d::CCDictionary * pDict);
	static cocos2d::CCArray * subActionsFromDictionary(cocos2d::CCDictionary * pDict);
};

// SFFiniteTimeAction
class SFFiniteTimeAction : public SFAction
{
	CC_SYNTHESIZE(cocos2d::ccTime, m_fDuration, Duration);
	
public:
	SFFiniteTimeAction(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
};

// SFRepeatForever
class SFRepeatForever : public SFAction
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCActionInterval *, m_pAction, Action);
	
public:
	SFRepeatForever(void);
	virtual ~SFRepeatForever(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFRepeatForever);
};

// SFSpeed
class SFSpeed : public SFAction
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCActionInterval *, m_pAction, Action);
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fRate, Rate);
	
public:
	SFSpeed(void);
	virtual ~SFSpeed(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFSpeed);
};

// SFFollow
class SFFollow : public SFAction
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCObject *, m_pTarget, Target);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCObject *, m_pFollowedNode, FollowedNode);
	CC_SYNTHESIZE(cocos2d::CCRect, m_tRect, Rect);
	
public:
	SFFollow(void);
	virtual ~SFFollow(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFFollow);
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_ACTION(SFRepeatForever);
SF_RUNTIME_ACTION(SFSpeed);
SF_RUNTIME_ACTION(SFFollow);

NS_SF_END

#endif
