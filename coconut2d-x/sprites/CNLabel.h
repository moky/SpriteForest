//
//  CNLabel.h
//  Coconut2D-X
//
//  Created by Moky on 13-7-8.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNLabel_h
#define Coconut2D_X_CNLabel_h

#include "../CNNode.h"
#include "../cocoa/CNSelector.h"

NS_CN_BEGIN

class CN_DLL CNLabel : public cocos2d::CCLabelTTF
{
public:
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	void setColorWithDictionary(cocos2d::CCDictionary * pColor);
	
	// default font name
	static const char * getDefaultFontName(void);
	static void setDefaultFontName(const char * pszFontName);
	// default font size
	static unsigned int getDefaultFontSize(void);
	static void setDefaultFontSize(const unsigned int uiFontSize);
	
	// factories
	CN_INLINE_FACTORY(CNLabel, node, init)
	CN_INLINE_FACTORY_VAR(CNLabel, labelWithDictionary, initWithDictionary, cocos2d::CCDictionary *);
};

NS_CN_END

#endif
