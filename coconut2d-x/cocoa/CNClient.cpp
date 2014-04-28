//
//  CNClient.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-23.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <arpa/inet.h>

#include "CNClient.h"

NS_CN_BEGIN

USING_NS_CC;

static std::string s_sClientParameters;

const char * CNClient::getClientParameters(void)
{
	if (s_sClientParameters.empty())
	{
		s_sClientParameters = "";
		// client-version
		s_sClientParameters.append("client-version=").append(getVersion());
		
		// screen
		CCSize size = getScreenSize();
		CCFloat scale = getScreenScale();
		char szScreen[32];
		memset(szScreen, 0, 32);
		snprintf(szScreen, 32, "%.0fx%.0f@%.1f", size.width, size.height, scale);
		s_sClientParameters.append("&screen=").append(szScreen);
		
		// os
		std::string sOS = std::string(getSystemName()).append("/").append(getSystemVersion());
		s_sClientParameters.append("&os=").append(sOS);
		
		// device
		std::string sDevice = std::string(getDeviceModel()).append("/").append(getHardware());
		s_sClientParameters.append("&device=").append(sDevice);
		
		// imei
		s_sClientParameters.append("&imei=").append(getDeviceIdentifier());
	}
	
	return s_sClientParameters.c_str();
}

void CNClient_showNetworkInterfaces(void)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		CNLog("error socket: %d", fd);
		return;
	}
	struct ifconf ifc;
	struct ifreq ifs[64];
	memset(&ifc, 0, sizeof(ifc));
	memset(&ifs, 0, sizeof(ifs));
	ifc.ifc_len = sizeof(ifs);
	ifc.ifc_ifcu.ifcu_req = ifs;
	if (ioctl(fd, SIOCGIFCONF, &ifc))
	{
		CNLog("error");
		close(fd);
		return;
	}
	struct ifreq * ifr, * ifend;
	ifend = ifs + (ifc.ifc_len / sizeof(struct ifreq));
	struct ifreq ifreq;
	for (ifr = ifc.ifc_ifcu.ifcu_req; ifr < ifend; ifr++)
	{
		CNLog("if name: %s, family: %d", ifr->ifr_name, ifr->ifr_ifru.ifru_addr.sa_family);
		if (ifr->ifr_ifru.ifru_addr.sa_family == AF_INET)
		{
			memset(&ifreq, 0, sizeof(struct ifreq));
			strncpy(ifreq.ifr_name, ifr->ifr_name, sizeof(ifreq.ifr_name));
			if (ioctl(fd, SIOCGIFADDR, &ifreq) < 0)
			{
				CNLog("error");
				continue;
			}
			CNLog("ip: %s", inet_ntoa(((struct sockaddr_in *)&ifreq.ifr_ifru.ifru_addr)->sin_addr));
		}
	}
	
	close(fd);
}

int CNClient_checkSocket(int socket, const char * name)
{
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifreq));
	strcpy(ifr.ifr_name, name);
	return ioctl(socket, SIOCGIFADDR, &ifr);
}

bool CNClient::isConnected(void)
{
	CNLog("checking network...");
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		CNLog("error");
		return false;
	}
	return true;
}

bool CNClient::isWiFiActived(void)
{
	CNLog("checking wifi...");
//	CNClient_showNetworkInterfaces(); // test
	bool flag = false;
	
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		CNLog("error");
		return false;
	}
	
	std::string ss[] = {"en0", "en1", "wlan0", "wlan1", "eth0", "eth1"};
	int res;
	for (int i = 0; i < 6; i++)
	{
		res = CNClient_checkSocket(fd, ss[i].c_str());
		if (res != -1)
		{
			CNLog("found at %s", ss[i].c_str());
			flag = true;
			break;
		}
	}
	
	close(fd);
	return flag;
}

NS_CN_END
