//
//  CNScene.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-21.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNScene.h"

NS_CN_BEGIN

USING_NS_CC;

CNScene::CNScene(void)
: CCScene()
, m_pTouchNodes(NULL)
, m_pAllClaimedKeys(NULL)
{
	
}

CNScene::~CNScene(void)
{
	CC_SAFE_RELEASE(m_pTouchNodes);
	CC_SAFE_RELEASE(m_pAllClaimedKeys);
	CNLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ dealloc");
}

bool CNScene::init(void)
{
	if (!CCScene::init())
	{
		CNLog("error");
		return false;
	}
	setAnchorPoint(CCPointZero);
	
	CC_SAFE_RELEASE(m_pTouchNodes);
	m_pTouchNodes = new CCDictionary();
	
	CC_SAFE_RELEASE(m_pAllClaimedKeys);
	m_pAllClaimedKeys = new CCSet();
	
	return true;
}

void CNScene::perform(void)
{
	perform(this);
}

void CNScene::perform(CCScene * scene)
{
	CCDirector * director = CCDirector::sharedDirector();
	if (director->getRunningScene())
	{
		// Clean the current scene before next created,
		// to avoid crash caused by sprite frame cache,
		// because CNScene will clean up all textures caches while creating
		director->getRunningScene()->cleanup();
		// Now create new scene for replacement.
		// NOTICE: here will call 'runningScene onExit' second time
		director->replaceScene(scene);
	}
	else
	{
		director->runWithScene(scene);
	}
}

#pragma mark Touch Dispatching

void CNScene::onEnter()
{
	CCScene::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, -1);
}

void CNScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCScene::onExit();
}

const char * CNScene_keyByNode(const CCNode * node)
{
	CCString * key = CCString::stringWithFormat("%x", (int)node);
	//CNLog("key = %s", key->getCString());
	return key->getCString();
}

void CNScene::addTouchNode(CCNode * node, CCTargetedTouchDelegate * delegate) const
{
	addTouchNode(node, delegate, -1);
}

void CNScene::addTouchNode(CCNode * node, CCTargetedTouchDelegate * delegate, const int maxTouches) const
{
	for (CCNode * p = node; p; p = p->getParent())
	{
		const char * key = CNScene_keyByNode(p);
		
		CNTouchObject * obj = (CNTouchObject *)m_pTouchNodes->objectForKey(key);
		if (!obj)
		{
			obj = new CNTouchObject();
			if (obj && obj->init())
			{
				obj->autorelease();
				m_pTouchNodes->setObject(obj, key);
			}
			else
			{
				CNLog("could not happen");
				CC_SAFE_DELETE(obj);
				continue;
			}
		}
		int count = obj->getCount();
		count++;
		obj->setCount(count);
		if (p == node && delegate)
		{
			obj->setDelegate(delegate);
			obj->setMaxTouches(maxTouches);
		}
	}
}

void CNScene::removeTouchNode(CCNode * node) const
{
	for (CCNode * p = node; p; p = p->getParent())
	{
		const char * key = CNScene_keyByNode(node);
		
		CNTouchObject * obj = (CNTouchObject *)m_pTouchNodes->objectForKey(key);
		if (obj)
		{
			int count = obj->getCount();
			count--;
			obj->setCount(count);
			if (count <= 0)
			{
				m_pTouchNodes->removeObjectForKey(key);
			}
		}
	}
}

CNTouchObject * CNScene::objectByNode(const CCNode * node) const
{
	const char * key = CNScene_keyByNode(node);
	return (CNTouchObject *)m_pTouchNodes->objectForKey(key);
}

const char * CNScene_keyByTouch(const CCTouch * touch)
{
	CCString * key = CCString::stringWithFormat("%x", (int)touch);
	//CNLog("key = %s", key->getCString());
	return key->getCString();
}

void CNScene::addClaimedKey(const char * pszKey) const
{
	if (!pszKey || strlen(pszKey) == 0)
	{
		return;
	}
	CCString * pKey = CCString::stringWithCString(pszKey);
	m_pAllClaimedKeys->addObject(pKey);
}

void CNScene::removeClaimedKey(const char * pszKey) const
{
	if (!pszKey || strlen(pszKey) == 0)
	{
		return;
	}
	CCArray * pArray = new CCArray();
	pArray->initWithCapacity(1);
	for (CCSetIterator iter = m_pAllClaimedKeys->begin(); iter != m_pAllClaimedKeys->end(); iter++)
	{
		CCString * pKey = (CCString *)(* iter);
		if (strcmp(pKey->getCString(), pszKey) == 0)
		{
			pArray->addObject(* iter);
		}
	}
	for (int i = pArray->count() - 1; i >= 0; --i)
	{
		CCObject * obj = pArray->objectAtIndex(i);
		m_pAllClaimedKeys->removeObject(obj);
	}
	pArray->release();
}

bool CNScene::isKeyClaimed(const char * pszKey) const
{
	if (!pszKey || strlen(pszKey) == 0)
	{
		return false;
	}
	for (CCSetIterator iter = m_pAllClaimedKeys->begin(); iter != m_pAllClaimedKeys->end(); iter++)
	{
		CCString * pKey = (CCString *)(* iter);
		if (strcmp(pKey->getCString(), pszKey) == 0)
		{
			return true;
		}
	}
	return false;
}

#pragma mark - Touch Delegate

bool CNScene::cnTouch(CCTouch * touch, CCEvent * event, const unsigned int touchType, CNTouchObject * touchObject)
{
	const char * pszTouchKey = CNScene_keyByTouch(touch);
	CCSet * claimedTouches = touchObject->getClaimedTouches();
	
	if (touchType == CCTOUCHBEGAN)
	{
        for (CCSetIterator iter = claimedTouches->begin(); iter != claimedTouches->end(); iter++)
        {
			pszTouchKey = CNScene_keyByTouch((CCTouch *)(*iter));
			removeClaimedKey(pszTouchKey);
		}
		touchObject->removeAllClaimedTouches();
	}
	
	bool claimed = false;
	// dispatch
	CCTargetedTouchDelegate * delegate = touchObject->getDelegate();
	if (!delegate)
	{
		CNLog("could not happen!");
	}
	else if (claimedTouches->containsObject(touch))
	{
		claimed = true;
		if (touchType == CCTOUCHMOVED)
		{
			delegate->ccTouchMoved(touch, event);
		}
		else if (touchType == CCTOUCHENDED)
		{
			removeClaimedKey(pszTouchKey);
			claimedTouches->removeObject(touch);
			delegate->ccTouchEnded(touch, event);
		}
		else if (touchType == CCTOUCHCANCELLED)
		{
			removeClaimedKey(pszTouchKey);
			claimedTouches->removeObject(touch);
			delegate->ccTouchCancelled(touch, event);
		}
		else
		{
			CNLog("could not happen!");
		}
	}
	else if (isKeyClaimed(pszTouchKey))
	{
		// already claimed by other obj
	}
	else if (touchObject->getMaxTouches() > 0 && claimedTouches->count() >= touchObject->getMaxTouches())
	{
		CNLog("the touch node has already claimed %d touch(es)", claimedTouches->count());
	}
	else if (touchType == CCTOUCHBEGAN || touchType == CCTOUCHMOVED)
	{
		claimed = delegate->ccTouchBegan(touch, event);
		if (claimed)
		{
			claimedTouches->addObject(touch);
			addClaimedKey(pszTouchKey);
		}
	}
	
	return claimed;
}

bool CNScene::cnTouch(CCTouch * touch, CCEvent * event, const unsigned int touchType, CCNode * node)
{
	int touchableCount = 0;
	CNTouchObject * obj = objectByNode(node);
	if (obj)
	{
		touchableCount = obj->getCount();
	}
	if (touchableCount <= 0)
	{
		CNLog("could not happen!");
		return false;
	}
	CCTargetedTouchDelegate * delegate = obj->getDelegate();
	
	CCArray * children = node->getChildren();
	if (!children)
	{
		children = CCArray::array();
	}
	int pos = children->count() - 1;
	
	CCNode * child;
	CNTouchObject * childObj;
	// check children which zOrder >= 0
	for (; pos >= 0 && (touchableCount > 1 || !delegate); pos--)
	{
		child = (CCNode *)children->objectAtIndex(pos);
		if (child->getZOrder() < 0)
		{
			break;
		}
		
		childObj = objectByNode(child);
		if (!childObj)
		{
			// not a touchable node
			continue;
		}
		touchableCount -= childObj->getCount();
		
		if (cnTouch(touch, event, touchType, child))
		{
			return true;
		}
	}
	
	if (touchableCount == 0)
	{
		return false;
	}
	else if (touchableCount < 0)
	{
		CNLog("could not happen!");
		return false;
	}
	
	// check self
	if (delegate)
	{
		touchableCount--;
		if (cnTouch(touch, event, touchType, obj))
		{
			return true;
		}
	}
	
	if (touchableCount == 0)
	{
		return false;
	}
	else if (touchableCount < 0)
	{
		CNLog("could not happen!");
		return false;
	}
	
	// check children which zOrder < 0
	for (; pos >= 0 && (touchableCount > 1 || !delegate); pos--)
	{
		child = (CCNode *)children->objectAtIndex(pos);
		if (child->getZOrder() >= 0)
		{
			CNLog("could not happen!");
			break;
		}
		
		childObj = objectByNode(child);
		if (!childObj)
		{
			// not a touchable node
			continue;
		}
		touchableCount -= childObj->getCount();
		
		if (cnTouch(touch, event, touchType, child))
		{
			return true;
		}
	}
	
	if (touchableCount != 0)
	{
		CNLog("could not happen!");
	}
	
	return false;
}

void CNScene::cnTouches(CCSet * touches, CCEvent * event, const unsigned int touchType)
{
	CCTouch * touch;
	for (CCSetIterator iter = touches->begin(); iter != touches->end(); iter++)
	{
		touch = (CCTouch *)(*iter);
		bool processed = cnTouch(touch, event, touchType, this);
		if (!processed)
		{
			CNLog("nothing hit.");
		}
	}
}

void CNScene::ccTouchesBegan(CCSet * pTouches, CCEvent * pEvent)
{
	cnTouches(pTouches, pEvent, CCTOUCHBEGAN);
}

void CNScene::ccTouchesMoved(CCSet * pTouches, CCEvent * pEvent)
{
	cnTouches(pTouches, pEvent, CCTOUCHMOVED);
}

void CNScene::ccTouchesEnded(CCSet * pTouches, CCEvent * pEvent)
{
	cnTouches(pTouches, pEvent, CCTOUCHENDED);
}

void CNScene::ccTouchesCancelled(CCSet * pTouches, CCEvent * pEvent)
{
	cnTouches(pTouches, pEvent, CCTOUCHCANCELLED);
}

#pragma mark - Touch Node

CNTouchObject::CNTouchObject(void)
: m_iCount(0)
, m_iMaxTouches(-1) // unlimited
, m_pClaimedTouches(NULL)
, m_pDelegate(NULL)
{
	
}

CNTouchObject::~CNTouchObject(void)
{
	setClaimedTouches(NULL);
	setDelegate(NULL);
}

bool CNTouchObject::init(void)
{
	m_iCount = 0;
	m_iMaxTouches = -1; // unlimited
	
	CCSet * pSet = new CCSet();
	setClaimedTouches(pSet);
	pSet->release();
	
	setDelegate(NULL);
	
	return true;
}

void CNTouchObject::removeAllClaimedTouches(void)
{
	while (m_pClaimedTouches->count() > 0)
	{
		CCObject * obj = m_pClaimedTouches->anyObject();
		if (!obj)
		{
			CNLog("could not happen!");
			break;
		}
		m_pClaimedTouches->removeObject(obj);
	}
}

NS_CN_END
