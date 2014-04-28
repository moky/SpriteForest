//
//  CNArray.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-7-13.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#include "CNArray.h"

NS_CN_BEGIN

USING_NS_CC;

CCArray * CNArray::randomArray(cocos2d::CCArray *pArray, const unsigned int iMaxCount)
{
	if (!pArray || iMaxCount == 0)
	{
		CNLog("error");
		return NULL;
	}
	int iCount = pArray->count();
	if (iCount <= 1)
	{
		return pArray;
	}
	else if (iCount > iMaxCount)
	{
		CNLog("count:%d, max: %d", iCount, iMaxCount);
		iCount = iMaxCount;
	}
	
	srand((unsigned int)time(NULL));
	
	CCArray * arr1 = CCArray::arrayWithArray(pArray);
	CCArray * arr2 = CCArray::arrayWithCapacity(iCount);
	int index;
	for (int i = 0; i < iCount; i++)
	{
		index = (int)(rand() % arr1->count());
		CNLog("%d: pick an object at index %d / %d.", i, index, arr1->count());
		arr2->addObject(arr1->objectAtIndex(index));
		arr1->removeObjectAtIndex(index);
	}
	CNLog("count: %d", arr2->count());
	
	return arr2;
}

NS_CN_END
