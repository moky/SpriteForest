//
//  CNDictionary.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-1.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "CNDictionary.h"

NS_CN_BEGIN

USING_NS_CC;

CCDictionary * CNDictionary::mergeDictionaries(cocos2d::CCDictionary *dict1, const cocos2d::CCDictionary *dict2)
{
	if (!dict1)
	{
		if (!dict2)
		{
			CNLog("empty dictionaries");
			return NULL;
		}
		dict1 = CCDictionary::dictionary();
	}
	
	CCDictElement * pElement = NULL;
	CCDICT_FOREACH(dict2, pElement)
	{
		const char * key = pElement->getStrKey();
		if (!key || strlen(key) == 0)
		{
			CNLog("could not happen");
			continue;
		}
		dict1->setObject(pElement->getObject(), key);
	}
	
	return dict1;
}

NS_CN_END
