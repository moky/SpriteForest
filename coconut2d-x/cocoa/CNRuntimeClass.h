//
//  CNRuntimeClass.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CRuntimeClass_h
#define Coconut2D_X_CRuntimeClass_h

#include "../cnMacros.h"

#define CN_RUNTIME_CLASS_INIT(class, func) static bool _rtti_sb_##class = \
    coconut2d::CNRuntimeClass::addRuntimeClass(#class, (coconut2d::CNRuntimeClassFunc)&class::func);

NS_CN_BEGIN

typedef cocos2d::CCObject * (* CNRuntimeClassFunc)();

class CNRuntimeClass : public cocos2d::CCObject
{
private:
	const char * m_pszClassName;
	CNRuntimeClassFunc m_pfnCreateObject;
	
public:
	CNRuntimeClass(void);
	virtual ~CNRuntimeClass(void);
	
	void setClassName(const char * pszClassName);
	void setCreateObject(const CNRuntimeClassFunc pfnCreateObject);
	
	static bool addRuntimeClass(const char * pszClassName, const CNRuntimeClassFunc pfnCreateObject);
	static bool addRuntimeClass(CNRuntimeClass * pRuntimeClass);
	static bool addRuntimeClass(const char * pszClassName, CNRuntimeClass * pRuntimeClass);
	
	static cocos2d::CCObject * createObject(const char * pszClassName);
};

NS_CN_END

#endif
