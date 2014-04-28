//
//  SFTextSprite.cpp
//  SpriteForest-X
//
//  Created by Moky on 13-7-8.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#include "SFTextSprite.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFTextSprite::SFTextSprite(void)
: SFSprite()
, m_pLabel(NULL)
{
	
}

SFTextSprite::~SFTextSprite(void)
{
	if (m_pLabel)
	{
		m_pLabel->removeFromParentAndCleanup(false);
	}
	setLabel(NULL);
}

bool SFTextSprite::init(void)
{
	if (!SFSprite::init())
	{
		CNLog("error");
		return false;
	}
	
	if (m_pLabel)
	{
		m_pLabel->removeFromParentAndCleanup(false);
	}
	setLabel(NULL);
	
	return true;
}

bool SFTextSprite::setAttributes(cocos2d::CCDictionary *pDict)
{
	if (!SFSprite::setAttributes(pDict))
	{
		CNLog("error");
		return false;
	}
	
	if (m_pLabel)
	{
		m_pLabel->removeFromParentAndCleanup(false);
	}
	setLabel(NULL);
	
	CCObject * pText = pDict->objectForKey("Text");
	if (!pText)
	{
		pText = CCString::stringWithCString("");
		pDict->setObject(pText, "Text");
	}
	
	CCString * pDimensions = (CCString *)pDict->objectForKey("Dimensions");
	if (!pDimensions)
	{
		CCSize dimensions = getContentSize();
		pDimensions = CCString::stringWithFormat("{%f, %f}", dimensions.width, dimensions.height);
		pDict->setObject(pDimensions, "Dimensions");
	}
	
	CNLabel * pLabel = CNLabel::labelWithDictionary(pDict);
	if (pLabel)
	{
		CCPoint center = ccpMult(ccpFromSize(getContentSize()), 0.5);
		pLabel->setPosition(center);
		addChild(pLabel);
		setLabel(pLabel);
	}
	
	return true;
}

const char * SFTextSprite::getText(void)
{
	if (m_pLabel)
	{
		return m_pLabel->getString();
	}
	return NULL;
}

void SFTextSprite::setText(const char *pszText)
{
	if (m_pLabel)
	{
		m_pLabel->setString(pszText);
	}
}

NS_SF_END
