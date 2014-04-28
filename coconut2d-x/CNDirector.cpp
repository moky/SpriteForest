//
//  CNDirector.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-20.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNDirector.h"

NS_CN_BEGIN

USING_NS_CC;

static CNDirector * s_pSharedDirector = NULL;

CNDirector * CNDirector::sharedDirector(void)
{
	if (!s_pSharedDirector)
	{
		s_pSharedDirector = new CNDirector();
		s_pSharedDirector->init();
	}
	
	return s_pSharedDirector;
}

CNDirector::CNDirector(void)
: CCObject()
, m_tWinSize(CCSizeZero)
{
	
}

CNDirector::~CNDirector(void)
{
	
}

bool CNDirector::init(void)
{
	m_tWinSize = CCDirector::sharedDirector()->getWinSize();
	return true;
}

NS_CN_END
