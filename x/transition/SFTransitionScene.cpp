//
//  SFTransitionScene.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFTransitionScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFTransitionScene::SFTransitionScene(void)
: CCObject()
, m_pName(NULL)
, m_pScene(NULL)
, m_fDuration(0)
, m_tOrientation(kOrientationLeftOver)
, m_tColor(ccc3(255, 255, 255))
, m_bReverse(false)
{
	
}

SFTransitionScene::~SFTransitionScene(void)
{
	setName(NULL);
	setScene(NULL);
}

bool SFTransitionScene::init(void)
{
	setName(NULL);
	setScene(NULL);
	setDuration(0);
	setOrientation(kOrientationLeftOver);
	setColor(ccc3(255, 255, 255));
	setReverse(false);
	return true;
}

SFTransitionScene * SFTransitionScene::transitionWithDictionary(CCDictionary * pDict)
{
	SFTransitionScene * out = new SFTransitionScene();
	if (out && out->initWithDictionary(pDict))
	{
		out->autorelease();
		return out;
	}
	CC_SAFE_DELETE(out);
	return NULL;
}

bool SFTransitionScene::initWithDictionary(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("invalid dictionary");
		return false;
	}
	if (!init())
	{
		return false;
	}
	
	// transition name
	CCString * pTransition = (CCString *)pDict->objectForKey("Transition");
	if (pTransition)
	{
		std::string name(pTransition->getCString());
		if (CNString::hasPrefix(name, "Transition"))
		{
			name = name.substr(10);
		}
		setName(CCString::stringWithCString(name.c_str()));
	}
	
	// target scene
	CCScene * pScene = CNDictionary::objectForKey<CCScene>("Scene", pDict);
	if (!pScene)
	{
		CNLog("invalid scene");
		return false;
	}
	setScene(pScene);
	
	// other values
	CCString * pDuration = (CCString *)pDict->objectForKey("Duration");
	m_fDuration = pDuration ? pDuration->floatValue() : 0;
	
	CCString * pOrientation = (CCString *)pDict->objectForKey("Orientation");
	if (!pOrientation)
	{
	}
	else if (strcasecmp(pOrientation->getCString(), "LeftOver") == 0)
	{
		m_tOrientation = kOrientationLeftOver;
	}
	else if (strcasecmp(pOrientation->getCString(), "RightOver") == 0)
	{
		m_tOrientation = kOrientationRightOver;
	}
	else if (strcasecmp(pOrientation->getCString(), "UpOver") == 0)
	{
		m_tOrientation = kOrientationUpOver;
	}
	else if (strcasecmp(pOrientation->getCString(), "DownOver") == 0)
	{
		m_tOrientation = kOrientationDownOver;
	}
	else
	{
		CNLog("unknown orientation: %s", pOrientation->getCString());
	}
	
	CCString * pRed = (CCString *)pDict->objectForKey("Red");
	CCString * pGreen = (CCString *)pDict->objectForKey("Green");
	CCString * pBlue = (CCString *)pDict->objectForKey("Blue");
	if (pRed && pGreen && pBlue)
	{
		m_tColor = ccc3(pRed->intValue(), pGreen->intValue(), pBlue->intValue());
	}
	
	CCString * pReverse = (CCString *)pDict->objectForKey("Reverse");
	m_bReverse = pReverse ? pReverse->boolValue() : false;
	
	return true;
}

bool SFTransitionScene::isNamed(const char * pszName)
{
	if (!m_pName || m_pName->length() == 0 || !pszName || strlen(pszName) == 0)
	{
		return false;
	}
	return 0 == strcmp(m_pName->getCString(), pszName);
}

#define SF_TRANSITION_WITH_DURATINO_AND_SCENE(name, p) /* switch (transition.name) begin */ \
	if (p->isNamed(#name)) { \
		return CCTransition##name::transitionWithDuration(p->getDuration(), p->getScene()); \
	} \
/* switch (transition.name) end */

#define SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_ORIENTED(name, p) /* switch (transition.name) begin */ \
	if (p->isNamed(#name)) { \
		return CCTransition##name::transitionWithDuration(p->getDuration(), p->getScene(), p->getOrientation()); \
	} \
/* switch (transition.name) end */

#define SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_COLOR(name, p) /* switch (transition.name) begin */ \
	if (p->isNamed(#name)) { \
		return CCTransition##name::transitionWithDuration(p->getDuration(), p->getScene(), p->getColor()); \
	} \
/* switch (transition.name) end */

#define SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_REVERSE(name, p) /* switch (transition.name) begin */ \
	if (p->isNamed(#name)) { \
		return CCTransition##name::transitionWithDuration(p->getDuration(), p->getScene(), p->getReverse()); \
	} \
/* switch (transition.name) end */

#define SF_SWITCH_TRANSITION(name)   SF_TRANSITION_WITH_DURATINO_AND_SCENE(name, pTransition);
#define SF_SWITCH_TRANSITION_O(name) SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_ORIENTED(name, pTransition);
#define SF_SWITCH_TRANSITION_C(name) SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_COLOR(name, pTransition);
#define SF_SWITCH_TRANSITION_R(name) SF_TRANSITION_WITH_DURATINO_AND_SCENE_AND_REVERSE(name, pTransition);

CCScene * SFTransitionScene::transitionScene(CCDictionary * pDict)
{
	SFTransitionScene * pTransition = SFTransitionScene::transitionWithDictionary(pDict);
	if (!pTransition)
	{
		CNLog("error");
		return NULL;
	}
	
	SF_SWITCH_TRANSITION(Scene);
	SF_SWITCH_TRANSITION_O(SceneOriented);
	//--------------------------------------
	SF_SWITCH_TRANSITION(RotoZoom);
	SF_SWITCH_TRANSITION(JumpZoom);
	//--------------------------------------
	SF_SWITCH_TRANSITION(MoveInL);
	SF_SWITCH_TRANSITION(MoveInR);
	SF_SWITCH_TRANSITION(MoveInT);
	SF_SWITCH_TRANSITION(MoveInB);
	//--------------------------------------
	SF_SWITCH_TRANSITION(SlideInL);
	SF_SWITCH_TRANSITION(SlideInR);
	SF_SWITCH_TRANSITION(SlideInB);
	SF_SWITCH_TRANSITION(SlideInT);
	//--------------------------------------
	SF_SWITCH_TRANSITION(ShrinkGrow);
	//--------------------------------------
	SF_SWITCH_TRANSITION_O(FlipX);
	SF_SWITCH_TRANSITION_O(FlipY);
	SF_SWITCH_TRANSITION_O(FlipAngular);
	//--------------------------------------
	SF_SWITCH_TRANSITION_O(ZoomFlipX);
	SF_SWITCH_TRANSITION_O(ZoomFlipY);
	SF_SWITCH_TRANSITION_O(ZoomFlipAngular);
	//--------------------------------------
	SF_SWITCH_TRANSITION_C(Fade);
	SF_SWITCH_TRANSITION(CrossFade);
	SF_SWITCH_TRANSITION(TurnOffTiles);
	//--------------------------------------
	SF_SWITCH_TRANSITION(SplitCols);
	SF_SWITCH_TRANSITION(SplitRows);
	//--------------------------------------
	SF_SWITCH_TRANSITION(FadeTR);
	SF_SWITCH_TRANSITION(FadeBL);
	SF_SWITCH_TRANSITION(FadeUp);
	SF_SWITCH_TRANSITION(FadeDown);
	//--------------------------------------
	SF_SWITCH_TRANSITION_R(PageTurn);
	//--------------------------------------
	SF_SWITCH_TRANSITION(Progress);
	SF_SWITCH_TRANSITION(ProgressRadialCCW);
	SF_SWITCH_TRANSITION(ProgressRadialCW);
	SF_SWITCH_TRANSITION(ProgressHorizontal);
	SF_SWITCH_TRANSITION(ProgressVertical);
	SF_SWITCH_TRANSITION(ProgressInOut);
	SF_SWITCH_TRANSITION(ProgressOutIn);
	
	CNLog("unrecognized transition name");
	return pTransition->getScene();
}

NS_SF_END
