//
//  SFTransitionScene.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFTransitionScene_h
#define SpriteForest_X_SFTransitionScene_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFTransitionScene : public cocos2d::CCObject
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, m_pName, Name);
	// values
	CC_SYNTHESIZE_RETAIN(cocos2d::CCScene *, m_pScene, Scene);
	CC_SYNTHESIZE(cocos2d::CCFloat, m_fDuration, Duration);
	CC_SYNTHESIZE(cocos2d::tOrientation, m_tOrientation, Orientation);
	CC_SYNTHESIZE(cocos2d::ccColor3B, m_tColor, Color);
	CC_SYNTHESIZE(bool, m_bReverse, Reverse);
	
public:
	SFTransitionScene(void);
	virtual ~SFTransitionScene(void);
	virtual bool init(void);
	
	static SFTransitionScene * transitionWithDictionary(cocos2d::CCDictionary * pDict);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	bool isNamed(const char * pszName);
	
	static cocos2d::CCScene * transitionScene(cocos2d::CCDictionary * pDict);
};

NS_SF_END

#endif
