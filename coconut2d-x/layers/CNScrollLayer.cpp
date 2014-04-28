//
//  CNScrollLayer.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-11.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNScrollLayer.h"

NS_CN_BEGIN

CNScrollLayer::CNScrollLayer(void)
: CNFiniteLayer()
, m_pScrollController(NULL)
{
	
}

CNScrollLayer::~CNScrollLayer(void)
{
	setScrollController(NULL);
}

bool CNScrollLayer::init(void)
{
	if (!CNFiniteLayer::init())
	{
		return false;
	}
	setScrollController(NULL);
	return true;
}

void CNScrollLayer::onEnter()
{
	CNFiniteLayer::onEnter();
	
	CNScrollLayerController * pController = new CNScrollLayerController();
	pController->init();
	pController->setNode(this);
	pController->setDragEnabled(true);
	setScrollController(pController);
	pController->release();
}

void CNScrollLayer::onExit()
{
	m_pScrollController->setNode(NULL);
	setScrollController(NULL);
	
	CNFiniteLayer::onExit();
}

NS_CN_END
