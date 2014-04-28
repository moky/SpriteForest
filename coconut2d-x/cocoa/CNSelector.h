//
//  CNSelector.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-28.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNSelector_h
#define Coconut2D_X_CNSelector_h

#include "../cnMacros.h"

NS_CN_BEGIN

#define CN_SELECTORS(SEL, getter, super, ...) /* SEL getSelector(const char *) begin */ \
public: \
    virtual SEL getter(const char * pszName) const \
    { \
        SEL sel = selector<SEL>(pszName, __VA_ARGS__); \
        return sel ? sel : super::getter(pszName); \
    } \
/* SEL getSelector(const char *) end */

#define CN_SELECTOR(super, ...)   CN_SELECTORS(cocos2d::SEL_CallFunc,  getSelector,  super, __VA_ARGS__)
#define CN_SELECTOR_O(super, ...) CN_SELECTORS(cocos2d::SEL_CallFuncO, getSelectorO, super, __VA_ARGS__)

class CNSelectorDelegate
{
public:
	virtual cocos2d::SEL_CallFunc  getSelector(const char * pszName) const
	{
		CNLog("cannot get selector: %s", pszName);
		return NULL;
	}
	virtual cocos2d::SEL_CallFuncO getSelectorO(const char * pszName) const
	{
		CNLog("cannot get selector: %s", pszName);
		return NULL;
	}
	
protected:
	template<typename SEL>
	SEL selector(const char * pszName, ...) const;
};

#pragma mark -

template<typename SEL>
SEL CNSelectorDelegate::selector(const char * pszName, ...) const
{
	if (!pszName || strlen(pszName) == 0)
	{
		CNLog("error selector");
		return NULL;
	}
	CNLog("searching selector: %s", pszName);
	
	const char * sz = NULL;
	SEL sel = NULL;
	
	va_list ap;
	va_start(ap, pszName);
	
	do
	{
		sz = va_arg(ap, const char *);
		if (sz == NULL)
		{
			sel = NULL;
			break;
		}
		sel = va_arg(ap, SEL);
		if (strcasecmp(sz, pszName) == 0)
		{
			CNLog("found it!");
			break;
		}
	}
	while (true);
	
	va_end(ap);
	
	return sel;
}

NS_CN_END

#endif
