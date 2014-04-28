//
//  SFSprite.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFSprite_h
#define SpriteForest_X_SFSprite_h

#include "SFNode.h"
#include "SFEventHandler.h"

NS_SF_BEGIN

#define SF_RUNTIME_SPRITE(name)    SF_RUNTIME_NODE_INIT(name)

class SF_DLL SFSprite : public coconut2d::CNSprite
{
	CC_PROPERTY(cocos2d::CCArray *, m_pTextures, Textures);
	CN_SYNTHESIZE_RETAIN(SFEventDelegate *, m_pEventDelegate, EventDelegate);
	
public:
	SFSprite(void);
	virtual ~SFSprite(void);
	virtual bool init();
	
	static cocos2d::CCNode * nodeWithString(const char * pszString);
	static cocos2d::CCNode * nodeWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual void appointHandler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	
	// CNNode Extensions
	SFNODE_EXTENSIONS(SFSprite);
	// CNSprite factorys
	CNSPRITE_FACTORIES(SFSprite);
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_SPRITE(SFSprite);

NS_SF_END

#endif
