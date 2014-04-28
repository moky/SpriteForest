//
//  SFActionInstant.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-27.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFActionInstant.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#pragma mark SFActionInstant

CCAction * SFActionInstant::ccAction(void)
{
	CNLog("override me!");
	return NULL;
}

#pragma mark SFShow

CCAction * SFShow::ccAction(void)
{
	return CCShow::action();
}

#pragma mark SFHide

CCAction * SFHide::ccAction(void)
{
	return CCHide::action();
}

#pragma mark SFToggleVisibility

CCAction * SFToggleVisibility::ccAction(void)
{
	return CCToggleVisibility::action();
}

#pragma mark SFFlipX

CCAction * SFFlipX::ccAction(void)
{
	return CCFlipX::action();
}

#pragma mark SFFlipY

CCAction * SFFlipY::ccAction(void)
{
	return CCFlipY::action();
}

#pragma mark SFPlace

bool SFPlace::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInstant::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	if (pPosition)
	{
		m_tPosition = CCPointFromString(pPosition->getCString());
	}
	return true;
}

CCAction * SFPlace::ccAction(void)
{
	return CCPlace::actionWithPosition(m_tPosition);
}

#pragma mark - Action call back

#pragma mark SFCallFunc

SFCallFunc::SFCallFunc(void)
: SFActionInstant()
, m_pTargetCallback(NULL)
, m_pSelector(NULL)
{
	
}

SFCallFunc::~SFCallFunc(void)
{
	setTargetCallback(NULL);
}

bool SFCallFunc::init(void)
{
	setTargetCallback(NULL);
	setSelector(NULL);
	return true;
}

bool SFCallFunc::initWithDictionary(CCDictionary * pDict)
{
	if (!SFActionInstant::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCObject * pTarget = pDict->objectForKey("Target");
	if (!pTarget)
	{
		pTarget = pDict->objectForKey("ss_Target");
	}
	setTargetCallback(pTarget);
	setSelector((CCString *)pDict->objectForKey("Selector"));
	return true;
}

CCAction * SFCallFunc::ccAction(void)
{
	if (!m_pTargetCallback || !m_pSelector)
	{
		CNLog("error");
		return NULL;
	}
	CNSelectorDelegate * pCallback = dynamic_cast<CNSelectorDelegate *>(m_pTargetCallback);
	if (!pCallback)
	{
		CNLog("cannot get selector: %s", m_pSelector->getCString());
		return NULL;
	}
	SEL_CallFunc selector = pCallback->getSelector(m_pSelector->getCString());
	if (!selector)
	{
		CNLog("no such selector: %s", m_pSelector->getCString());
		return NULL;
	}
	CNLog("selector: %s", m_pSelector->getCString());
	return CCCallFunc::actionWithTarget(m_pTargetCallback, selector);
}

#pragma mark SFCallFuncO

SFCallFuncO::SFCallFuncO(void)
: SFCallFunc()
, m_pObject(NULL)
{
	
}

SFCallFuncO::~SFCallFuncO(void)
{
	setObject(NULL);
}

bool SFCallFuncO::init(void)
{
	setObject(NULL);
	return true;
}

bool SFCallFuncO::initWithDictionary(CCDictionary * pDict)
{
	if (!SFCallFunc::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	setObject(pDict->objectForKey("Object"));
	return true;
}

CCAction * SFCallFuncO::ccAction(void)
{
	CCObject * pTargetCallback = getTargetCallback();
	CCString * pSelector = getSelector();
	if (!pTargetCallback || !pSelector)
	{
		CNLog("error");
		return NULL;
	}
	CNSelectorDelegate * pCallback = dynamic_cast<CNSelectorDelegate *>(pTargetCallback);
	if (!pCallback)
	{
		CNLog("cannot get selector: %s", pSelector->getCString());
		return NULL;
	}
	SEL_CallFuncO selector = pCallback->getSelectorO(pSelector->getCString());
	if (!selector)
	{
		CNLog("no such selector: %s", pSelector->getCString());
		return NULL;
	}
	return CCCallFuncO::actionWithTarget(pTargetCallback, selector, m_pObject);
}

NS_SF_END
