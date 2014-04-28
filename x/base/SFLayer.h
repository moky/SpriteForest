//
//  SFLayer.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFLayer_h
#define SpriteForest_X_SFLayer_h

#include "SFNode.h"

NS_SF_BEGIN

#define SF_RUNTIME_LAYER(name)    SF_RUNTIME_NODE_INIT(name)

class SF_DLL SFLayer : public coconut2d::CNLayer
{
	CC_PROPERTY(cocos2d::CCArray *, m_pTextures, Textures);
	
public:
	SFLayer(void);
	virtual ~SFLayer(void);
	virtual bool init(void);
	
	static cocos2d::CCNode * nodeWithString(const char * pszString);
	static cocos2d::CCNode * nodeWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	// CNNode Extensions
	SFNODE_EXTENSIONS(SFLayer);
	// CNLayers factorys
	CNLAYER_FACTORIES(SFLayer)
};

#pragma mark - Run-Time Type Identification

SF_RUNTIME_LAYER(SFLayer);

NS_SF_END

#endif
