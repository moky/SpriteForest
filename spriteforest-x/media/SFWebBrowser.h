//
//  SFWebBrowser.h
//  SpriteForest-X
//
//  Created by Moky on 13-7-23.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFWebBrowser_h
#define SpriteForest_X_SFWebBrowser_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFWebBrowser : public cocos2d::CCObject
{
public:
	static void openURL(const char * pszURL);
	static void openURL(const char * pszURL, cocos2d::CCRect frame);
	static void openURL(const char * pszURL, cocos2d::CCRect frame, const char * pszButtonImage);
};

NS_SF_END

#endif
