//
//  CNClient.mm
//  Coconut2D-X
//
//  Created by Moky on 12-12-23.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <ifaddrs.h>

#include "IPAddress.h"

#include "../CNClient.h"

NS_CN_BEGIN

// client info
static std::string s_sHardware         = ""; // "iPad2,1"
static std::string s_sDeviceIdentifier = ""; // "C1898E26-2F6B-50CC-9221-9350CF40DFDE"
static std::string s_sDeviceModel      = ""; // "iPad"
static std::string s_sSystemName       = ""; // "iPhone_OS"
static std::string s_sSystemVersion    = ""; // "5.1.1"
// bundle version
static std::string s_sVersion          = "";

std::string & CNClient_escape(std::string & str)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * string = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
	string = [string stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	str = [string cStringUsingEncoding:NSUTF8StringEncoding];
	[pool release];
	return str;
}

std::string & CNClient_escape(std::string & str, NSString * src)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	str = [src cStringUsingEncoding:NSUTF8StringEncoding];
	[pool release];
	return CNClient_escape(str);
}

USING_NS_CC;

CCSize CNClient::getScreenSize(void)
{
	CGRect rect = [[UIScreen mainScreen] bounds];
	return CCSizeMake(rect.size.width, rect.size.height);
}

CCFloat CNClient::getScreenScale(void)
{
	UIScreen * screen = [UIScreen mainScreen];
	if ([screen respondsToSelector:@selector(scale)])
	{
		return [screen scale];
	}
	else
	{
		return 1.0f;
	}
}

CCSize CNClient::getWindowSize(void)
{
	CGRect rect = [[UIScreen mainScreen] applicationFrame];
	return CCSizeMake(rect.size.width, rect.size.height);
}

const char * CNClient::getHardware(void)
{
	if (s_sHardware.empty())
	{
		size_t size;
		sysctlbyname("hw.machine", NULL, &size, NULL, 0);
		char * machine = (char *)malloc(size);
		memset(machine, 0, size);
		sysctlbyname("hw.machine", machine, &size, NULL, 0);
		s_sHardware = machine;
		free(machine);
		s_sHardware = CNClient_escape(s_sHardware);
	}
	return s_sHardware.c_str();
}

const char * CNClient::getDeviceIdentifier(void)
{
	if (s_sDeviceIdentifier.empty())
	{
//		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//		s_sDeviceIdentifier = CNClient_escape(s_sDeviceIdentifier,
//											  [[UIDevice currentDevice] uniqueIdentifier]);
//		[pool release];
		
		/**
		 *  [UIDevice uniqueIdentifier] is forbidden in iOS5+
		 *  so we must use other way...
		 */
		InitAddresses();
		GetIPAddresses();
		GetHWAddresses();
		
		for (int i = 0; i<MAXADDRS; ++i)
		{
			static unsigned long localHost = 0x7F000001;            // 127.0.0.1
			unsigned long theAddr;
			
			theAddr = ip_addrs[i];
			
			if (theAddr == 0) break;
			if (theAddr == localHost) continue;
			
			//Name: lo0 MAC: 2535A38:815B400:24D8921:BFFFAE98:8157000:20 IP: 127.0.0.1
			//Name: en0 MAC: 0E:815B400:24D8921:BFFFAE98:8157000:20 IP: 192.168.1.91
			CNLog("Name: %s MAC: %s IP: %s\n", if_names[i], hw_addrs[i], ip_names[i]);
			s_sDeviceIdentifier = hw_addrs[i];
			
			//decided what adapter you want details for
			if (strncmp(if_names[i], "en", 2) == 0)
			{
				CNLog("ok");
				break;
			}
		}
		
		std::size_t pos;
		while ((pos = s_sDeviceIdentifier.find(":")) != std::string::npos)
		{
			s_sDeviceIdentifier = s_sDeviceIdentifier.substr(0, pos) + "-" + s_sDeviceIdentifier.substr(pos + 1);
		}
		CNLog("MAC: %s", s_sDeviceIdentifier.c_str());
		
		FreeAddresses();
	}
	return s_sDeviceIdentifier.c_str();
}

const char * CNClient::getDeviceModel(void)
{
	if (s_sDeviceModel.empty())
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		s_sDeviceModel = CNClient_escape(s_sDeviceModel,
										 [[UIDevice currentDevice] model]);
		[pool release];
	}
	return s_sDeviceModel.c_str();
}

const char * CNClient::getSystemName(void)
{
	if (s_sSystemName.empty())
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		s_sSystemName = CNClient_escape(s_sSystemName,
										[[UIDevice currentDevice] systemName]);
		[pool release];
	}
	return s_sSystemName.c_str();
}

const char * CNClient::getSystemVersion(void)
{
	if (s_sSystemVersion.empty())
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		s_sSystemVersion = CNClient_escape(s_sSystemVersion,
										   [[UIDevice currentDevice] systemVersion]);
		[pool release];
	}
	return s_sSystemVersion.c_str();
}

const char * CNClient::getVersion(void)
{
	if (s_sVersion.empty())
	{
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		NSString * string = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
		s_sVersion = CNClient_escape(s_sVersion,
									 string);
		[pool release];
	}
	return s_sVersion.c_str();
}

NS_CN_END
