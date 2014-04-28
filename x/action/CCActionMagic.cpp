//
//  CCActionMagic.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "CCActionMagic.h"

#include "../base/SFNodeFileParser.h"
#include "../base/SFNode.h"
#include "../base/SFSprite.h"
#include "../media/SFAudio.h"
#include "../media/SFVideo.h"
#include "../media/SFParticleSystem.h"
#include "../media/SFWebBrowser.h"

NS_SF_BEGIN

USING_NS_CC;

// CCActionMagic
CCActionMagic::CCActionMagic(void)
: CCActionInstant()
, m_pDict(NULL)
{
	
}

CCActionMagic::~CCActionMagic(void)
{
	setDict(NULL);
}

bool CCActionMagic::init(void)
{
	setDict(NULL);
	return true;
}

bool CCActionMagic::initWithDictionary(CCDictionary * pDict)
{
	if (!init())
	{
		CNLog("could not happen!");
		return false;
	}
	setDict(pDict);
	return true;
}

CCObject * CCActionMagic::copyWithZone(CCZone * pZone)
{
	CCZone * pNewZone = NULL;
	CCActionMagic * pCopy = NULL;
	if (pZone && pZone->m_pCopyObject)
	{
		// incase of being called at sub class
		pCopy = (CCActionMagic *)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCActionMagic();
		pZone = pNewZone = new CCZone(pCopy);
	}
	
	CCActionInstant::copyWithZone(pZone);
	
	pCopy->initWithDictionary(m_pDict);
	
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

CCNode * CCActionMagic::getTarget(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	CCObject * pTarget = m_pDict->objectForKey("Target");
	if (!pTarget)
	{
		pTarget = m_pDict->objectForKey("ss_Target");
	}
	if (!pTarget)
	{
		return m_pTarget;
	}
	else if (CCNode * pNode = dynamic_cast<CCNode *>(pTarget))
	{
		return pNode;
	}
	else if (CCString * pString = dynamic_cast<CCString *>(pTarget))
	{
		return SFNode::getTarget(m_pTarget, pString->getCString());
	}
	else
	{
		CNLog("could not happen!");
		return NULL;
	}
}

void CCActionMagic::startWithTarget(CCNode * pTarget)
{
	CCActionInstant::startWithTarget(pTarget);
	execute();
}

void CCActionMagic::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCObject * pName = m_pDict->objectForKey("Name");
	if (!pName)
	{
		CNLog("cannot find action name");
		return;
	}
	
	CCNode * pTarget = getTarget();
	if (!pTarget)
	{
		CNLog("could not happen!");
		return;
	}
	SFSprite * pSprite = dynamic_cast<SFSprite *>(pTarget);
	if (!pSprite)
	{
		CNLog("cannot execute this action on a non-sfsprite");
		return;
	}
	
	SFEventDelegate * pWorker = pSprite->getEventDelegate();
	if (!pWorker)
	{
		CNLog("could not happen!");
		return;
	}
	
	CCString * pActionName = dynamic_cast<CCString *>(pName);
	if (!pActionName)
	{
		CNLog("could not happen");
		return;
	}
	
	const char * pszActionName = pActionName->getCString();
	
	if (pWorker->doEvent(pszActionName, pSprite))
	{
		//CNLog("OK");
	}
	else if (pWorker->doAction(pszActionName, pSprite))
	{
		//CNLog("OK");
	}
	else
	{
		CNLog("no such action: %s", pszActionName);
	}
}

#pragma mark -

// Audio
void CCActionAudio::execute(void) const
{
	if (!SFAudio::perform(m_pDict))
	{
		CNLog("error");
	}
}

// Video
void CCActionVideo::execute(void) const
{
	CCNode * pTarget = getTarget();
	if (!SFVideo::perform(m_pDict, pTarget))
	{
		CNLog("error");
	}
}

// Particle
void CCActionParticle::execute(void) const
{
	CCNode * pTarget = getTarget();
	if (!pTarget)
	{
		CNLog("could not happen");
		return;
	}
	SFParticleSystem * pSystem = SFParticleSystem::particle(m_pDict);
	if (!pSystem)
	{
		CNLog("error");
		return;
	}
	pSystem->run(pTarget);
}

// Web
void CCActionWeb::execute(void) const
{
	CCString * pURL = (CCString *)m_pDict->objectForKey("URL");
	if (!pURL)
	{
		CNLog("no url to open");
		return;
	}
	
	CCString * pFrame = (CCString *)m_pDict->objectForKey("Frame");
	if (!pFrame)
	{
		SFWebBrowser::openURL(pURL->getCString());
		return;
	}
	
	CCObject * pCloseButton = m_pDict->objectForKey("CloseButton");
	if (!pCloseButton)
	{
		SFWebBrowser::openURL(pURL->getCString(), CCRectFromString(pFrame->getCString()));
		return;
	}
	
	CCString * pFilename = NULL;
	if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pCloseButton))
	{
		pFilename = (CCString *)pDict->objectForKey("File");
	}
	else
	{
		pFilename = (CCString *)pCloseButton;
	}
	SFWebBrowser::openURL(pURL->getCString(), CCRectFromString(pFrame->getCString()), pFilename->getCString());
}

// Alert
void CCActionAlert::execute(void) const
{
	CCString * pTitle = (CCString *)m_pDict->objectForKey("Title");
	CCString * pMessage = (CCString *)m_pDict->objectForKey("Message");
	if (!pMessage)
	{
		CNLog("could not happen");
		return;
	}
	if (pTitle && pTitle->length() > 0)
	{
		CCMessageBox(pMessage->getCString(), pTitle->getCString());
	}
	else
	{
		CCMessageBox(pMessage->getCString(), "Alert");
	}
}

// AddChild
void CCActionAddChild::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCNode * pNode = getTarget();
	if (!pNode)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pFilename = (CCString *)m_pDict->objectForKey("File");
	if (!pFilename)
	{
		CNLog("invalid action");
		return;
	}
	
	CNLog("adding child from %s", pFilename->getCString());
	SFNodeFileParser * parser = SFNodeFileParser::parser(pFilename->getCString());
	if (!parser)
	{
		CNLog("failed to load SFNode file");
		return;
	}
	CCObject * pObject = parser->node();
	CCDictionary * pDict = dynamic_cast<CCDictionary *>(pObject);
	if (!pDict)
	{
		CNLog("SFNode file error");
		return;
	}
	CCNode * pChild = SFSprite::nodeWithDictionary(pDict);
	if (!pChild)
	{
		CNLog("error");
		return;
	}
	
	CCString * pOrder = (CCString *)pDict->objectForKey("ZOrder");
	int zOrder = pOrder ? pOrder->intValue() : 0;
	pNode->addChild(pChild, zOrder);
}

// RemoveFromParent
void CCActionRemoveFromParent::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCNode * pNode = getTarget();
	if (!pNode)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pCleanup = (CCString *)m_pDict->objectForKey("Cleanup");
	bool flag = pCleanup ? pCleanup->boolValue() : true;
	pNode->removeFromParentAndCleanup(flag);
}

// CCStopAllActions
void CCActionStopAllActions::execute(void) const
{
	CCNode * pNode = getTarget();
	if (!pNode)
	{
		CNLog("could not happen!");
		return;
	}
	pNode->stopAllActions();
}

NS_SF_END
