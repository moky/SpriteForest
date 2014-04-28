//
//  CNScrollLayer.h
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNScrollLayer_h
#define Coconut2D_X_CNScrollLayer_h

#include "CNFiniteLayer.h"
#include "../controllers/CNScrollLayerController.h"

NS_CN_BEGIN

class CNScrollLayer : public CNFiniteLayer
{
	CC_SYNTHESIZE_RETAIN(CNScrollLayerController *, m_pScrollController, ScrollController);
	
public:
	CNScrollLayer(void);
	virtual ~CNScrollLayer(void);
	virtual bool init(void);
	
	virtual void onEnter();
	virtual void onExit();
};

NS_CN_END

#endif
