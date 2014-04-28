//
//  CNDictionary.h
//  Coconut2D-X
//
//  Created by Moky on 12-12-1.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNDictionary_h
#define Coconut2D_X_CNDictionary_h

#include "../cnMacros.h"

NS_CN_BEGIN

//
// Convienient Dictionary Reader
//
class CNDictionary
{
public:
	
	// copy values from dict2 into dict1
	static cocos2d::CCDictionary * mergeDictionaries(cocos2d::CCDictionary * dict1, const cocos2d::CCDictionary * dict2);
	
#pragma mark Template
	
	template<class T>
	static inline T * objectForKey(const char * pszKey, cocos2d::CCDictionary * pDict)
	{
		return pDict ? dynamic_cast<T *>(pDict->objectForKey(pszKey)) : NULL;
	}
	
#pragma mark Static functions
	
	static inline cocos2d::CCObject * objectForKey(const char * pszKey, cocos2d::CCDictionary * pDict)
	{
		return pDict ? pDict->objectForKey(pszKey) : NULL;
	}
	
	static inline cocos2d::CCString * stringForKey(const char * pszKey, cocos2d::CCDictionary * pDict)
	{
		return objectForKey<cocos2d::CCString>(pszKey, pDict);
	}
	
	static inline cocos2d::CCDictionary * dictionaryForKey(const char * pszKey, cocos2d::CCDictionary * pDict)
	{
		return objectForKey<cocos2d::CCDictionary>(pszKey, pDict);
	}
	
	static inline cocos2d::CCArray * arrayForKey(const char * pszKey, cocos2d::CCDictionary * pDict)
	{
		return objectForKey<cocos2d::CCArray>(pszKey, pDict);
	}
};

NS_CN_END

#endif
