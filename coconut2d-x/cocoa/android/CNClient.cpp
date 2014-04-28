//
//  CNClient.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-23.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "../CNClient.h"

#include <jni.h>
#include "android/jni/JniHelper.h"

NS_CN_BEGIN

// client info
static std::string s_sHardware         = "x86"; // "iPad2,1"
static std::string s_sDeviceIdentifier = "Android-Test-Alpha-0123456789ABCDEF"; // "C1898E26-2F6B-50CC-9221-9350CF40DFDE"
static std::string s_sDeviceModel      = "Android"; // "iPad"
static std::string s_sSystemName       = "Android"; // "iPhone_OS"
static std::string s_sSystemVersion    = "4.0"; // "5.1.1"
// bundle version
static std::string s_sVersion          = "1.0";

USING_NS_CC;

extern "C"
{
	void Java_com_slanissue_bevatingx_bevatingx_nativeSetClientInfo(JNIEnv*  env, jobject thiz, jstring clientInfo)
	{
		const char * str = env->GetStringUTFChars(clientInfo, NULL);
		std::string sClientInfo = str ? str : "";
		env->ReleaseStringUTFChars(clientInfo, str);
		
		CNLog("clientInfo: %s", sClientInfo.c_str());
		
		std::size_t pos = sClientInfo.find("=");
		if (pos == std::string::npos)
		{
			CNLog("error");
			return;
		}
		std::string sKey = sClientInfo.substr(0, pos);
		std::string sValue = sClientInfo.substr(pos + 1);
		CNLog("key: %s, value: %s", sKey.c_str(), sValue.c_str());
		
		if (sKey.empty())
		{
			CNLog("key is empty");
		}
		else if (strcasecmp(sKey.c_str(), "Hardware") == 0)
		{
			s_sHardware = sValue;
		}
		else if (strcasecmp(sKey.c_str(), "IMEI") == 0)
		{
			s_sDeviceIdentifier = sValue;
		}
		else if (strcasecmp(sKey.c_str(), "Model") == 0)
		{
			s_sDeviceModel = sValue;
		}
		else if (strcasecmp(sKey.c_str(), "SystemName") == 0)
		{
			s_sSystemName = sValue;
		}
		else if (strcasecmp(sKey.c_str(), "SystemVersion") == 0)
		{
			s_sSystemVersion = sValue;
		}
		else if (strcasecmp(sKey.c_str(), "Version") == 0)
		{
			s_sVersion = sValue;
		}
		else
		{
			CNLog("unrecognized key");
		}
	}
}

#pragma mark -

CCSize CNClient::getScreenSize(void)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CNLog("ScreenSize: (%f, %f)", winSize.height, winSize.width);
	return CCSizeMake(winSize.height, winSize.width);
}

CCFloat CNClient::getScreenScale(void)
{
	CCFloat scale = CCDirector::sharedDirector()->getContentScaleFactor();
	CNLog("ScreenScale: %f", scale);
	return scale;
}

CCSize CNClient::getWindowSize(void)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CNLog("WindowSize: (%f, %f)", winSize.height, winSize.width);
	return CCSizeMake(winSize.height, winSize.width);
}

const char * CNClient::getHardware(void)
{
	CNLog("Hardware: %s", s_sHardware.c_str());
	return s_sHardware.c_str();
}

const char * CNClient::getDeviceIdentifier(void)
{
	CNLog("DeviceIdentifier: %s", s_sDeviceIdentifier.c_str());
	return s_sDeviceIdentifier.c_str();
}

const char * CNClient::getDeviceModel(void)
{
	CNLog("DeviceModel: %s", s_sDeviceModel.c_str());
	return s_sDeviceModel.c_str();
}

const char * CNClient::getSystemName(void)
{
	CNLog("SystemName: %s", s_sSystemName.c_str());
	return s_sSystemName.c_str();
}

const char * CNClient::getSystemVersion(void)
{
	CNLog("SystemVersion: %s", s_sSystemVersion.c_str());
	return s_sSystemVersion.c_str();
}

const char * CNClient::getVersion(void)
{
	CNLog("Version: %s", s_sVersion.c_str());
	return s_sVersion.c_str();
}

NS_CN_END
