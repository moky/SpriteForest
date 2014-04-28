//
//  SFActionInterval.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFActionInterval_h
#define SpriteForest_X_SFActionInterval_h

#include "SFAction.h"

NS_SF_BEGIN

// SFActionInterval
SFACTION_DECLARE_CCACTION_CLASS(SFActionInterval, SFFiniteTimeAction);

// SFSequence
class SFSequence : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pActions, Actions);
public:
	SFSequence(void);
	virtual ~SFSequence(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFSequence);
};

// SFRepeat
class SFRepeat : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCFiniteTimeAction *, m_pAction, Action);
	CC_SYNTHESIZE(int, m_iTimes, Times);
public:
	SFRepeat(void);
	virtual ~SFRepeat(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFRepeat);
};

// SFSpawn
class SFSpawn : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pActions, Actions);
public:
	SFSpawn(void);
	virtual ~SFSpawn(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFSpawn);
};

// SFRotateTo
class SFRotateTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fAngle, Angle);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFRotateTo);
};

// SFRotateBy
SFACTION_DECLARE_CCACTION_CLASS(SFRotateBy, SFRotateTo);

// SFMoveTo
class SFMoveTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tPosition, Position);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFMoveTo);
};

// SFMoveBy
SFACTION_DECLARE_CCACTION_CLASS(SFMoveBy, SFMoveTo);

// SFSkewTo
class SFSkewTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fSkewX, SkewX);
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fSkewY, SkewY);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFSkewTo);
};

// SFSkewBy
SFACTION_DECLARE_CCACTION_CLASS(SFSkewBy, SFSkewTo);

// SFJumpTo
class SFJumpTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCPoint, m_tPosition, Position);
	CC_SYNTHESIZE(cocos2d::ccTime, m_fHeight, Height);
	CC_SYNTHESIZE(int, m_iJumps, Jumps);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFJumpTo);
};

// SFJumpBy
SFACTION_DECLARE_CCACTION_CLASS(SFJumpBy, SFJumpTo);

// SFBezierTo
class SFBezierTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::ccBezierConfig, m_tBezierConfig, BezierConfig);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFBezierTo);
};

// SFBezierBy
SFACTION_DECLARE_CCACTION_CLASS(SFBezierBy, SFBezierTo);

// SFScaleTo
class SFScaleTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fScaleX, SkewX);
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fScaleY, SkewY);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFScaleTo);
};

// SFScaleBy
SFACTION_DECLARE_CCACTION_CLASS(SFScaleBy, SFScaleTo);

// SFBlink
class SFBlink : public SFActionInterval
{
	CC_SYNTHESIZE(int, m_iTimes, Times);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFBlink);
};

// SFFadeIn
SFACTION_DECLARE_CCACTION_CLASS(SFFadeIn, SFActionInterval);

// SFFadeOut
SFACTION_DECLARE_CCACTION_CLASS(SFFadeOut, SFActionInterval);

// SFFadeTo
class SFFadeTo : public SFActionInterval
{
	CC_SYNTHESIZE(GLubyte, m_iOpacity, Opacity);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFFadeTo);
};

// SFTintTo
class SFTintTo : public SFActionInterval
{
	CC_SYNTHESIZE(GLubyte, m_iRed, Red);
	CC_SYNTHESIZE(GLubyte, m_iGreen, Green);
	CC_SYNTHESIZE(GLubyte, m_iBlue, Blue);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFTintTo);
};

// SFTintBy
SFACTION_DECLARE_CCACTION_CLASS(SFTintBy, SFTintTo);

// SFDelayTime
SFACTION_DECLARE_CCACTION_CLASS(SFDelayTime, SFActionInterval);

// SFReverseTime
class SFReverseTime : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCFiniteTimeAction *, m_pAction, Action);
public:
	SFReverseTime(void);
	virtual ~SFReverseTime(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFReverseTime);
};

// SFMaskTo
class SFMaskTo : public SFActionInterval
{
	CC_SYNTHESIZE(cocos2d::CCRect, m_tRect, Rect);
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFMaskTo);
};

// SFMaskBy
SFACTION_DECLARE_CCACTION_CLASS(SFMaskBy, SFMaskTo);

// SFAnimate
class SFAnimate : public SFActionInterval
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFrames, Frames);
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fDelay, Delay);
	CC_SYNTHESIZE(int, m_iLoops, Loops);
	CC_SYNTHESIZE(bool, m_bRestoreOriginalFrame, RestoreOriginalFrame);
public:
	SFAnimate(void);
	virtual ~SFAnimate(void);
	virtual bool init(void);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	virtual cocos2d::CCAction * ccAction(void);
	SF_ACTION_FACTORY(SFAnimate);
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_ACTION(SFSequence);
SF_RUNTIME_ACTION(SFRepeat);
SF_RUNTIME_ACTION(SFSpawn);

SF_RUNTIME_ACTION(SFRotateTo);
SF_RUNTIME_ACTION(SFRotateBy);

SF_RUNTIME_ACTION(SFMoveTo);
SF_RUNTIME_ACTION(SFMoveBy);

SF_RUNTIME_ACTION(SFSkewTo);
SF_RUNTIME_ACTION(SFSkewBy);

SF_RUNTIME_ACTION(SFJumpTo);
SF_RUNTIME_ACTION(SFJumpBy);

SF_RUNTIME_ACTION(SFBezierTo);
SF_RUNTIME_ACTION(SFBezierBy);

SF_RUNTIME_ACTION(SFScaleTo);
SF_RUNTIME_ACTION(SFScaleBy);

SF_RUNTIME_ACTION(SFBlink);

SF_RUNTIME_ACTION(SFFadeIn);
SF_RUNTIME_ACTION(SFFadeOut);
SF_RUNTIME_ACTION(SFFadeTo);

SF_RUNTIME_ACTION(SFTintTo);
SF_RUNTIME_ACTION(SFTintBy);

SF_RUNTIME_ACTION(SFDelayTime);
SF_RUNTIME_ACTION(SFReverseTime);

SF_RUNTIME_ACTION(SFMaskTo);
SF_RUNTIME_ACTION(SFMaskBy);

SF_RUNTIME_ACTION(SFAnimate);

NS_SF_END

#endif
