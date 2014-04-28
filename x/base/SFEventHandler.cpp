//
//  SFEventHandler.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFEventHandler.h"

#include "SFNode.h"
#include "SFSprite.h"
#include "../action/SFAction.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFEventHandler::SFEventHandler(void)
: CCObject()
, m_pEventTree(NULL)
, m_pActionTree(NULL)
{
	
}

SFEventHandler::~SFEventHandler(void)
{
	setEventTree(NULL);
	setActionTree(NULL);
}

SFEventHandler * SFEventHandler::handler(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	SFEventHandler * pHandler = new SFEventHandler();
	if (pHandler && pHandler->init(pEventTree, pActionTree))
	{
		pHandler->autorelease();
		return pHandler;
	}
	else
	{
		CC_SAFE_RELEASE(pHandler);
		return NULL;
	}
}

bool SFEventHandler::init(CCDictionary * pEventTree, CCDictionary * pActionTree)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	setEventTree(pEventTree);
	setActionTree(pActionTree);
	
	snapshot(); // for restore 'Target'
	
	return true;
}

bool SFEventHandler::init(void)
{
	setEventTree(NULL);
	setActionTree(NULL);
	return true;
}

#pragma mark SFEventDelegate

CCNode * getTarget(CCDictionary * pDict, CCNode * pNode)
{
	if (!pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	CCObject * pTarget = pDict->objectForKey("Target");
	if (!pTarget)
	{
		pTarget = pDict->objectForKey("ss_Target");
	}
	if (!pTarget)
	{
		return pNode;
	}
	else if (CCString * string = dynamic_cast<CCString *>(pTarget))
	{
		return SFNode::getTarget(pNode, string->getCString());
	}
	else if (CCNode * node = dynamic_cast<CCNode *>(pTarget))
	{
		return node;
	}
	else
	{
		CNLog("could not happen");
		return NULL;
	}
}

bool SFEventHandler_runAction(CCDictionary * pDict, CCNode * pNode)
{
	if (!pDict || !pNode)
	{
		CNLog("could not happen!");
		return false;
	}
	pDict->setObject(pNode, "Target");
	SFAction * pAction = SFAction::getInstance(pDict);
	if (!pAction)
	{
		CNLog("failed to create action");
		return false;
	}
	CCAction * ccAction = pAction->ccAction();
	if (!ccAction)
	{
		CNLog("failed to create action");
		return false;
	}
	pNode->runAction(ccAction);
	return true;
}

bool SFEventHandler::doEvent(const char * pszEventName, CCNode * pNode)
{
	if (!pszEventName || strlen(pszEventName) == 0 || !pNode)
	{
		CNLog("invalid parameters");
		return false;
	}
	if (!m_pEventTree)
	{
		//CNLog("no event defined. name = %s", pszEventName);
		return false;
	}
	CCArray * pTasks = CNDictionary::arrayForKey(pszEventName, m_pEventTree);
	if (!pTasks)
	{
		//CNLog("no such event: %s", pszEventName);
		return false;
	}
	
	bool flag = false;
	
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(pTasks, pObj)
	{
		CCDictionary * pTask = dynamic_cast<CCDictionary *>(pObj);
		if (!pTask)
		{
			CNLog("invalid task in event: %s", pszEventName);
			continue;
		}
		CCNode * pTarget = getTarget(pTask, pNode);
		
		SFEventDelegate * pWorker = this;
		if (SFSprite * pSprite = dynamic_cast<SFSprite *>(pTarget))
		{
			pWorker = pSprite->getEventDelegate();
			if (!pWorker)
			{
				CNLog("could not happen!");
				continue;
			}
		}
		
		CCString * pName = (CCString *)pTask->objectForKey("Name");
		if (!pName)
		{
			CNLog("invalid task");
		}
		else if (pWorker->doEvent(pName->getCString(), pTarget))
		{
			flag = true;
		}
		else if (pWorker->doAction(pName->getCString(), pTarget))
		{
			// combined action
			flag = true;
		}
		else
		{
			// cc action
			flag = SFEventHandler_runAction(pTask, pTarget);
		}
		
	} // EOF 'CCARRAY_FOREACH(pTasks, pObj)'
	
	return flag;
}

bool SFEventHandler::doAction(const char * pszActionName, CCNode * pNode)
{
	if (!pszActionName || strlen(pszActionName) == 0 || !pNode)
	{
		CNLog("invalid parameters");
		return false;
	}
	if (!m_pActionTree)
	{
		//CNLog("no action defined.");
		return false;
	}
	CCDictionary * pDict = CNDictionary::dictionaryForKey(pszActionName, m_pActionTree);
	if (!pDict)
	{
		//CNLog("no such action: %s", pszActionName);
		return false;
	}
	
	CCNode * pTarget = getTarget(pDict, pNode);
	return SFEventHandler_runAction(pDict, pTarget);
}

#pragma mark -

void SFEventHandler_snapshot(CCDictionary * pDict); // pre-defined
void SFEventHandler_restore(CCDictionary * pDict); // pre-defined

void SFEventHandler_snapshot(CCArray * pArray)
{
	CCObject * obj = NULL;
	CCARRAY_FOREACH(pArray, obj)
	{
		if (CCDictionary * dict = dynamic_cast<CCDictionary *>(obj))
		{
			SFEventHandler_snapshot(dict);
		}
	}
}

void SFEventHandler_restore(CCArray * pArray)
{
	CCObject * obj = NULL;
	CCARRAY_FOREACH(pArray, obj)
	{
		if (CCDictionary * dict = dynamic_cast<CCDictionary *>(obj))
		{
			SFEventHandler_restore(dict);
		}
	}
}

void SFEventHandler_snapshot(CCDictionary * pDict)
{
	if (!pDict)
	{
		return;
	}
	CCDictElement * pElement = NULL;
	CCDICT_FOREACH(pDict, pElement)
	{
		const char * key = pElement->getStrKey();
		CCObject * obj = pElement->getObject();
		
		if (strcmp(key, "Target") == 0 && dynamic_cast<CCString *>(obj))
		{
			pDict->setObject(obj, "ss_Target"); // snapshot
		}
		else if (CCDictionary * dict = dynamic_cast<CCDictionary *>(obj))
		{
			SFEventHandler_snapshot(dict);
		}
		else if (CCArray * array = dynamic_cast<CCArray *>(obj))
		{
			SFEventHandler_snapshot(array);
		}
	}
}

void SFEventHandler_restore(CCDictionary * pDict)
{
	if (!pDict)
	{
		return;
	}
	CCDictElement * pElement = NULL;
	CCDICT_FOREACH(pDict, pElement)
	{
		const char * key = pElement->getStrKey();
		CCObject * obj = pElement->getObject();
		
		if (strcmp(key, "Target") == 0 && !dynamic_cast<CCString *>(obj))
		{
			obj = pDict->objectForKey("ss_Target");
			if (obj)
			{
				pDict->setObject(obj, "Target"); // restore
				pDict->removeObjectForKey("ss_Target");
			}
			else
			{
				pDict->removeObjectForKey("Target");
			}
		}
		else if (CCDictionary * dict = dynamic_cast<CCDictionary *>(obj))
		{
			SFEventHandler_restore(dict);
		}
		else if (CCArray * array = dynamic_cast<CCArray *>(obj))
		{
			SFEventHandler_restore(array);
		}
	}
}

void SFEventHandler::snapshot(void) const
{
	SFEventHandler_snapshot(m_pEventTree);
	SFEventHandler_snapshot(m_pActionTree);
}

void SFEventHandler::restore(void) const
{
	SFEventHandler_restore(m_pEventTree);
	SFEventHandler_restore(m_pActionTree);
}

NS_SF_END
