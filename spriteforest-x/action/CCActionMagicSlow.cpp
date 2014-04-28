//
//  CCActionMagicSlow.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "CCActionMagicSlow.h"

#include "../base/SFLord.h"

NS_SF_BEGIN

USING_NS_CC;

// MagicSlow
void CCActionMagicSlow::showIndicator(void)
{
	CNLog("not implement");
}

void CCActionMagicSlow::hideIndicator(void)
{
	CNLog("not implement");
}

// LoadingIndicator
void CCActionLoadingIndicator::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pHidden = (CCString *)m_pDict->objectForKey("Hidden");
	if (!pHidden)
	{
		CNLog("invalid dict");
		return;
	}
	if (pHidden->boolValue())
	{
		hideIndicator();
	}
	else
	{
		showIndicator();
	}
}

// Forest
void CCActionForest_performForestWithDictonary(CCDictionary * pDict)
{
	SFLord * myLord = SFLord::sharedLord();
	if (!myLord)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pHistory = (CCString *)pDict->objectForKey("History");
	if (pHistory)
	{
		if (strcasecmp(pHistory->getCString(), "goBack()") == 0)
		{
			if (myLord->goBack())
			{
				CNLog("back to previous forest/scene");
			}
			else
			{
				CNLog("failed to go back");
			}
		}
		else
		{
			CNLog("unrecognized history");
		}
		return;
	}
	
	CCString * pPath = (CCString *)pDict->objectForKey("File");
	CCObject * pScene = pDict->objectForKey("Scene");
	
	if (pPath)
	{
		if (!pScene || dynamic_cast<CCString *>(pScene))
		{
			pScene = pDict;
		}
		if (myLord->runIntoForest(pPath->getCString(), pScene))
		{
			CNLog("OK");
		}
		else
		{
			CNLog("invalid forest");
		}
	}
	else if (pScene)
	{
		if (myLord->performScene(pScene))
		{
			CNLog("OK");
		}
		else
		{
			CNLog("failed to perform scene");
		}
	}
	else
	{
		CNLog("error");
	}
}

void CCActionForest_performForestWithDictonary(CCDictionary * pDict, const bool bShowIndicator)
{
	if (bShowIndicator)
	{
		CCActionForest::showIndicator();
		CCActionForest_performForestWithDictonary(pDict);
		CCActionForest::hideIndicator();
	}
	else
	{
		CCActionForest_performForestWithDictonary(pDict);
	}
}

void CCActionForest::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pShowIndicator = (CCString *)m_pDict->objectForKey("ShowIndicator");
	bool flag = pShowIndicator ? pShowIndicator->boolValue() : true;
	CCActionForest_performForestWithDictonary(m_pDict, flag);
}

// Scene
void CCActionScene::execute(void) const
{
	if (!m_pDict)
	{
		CNLog("could not happen!");
		return;
	}
	CCString * pShowIndicator = (CCString *)m_pDict->objectForKey("ShowIndicator");
	bool flag = pShowIndicator ? pShowIndicator->boolValue() : true;
	// this is a 'Scene' action info, transform it to a 'Forest' action info
	CCDictionary * pDict = CCDictionary::dictionary();
	pDict->setObject(m_pDict, "Scene");
	CCActionForest_performForestWithDictonary(pDict, flag);
}

NS_SF_END
