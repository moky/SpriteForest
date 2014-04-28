//
//  SFProgressTimer.cpp
//  BevaTing-X
//
//  Created by Moky on 12-12-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFProgressTimer.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFProgressTimer::SFProgressTimer(void)
: SFSprite()
, m_pMask(NULL)
, m_iType(kCCProgressTimerTypeRadial)
, m_sTarget("")
{
	
}

SFProgressTimer::~SFProgressTimer(void)
{
	setMask(NULL);
}

bool SFProgressTimer::init(void)
{
	if (!SFSprite::init())
	{
		return false;
	}
	
	setMask(NULL);
	setType(kCCProgressTimerTypeRadial);
	setTarget("");
	return true;
}

bool SFProgressTimer::setAttributes(CCDictionary * pDict)
{
	if (!SFSprite::setAttributes(pDict))
	{
		return false;
	}
	CCString * pType = (CCString *)pDict->objectForKey("Type");
	if (pType)
	{
		setType(pType->getCString());
	}
	CCString * pSnapshot = (CCString *)pDict->objectForKey("Snapshot");
	if (pSnapshot)
	{
		setTarget(pSnapshot->getCString());
	}
	else
	{
		CNLog("ERROR: cannot file 'Snapshot'");
	}
	return true;
}

void SFProgressTimer::setType(const char * pszType)
{
	if (!pszType || strlen(pszType) == 0)
	{
		return;
	}
	// Radial
	else if (strcasecmp(pszType, "Radial") == 0)
	{
		setType(kCCProgressTimerTypeRadial);
	}
	else if (strcasecmp(pszType, "RadialCW") == 0)
	{
		setType(kCCProgressTimerTypeRadial);
	}
	else if (strcasecmp(pszType, "RadialCW") == 0)
	{
		setType(kCCProgressTimerTypeRadial);
	}
	// Bar
	else if (strcasecmp(pszType, "Bar") == 0)
	{
		setType(kCCProgressTimerTypeBar);
	}
	else if (strcasecmp(pszType, "HorizontalBarLR") == 0)
	{
		setType(kCCProgressTimerTypeBar);
	}
	else if (strcasecmp(pszType, "HorizontalBarRL") == 0)
	{
		setType(kCCProgressTimerTypeBar);
	}
	else if (strcasecmp(pszType, "VerticalBarBT") == 0)
	{
		setType(kCCProgressTimerTypeBar);
	}
	else if (strcasecmp(pszType, "VerticalBarTB") == 0)
	{
		setType(kCCProgressTimerTypeBar);
	}
}

CCProgressTimer * SFProgressTimer::getMask(void)
{
	return m_pMask;
}

void SFProgressTimer::setMask(CCProgressTimer * pMask)
{
	if (m_pMask != pMask)
	{
		CC_SAFE_RETAIN(pMask);
		if (m_pMask)
		{
			m_pMask->removeFromParentAndCleanup(true);
			m_pMask->release();
		}
		m_pMask = pMask;
	}
}

void SFProgressTimer::showProgress(void)
{
	if (m_sTarget.empty())
	{
		CNLog("target not set");
		return;
	}
	CCNode * pTarget = SFSprite::getTarget(m_sTarget.c_str());
	if (!pTarget)
	{
		CNLog("could not happen, target = %s", m_sTarget.c_str());
		return;
	}
	if (pTarget == this || CCSize::CCSizeEqualToSize(pTarget->getContentSize(), CCSizeZero))
	{
		CNLog("");
		return;
	}
	
	do
	{
		if (m_pMask)
		{
			break;
		}
		CCNode * parent = pTarget->getParent();
		if (!parent)
		{
			CNLog("could not happen");
			break;
		}
		
		// create image from target sprite
		CCImage * pImage = CNNode::getImageThreadSafe(pTarget);
		if (!pImage)
		{
			CNLog("error");
			break;
		}
		
		// create texture from image and put it into the cache
		char key[32];
		memset(key, 0, sizeof(key));
		snprintf(key, sizeof(key), "SFProgressTimer-%x", (int)this);
		CNLog("key: %s", key);
		CCTexture2D * pTexture = CCTextureCache::sharedTextureCache()->addUIImage(pImage, key);
		CC_SAFE_RELEASE(pImage);
		
		if (!pTexture)
		{
			CNLog("could not happen");
			break;
		}
		
		// put this texture into 'Textures' for auto cleanup when this object release
		if (!m_pTextures)
		{
			this->setTextures(CCArray::arrayWithCapacity(1));
		}
		m_pTextures->addObject(pTexture);
		
		CCPoint anchorPoint = ccp(0.5f, 0.5f);
		CCPoint position = CCPointZero;
		{
			CCSize size = pTarget->getContentSize();
			CCPoint anchor = pTarget->getAnchorPointInPoints();
			CCPoint center = CCPoint(size.width / 2, size.height / 2);
			CCPoint point = ccpAdd(pTarget->getPosition(), ccpSub(center, anchor));
			point = parent->convertToWorldSpace(point);
			position = this->convertToNodeSpace(point);
		}
		
		// snapshot
		CCSprite * pSnapshot = new CCSprite();
		if (pSnapshot && pSnapshot->initWithTexture(pTexture))
		{
			pSnapshot->setAnchorPoint(anchorPoint);
			pSnapshot->setPosition(position);
			pSnapshot->setOpacity(0x40);
			this->addChild(pSnapshot);
		}
		
		// snapshot2
		CCSprite * pSnapshot2 = new CCSprite();
		if (pSnapshot2 && pSnapshot2->initWithTexture(pTexture))
		{
			pSnapshot2->setAnchorPoint(anchorPoint);
			pSnapshot2->setPosition(position);
		}
		
		// mask
		CCProgressTimer * pMask = new CCProgressTimer();
		if (pMask && pMask->initWithSprite(pSnapshot2))
		{
			pMask->setAnchorPoint(anchorPoint);
			pMask->setPosition(position);
			pMask->setType(m_iType);
//			pMask->getSprite()->setOpacity(0x40);
			this->addChild(pMask);
		}
		
		this->setMask(pMask);
		CC_SAFE_RELEASE(pMask);
		CC_SAFE_RELEASE(pSnapshot);
		CC_SAFE_RELEASE(pSnapshot2);
	}
	while (0);
	
	pTarget->setIsVisible(false);
	this->setIsVisible(true);
}

void SFProgressTimer::hideProgress(void)
{
	if (m_sTarget.empty())
	{
		return;
	}
	CCNode * pTarget = SFSprite::getTarget(m_sTarget.c_str());
	if (!pTarget || pTarget == this)
	{
		return;
	}
	
	pTarget->setIsVisible(true);
	this->setIsVisible(false);
}

void SFProgressTimer::setPercentage(const CCFloat fPercentage)
{
	CCFloat percentage = fPercentage < 0 ? 0 : fPercentage;
	
	if (percentage < 100)
	{
		showProgress();
	}
	else
	{
		percentage = 100;
		hideProgress();
	}
	if (m_pMask)
	{
		m_pMask->setPercentage(/*100 -*/ percentage);
	}
}

NS_SF_END
