//
//  SFScrollLayer.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFScrollLayer_h
#define SpriteForest_X_SFScrollLayer_h

#include "SFFiniteLayer.h"

NS_SF_BEGIN

class SFScrollLayer : public SFFiniteLayer
{
	CC_SYNTHESIZE_RETAIN(coconut2d::CNScrollLayerController *, m_pScrollController, ScrollController);
	
public:
	SFScrollLayer(void);
	virtual ~SFScrollLayer(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual void onEnter();
	virtual void onExit();
	
	// CNLayers factorys
	CNLAYER_FACTORIES(SFScrollLayer)
};

#pragma mark Run-Time Type Identification

SF_RUNTIME_LAYER(SFScrollLayer);

NS_SF_END

#endif
