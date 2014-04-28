//
//  SFScene.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFScene_h
#define SpriteForest_X_SFScene_h

#include "SFNode.h"

NS_SF_BEGIN

class SF_DLL SFScene : public coconut2d::CNScene
{
public:
	static cocos2d::CCNode * nodeWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	static cocos2d::CCArray * loadTextures(cocos2d::CCArray * pTextures);
	static void cleanTextures(cocos2d::CCArray * pTextures);
	
	// SFNode Extensions
	SFNODE_EXTENSIONS(SFScene);
	// factory
	CN_INLINE_FACTORY(SFScene, node, init);
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_NODE_INIT(SFScene);

NS_SF_END

#endif
