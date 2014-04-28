//
//  SFFiniteLayer.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFFiniteLayer_h
#define SpriteForest_X_SFFiniteLayer_h

#include "../base/SFLayer.h"

NS_SF_BEGIN

class SFFiniteLayer : public SFLayer
{
public:
	virtual void setPosition(const cocos2d::CCPoint & tPosition);
	
	// CNLayers factorys
	CNLAYER_FACTORIES(SFFiniteLayer)
};

#pragma mark Run-Time Type Identification

SF_RUNTIME_LAYER(SFFiniteLayer);

NS_SF_END

#endif
