//
//  SFActionInstant.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-27.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFActionInstant_h
#define SpriteForest_X_SFActionInstant_h

#include "SFAction.h"

NS_SF_BEGIN

// SFActionInstant
SFACTION_DECLARE_CCACTION_CLASS(SFActionInstant, SFFiniteTimeAction);

// SFShow
SFACTION_DECLARE_CCACTION_CLASS(SFShow, SFActionInstant);

// SFHide
SFACTION_DECLARE_CCACTION_CLASS(SFHide, SFActionInstant);

// SFToggleVisibility
SFACTION_DECLARE_CCACTION_CLASS(SFToggleVisibility, SFActionInstant);

// SFFlipX
SFACTION_DECLARE_CCACTION_CLASS(SFFlipX, SFActionInstant);

// SFFlipY
SFACTION_DECLARE_CCACTION_CLASS(SFFlipY, SFActionInstant);

// SFPlace
class SFPlace : public SFActionInstant
{
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tPosition, Position);
	
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFPlace);
};

// SFCallFunc
class SFCallFunc : public SFActionInstant
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCObject *, m_pTargetCallback, TargetCallback);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, m_pSelector, Selector);
	
public:
	SFCallFunc(void);
	virtual ~SFCallFunc(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFCallFunc);
};

// SFCallFuncO
class SFCallFuncO : public SFCallFunc
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCObject *, m_pObject, Object);
	
public:
	SFCallFuncO(void);
	virtual ~SFCallFuncO(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	
	SF_ACTION_FACTORY(SFCallFuncO);
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_ACTION(SFShow);
SF_RUNTIME_ACTION(SFHide);
SF_RUNTIME_ACTION(SFToggleVisibility);

SF_RUNTIME_ACTION(SFFlipX);
SF_RUNTIME_ACTION(SFFlipY);

SF_RUNTIME_ACTION(SFPlace);

SF_RUNTIME_ACTION(SFCallFunc);
SF_RUNTIME_ACTION(SFCallFuncO);

NS_SF_END

#endif
