//
//  SFAction.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFAction.h"

#include "../base/SFNode.h"
#include "SFActionMagic.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

#pragma mark SFAction

SFAction::SFAction(void)
: CCObject()
{
	
}

SFAction::~SFAction(void)
{
//	CNLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ dealloc");
}

bool SFAction::init(void)
{
	return true;
}

SFAction * SFAction::getInstance(CCDictionary * pDict)
{
	CCString * pName = (CCString *)pDict->objectForKey("Name");
	if (!pName)
	{
		CNLog("error");
		return NULL;
	}
	
	SFAction * pAction = NULL;
	
	std::string sClassName = std::string("SFAction").append(pName->getCString());
	CCObject * pObject = CNRuntimeClass::createObject(sClassName.c_str());
	if ((pAction = dynamic_cast<SFAction *>(pObject)))
	{
		return pAction->initWithDictionary(pDict) ? pAction : NULL;
	}
	
	sClassName = std::string("SF").append(pName->getCString());
	pObject = CNRuntimeClass::createObject(sClassName.c_str());
	if ((pAction = dynamic_cast<SFAction *>(pObject)))
	{
		return pAction->initWithDictionary(pDict) ? pAction : NULL;
	}
	
	sClassName = std::string("SFActionMagic");
	pObject = CNRuntimeClass::createObject(sClassName.c_str());
	if ((pAction = dynamic_cast<SFAction *>(pObject)))
	{
		return pAction->initWithDictionary(pDict) ? pAction : NULL;
	}
	
	CNLog("no such action: %s", pName->getCString());
	return NULL;
}

bool SFAction::initWithDictionary(CCDictionary * pDict)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	if (!pDict)
	{
		CNLog("dict cannot be null");
		return false;
	}
	return true;
}

CCAction * SFAction::ccAction(void)
{
	CNLog("override me!");
	return NULL;
}

CCAction * CCAction_actionByReplaceTarget(CCObject * pTarget, CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	
	if (!pTarget)
	{
		CNLog("target is NULL!");
		return NULL;
	}
	else if (CCNode * pNode = dynamic_cast<CCNode *>(pTarget))
	{
		pTarget = pDict->objectForKey("Target");
		if (!pTarget)
		{
			pTarget = pDict->objectForKey("ss_Target");
		}
		if (!pTarget)
		{
			pDict->setObject(pNode, "Target");
		}
		else if (CCString * pString = dynamic_cast<CCString *>(pTarget))
		{
			pNode = SFNode::getTarget(pNode, pString->getCString());
			if (pNode)
			{
				pDict->setObject(pNode, "Target");
			}
		}
	}
	else if (CCString * pString = dynamic_cast<CCString *>(pTarget))
	{
		CNLog("error: %s", pString->getCString());
		CC_UNUSED_PARAM(pString);
		return NULL;
	}
	else
	{
		CNLog("could not happen");
		return NULL;
	}
	
	SFAction * pAction = SFAction::getInstance(pDict);
	if (!pAction)
	{
		return NULL;
	}
	return pAction->ccAction();
}

CCAction * SFAction::subActionFromDictionary(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	CCObject * pAction = pDict->objectForKey("Action");
	if (!pAction)
	{
		CNLog("error");
		return NULL;
	}
	
	if (CCDictionary * dict = dynamic_cast<CCDictionary *>(pAction)) // maybe already replaced
	{
		CCObject * pTarget = pDict->objectForKey("Target");
		if (!pTarget)
		{
			pTarget = pDict->objectForKey("ss_Target");
		}
		CCAssert(pTarget, "target not set");
		pAction = CCAction_actionByReplaceTarget(pTarget, dict);
	}
	
	return dynamic_cast<CCAction *>(pAction);
}

CCArray * SFAction::subActionsFromDictionary(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	CCArray * pActions = CNDictionary::arrayForKey("Actions", pDict);
	if (!pActions)
	{
		CNLog("could not happen!");
		return NULL;
	}
	
	CCObject * pTarget = pDict->objectForKey("Target");
	if (!pTarget)
	{
		pTarget = pDict->objectForKey("ss_Target");
	}
	CCAssert(pTarget, "target not set");
	CCArray * pArr = CCArray::arrayWithCapacity(pActions->count());
	
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(pActions, pObj)
	{
		pm->push();
		
		if (CCDictionary * dict = dynamic_cast<CCDictionary *>(pObj)) // maybe already replaced
		{
			pObj = CCAction_actionByReplaceTarget(pTarget, dict);
		}
		
		if (dynamic_cast<CCAction *>(pObj))
		{
			pArr->addObject(pObj);
		}
		else
		{
			CNLog("error");
		}
		
		pm->pop();
	}
	return pArr;
}

#pragma mark SFFiniteTimeAction

SFFiniteTimeAction::SFFiniteTimeAction(void)
: SFAction()
, m_fDuration(0)
{
	
}

bool SFFiniteTimeAction::init(void)
{
	m_fDuration = 0.0f;
	return true;
}

bool SFFiniteTimeAction::initWithDictionary(CCDictionary * pDict)
{
	if (!SFAction::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCString * pDuration = (CCString *)pDict->objectForKey("Duration");
	if (pDuration)
	{
		m_fDuration = pDuration->floatValue();
	}
	return true;
}

#pragma mark SFRepeatForever

SFRepeatForever::SFRepeatForever(void)
: SFAction()
, m_pAction(NULL)
{
	
}

SFRepeatForever::~SFRepeatForever(void)
{
	setAction(NULL);
}

bool SFRepeatForever::init(void)
{
	setAction(NULL);
	return true;
}

bool SFRepeatForever::initWithDictionary(CCDictionary * pDict)
{
	if (!SFAction::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCAction * pAction = SFAction::subActionFromDictionary(pDict);
	CCActionInterval * pActionInterval = dynamic_cast<CCActionInterval *>(pAction);
	if (!pActionInterval)
	{
		CNLog("error");
		return false;
	}
	setAction(pActionInterval);
	return true;
}

CCAction * SFRepeatForever::ccAction(void)
{
	if (!m_pAction)
	{
		CNLog("error");
		return NULL;
	}
	return CCRepeatForever::actionWithAction(m_pAction);
}

#pragma mark SFSpeed

SFSpeed::SFSpeed(void)
: SFAction()
, m_pAction(NULL)
, m_fRate(0)
{
	
}

SFSpeed::~SFSpeed(void)
{
	setAction(NULL);
	setRate(0);
}

bool SFSpeed::init(void)
{
	setAction(NULL);
	setRate(0);
	return true;
}

bool SFSpeed::initWithDictionary(CCDictionary * pDict)
{
	if (!SFAction::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCAction * pAction = SFAction::subActionFromDictionary(pDict);
	CCActionInterval * pActionInterval = dynamic_cast<CCActionInterval *>(pAction);
	if (!pActionInterval)
	{
		CNLog("error");
		return NULL;
	}
	setAction(pActionInterval);
	
	CCString * pRate = (CCString *)pDict->objectForKey("Rate");
	if (pRate)
	{
		m_fRate = pRate->floatValue();
	}
	
	return true;
}

CCAction * SFSpeed::ccAction(void)
{
	if (!m_pAction)
	{
		CNLog("error");
		return NULL;
	}
	return CCSpeed::actionWithAction(m_pAction, m_fRate);
}

#pragma mark SFFollow

SFFollow::SFFollow(void)
: SFAction()
, m_pTarget(NULL)
, m_pFollowedNode(NULL)
, m_tRect(CCRectZero)
{
	
}

SFFollow::~SFFollow(void)
{
	setTarget(NULL);
	setFollowedNode(NULL);
}

bool SFFollow::init(void)
{
	setTarget(NULL);
	setFollowedNode(NULL);
	setRect(CCRectZero);
	return true;
}

bool SFFollow::initWithDictionary(CCDictionary * pDict)
{
	if (!SFAction::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	CCObject * pTarget = pDict->objectForKey("Target");
	if (!pTarget)
	{
		pTarget = pDict->objectForKey("ss_Target");
	}
	setTarget(pTarget);
	setFollowedNode(pDict->objectForKey("FollowedNode"));
	
	CCString * pRect = (CCString *)pDict->objectForKey("Rect");
	if (pRect)
	{
		setRect(CCRectFromString(pRect->getCString()));
	}
	return true;
}

CCAction * SFFollow::ccAction(void)
{
	// check followed node
	if (CCString * pString = dynamic_cast<CCString *>(m_pFollowedNode))
	{
		if (CCNode * pNode = dynamic_cast<CCNode *>(m_pTarget))
		{
			m_pFollowedNode = SFNode::getTarget(pNode, pString->getCString());
		}
	}
	
	CCNode * pNode = dynamic_cast<CCNode *>(m_pFollowedNode);
	if (!pNode)
	{
		CNLog("invalid followed node");
		return NULL;
	}
	
	if (CCRect::CCRectEqualToRect(m_tRect, CCRectZero))
	{
		return CCFollow::actionWithTarget(pNode);
	}
	else
	{
		return CCFollow::actionWithTarget(pNode, m_tRect);
	}
}

NS_SF_END
