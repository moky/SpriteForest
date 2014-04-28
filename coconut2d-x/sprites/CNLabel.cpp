//
//  CNLabel.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-7-8.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#include "CNLabel.h"

NS_CN_BEGIN

USING_NS_CC;

static std::string s_sDefaultFontName = "Helvetica";
static unsigned int s_uiDefaultFontSize = 14;

bool CNLabel::initWithDictionary(cocos2d::CCDictionary *pDict)
{
	if (!pDict)
	{
		CNLog("invalid parameter: pDict");
		return false;
	}
	
	CCString * pText = (CCString *)pDict->objectForKey("Text");
	std::string sText = pText ? pText->getCString() : "";
	
	CCString * pFontName = (CCString *)pDict->objectForKey("FontName");
	std::string sFontName = pFontName ? pFontName->getCString() : CNLabel::getDefaultFontName();
	
	CCString * pFontSize = (CCString *)pDict->objectForKey("FontSize");
	float fFontSize = pFontSize ? pFontSize->floatValue() : CNLabel::getDefaultFontSize();
	
	// dimension for alignment
	CCString * pDimensions = (CCString *)pDict->objectForKey("Dimensions");
	CCSize dimensions = pDimensions ? CCSizeFromString(pDimensions->getCString()) : CCSizeZero;
	
	CCTextAlignment alignment = CCTextAlignmentCenter;
	CCString * pAlignment = (CCString *)pDict->objectForKey("Alignment");
	if (!pAlignment)
	{
		//
	}
	else if (strcasecmp(pAlignment->getCString(), "Left") == 0)
	{
		alignment = CCTextAlignmentLeft;
	}
	else if (strcasecmp(pAlignment->getCString(), "Right") == 0)
	{
		alignment = CCTextAlignmentRight;
	}
	
	if (!initWithString(sText.c_str(), dimensions, alignment, sFontName.c_str(), fFontSize))
	{
		CNLog("error");
		return false;
	}
	
	// color
	setColorWithDictionary(pDict);
	
	return true;
}

void CNLabel::setColorWithDictionary(cocos2d::CCDictionary *pColor)
{
	if (!pColor)
	{
		return;
	}
	CCString * pRed = (CCString *)pColor->objectForKey("Red");
	int iRed = pRed ? pRed->intValue() : 0;
	CCString * pGreen = (CCString *)pColor->objectForKey("Green");
	int iGreen = pGreen ? pGreen->intValue() : 0;
	CCString * pBlue = (CCString *)pColor->objectForKey("Blue");
	int iBlue = pBlue ? pBlue->intValue() : 0;
	
	setColor(ccc3(iRed, iGreen, iBlue));
}

// default font name
const char * CNLabel::getDefaultFontName(void)
{
	return s_sDefaultFontName.c_str();
}

void CNLabel::setDefaultFontName(const char * pszFontName)
{
	s_sDefaultFontName = pszFontName;
}

// default font size
unsigned int CNLabel::getDefaultFontSize(void)
{
	return s_uiDefaultFontSize;
}

void CNLabel::setDefaultFontSize(const unsigned int uiFontSize)
{
	s_uiDefaultFontSize = uiFontSize;
}

NS_CN_END
