//
//  CNString.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-26.
//  Copyright (c) 2012年 Slanissue.com. All rights reserved.
//

#include "CNClient.h"

#include "CNString.h"

NS_CN_BEGIN

USING_NS_CC;

bool CNString::isNumeric(const std::string &string)
{
	int len = string.length();
	int cnt = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (string[i] == '-')
		{
			if (i > 0 || len == 1)
			{
				return false;
			}
		}
		else if (string[i] == '.')
		{
			if (++cnt > 1)
			{
				return false;
			}
		}
		else if ((string[i] < '0' || string[i] > '9'))
		{
			return false;
		}
	}
	return true;
}

bool CNString::isInteger(const std::string &string)
{
	int len = string.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (string[i] == '-')
		{
			if (i > 0 || len == 1)
			{
				return false;
			}
		}
		else if ((string[i] < '0' || string[i] > '9'))
		{
			return false;
		}
	}
	return true;
}

std::string & CNString::stringByAddingPercentEscapes(std::string &string)
{
	CNLog("not implement");
	return string;
}

std::string & CNString::stringByReplacingPercentEscapes(std::string &string)
{
	CNLog("not implement");
	return string;
}

std::string & CNString::stringByAddingUrlParameter(std::string &url, const std::string &key, const std::string &value)
{
	std::string fragment("");
	std::size_t pos = url.find("#");
	if (pos != std::string::npos)
	{
		fragment = url.substr(pos);
		url = url.substr(0, pos);
	}
	
	// TODO: check whether the key exists...
	
	// TODO: escape value...
	
	pos = url.find("?");
	if (pos != std::string::npos)
	{
		url.append("&").append(key).append("=").append(value);
	}
	else
	{
		url.append("?").append(key).append("=").append(value);
	}
	
	url.append(fragment);
	return url;
}

bool CNString::isDynamicURLString(const std::string &url)
{
	return url.rfind("cgi-bin") != std::string::npos;
}

std::string & CNString::stringByAddingClientParameters(std::string &url)
{
	if (url.rfind("client-version=") != std::string::npos)
	{
		CNLog("client parameters has already added: %s", url.c_str());
		return url;
	}
	
	std::string fragment("");
	std::size_t pos = url.find("#");
	if (pos != std::string::npos)
	{
		fragment = url.substr(pos);
		url = url.substr(0, pos);
	}
	// append client stat parameters
	const char * pszClient = CNClient::getClientParameters();
	pos = url.find("?");
	if (pos != std::string::npos)
	{
		url.append("&").append(pszClient);
	}
	else
	{
		url.append("?").append(pszClient);
	}
	
	if (!fragment.empty())
	{
		url.append(fragment);
	}
	
	return url;
}

CCArray * CNString::split(const std::string &string, const std::string &pattern)
{
	int len = string.length();
	int gap = pattern.length();
	std::string::size_type pos;
	std::string fragment;
	
	CCArray * array = CCArray::array();
	for (int i = 0; i < len; i += gap)
	{
		pos = string.find(pattern, i);
		if (pos == std::string::npos)
		{
			pos = len;
		}
		fragment = string.substr(i, pos - i);
		array->addObject(CCString::stringWithCString(fragment.c_str()));
		i = pos;
	}
	return array;
}

std::string & CNString::simplifyPath(std::string &string)
{
	std::size_t pos1, pos2;
	while ((pos1 = string.find("/../")) != std::string::npos)
	{
		if (pos1 < 1 || string[pos1 - 1] == '/')
		{
			CNLog("error: %s", string.c_str());
			break;
		}
		pos2 = string.rfind("/", pos1 - 1);
		if (pos2 == std::string::npos)
		{
			pos2 = - 1;
		}
		string = string.substr(0, pos2 + 1) + string.substr(pos1 + 4);
	}
	return string;
}

bool CNString::containsInArray(const std::string &string, const cocos2d::CCArray *pArray)
{
	cocos2d::CCObject * pObj = NULL;
	CCARRAY_FOREACH(pArray, pObj)
	{
		if (cocos2d::CCString * str = dynamic_cast<cocos2d::CCString *>(pObj))
		{
			CNLog("comparing %s & %s", string.c_str(), str->getCString());
			if (strcmp(string.c_str(), str->getCString()) == 0)
			{
				CNLog("right!");
				return true;
			}
		}
	}
	return false;
}

std::string & CNString::stringWithFormat(std::string &string, const char *format, ...)
{
	va_list ap;
    va_start(ap, format);
	
    char * pBuf = (char *)malloc(1024 * 64);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, 1024 * 64, format, ap);
        string = pBuf;
        free(pBuf);
    }
	
    va_end(ap);
	return string;
}

NS_CN_END
