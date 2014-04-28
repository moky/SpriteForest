//
//  CNRuntimeClass.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "CNRuntimeClass.h"

NS_CN_BEGIN

USING_NS_CC;

CNRuntimeClass::CNRuntimeClass(void)
: CCObject()
, m_pszClassName(NULL)
, m_pfnCreateObject(NULL)
{
	
}

CNRuntimeClass::~CNRuntimeClass(void)
{
	
}

void CNRuntimeClass::setClassName(const char * pszClassName)
{
	m_pszClassName = pszClassName;
}

void CNRuntimeClass::setCreateObject(const CNRuntimeClassFunc pfnCreateObject)
{
	m_pfnCreateObject = pfnCreateObject;
}

static CCDictionary * s_pRuntimeCreators = NULL;

bool CNRuntimeClass::addRuntimeClass(const char * pszClassName, const CNRuntimeClassFunc pfnCreateObject)
{
	if (!pszClassName || strlen(pszClassName) == 0 || !pfnCreateObject)
	{
		CNLog("error");
		return false;
	}
	CNRuntimeClass * pRTC = new CNRuntimeClass();
	if (!pRTC)
	{
		CNLog("could not happen!");
		return false;
	}
	pRTC->setClassName(pszClassName);
	pRTC->setCreateObject(pfnCreateObject);
	addRuntimeClass(pszClassName, pRTC);
	pRTC->release();
	return true;
}

bool CNRuntimeClass::addRuntimeClass(CNRuntimeClass * pRuntimeClass)
{
	return addRuntimeClass(pRuntimeClass->m_pszClassName, pRuntimeClass);
}

bool CNRuntimeClass::addRuntimeClass(const char * pszClassName, CNRuntimeClass * pRuntimeClass)
{
	if (!pszClassName || strlen(pszClassName) == 0)
	{
		CNLog("Error!");
		return false;
	}
	// lock
	if (!s_pRuntimeCreators)
	{
		s_pRuntimeCreators = new CCDictionary();
	}
	s_pRuntimeCreators->setObject(pRuntimeClass, pszClassName);
	// unlock
	return true;
}

CCObject * CNRuntimeClass::createObject(const char * pszClassName)
{
	if (!pszClassName || strlen(pszClassName) == 0)
	{
		CNLog("Error!");
		return NULL;
	}
	if (!s_pRuntimeCreators)
	{
		CNLog("Error: s_pRuntimeCreators not init");
		return NULL;
	}
	CNRuntimeClass * pRuntimeClass = (CNRuntimeClass *)s_pRuntimeCreators->objectForKey(pszClassName);
	if (!pRuntimeClass)
	{
		//CNLog("error: %s", pszClassName);
		return NULL;
	}
	if (!pRuntimeClass->m_pfnCreateObject)
	{
		CNLog("could not happen!");
		return NULL;
	}
	return (* pRuntimeClass->m_pfnCreateObject)();
}

NS_CN_END
