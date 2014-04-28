//
//  CNClient.h
//  Coconut2D-X
//
//  Created by Moky on 12-12-23.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNClient_h
#define Coconut2D_X_CNClient_h

#include "../cnMacros.h"

NS_CN_BEGIN

class CNClient
{
public:
	static cocos2d::CCSize  getScreenSize(void);
	static cocos2d::CCFloat getScreenScale(void);
	static cocos2d::CCSize  getWindowSize(void);
	
	static const char * getHardware(void);
	static const char * getDeviceIdentifier(void);
	static const char * getDeviceModel(void);
	static const char * getSystemName(void);
	static const char * getSystemVersion(void);
	
	static const char * getVersion(void); // client version from bundle
	
	// HTTP Request
	static const char * getClientParameters(void); // for stat
	
	static bool openURL(const char * pszURL);
	
	static bool isWiFiActived(void);
	static bool isConnected(void);
};

NS_CN_END

#endif
