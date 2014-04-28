//
//  CNDataTransformer.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNDataTransformer.h"
#include "../cocoa/CNString.h"

NS_CN_BEGIN

USING_NS_CC;

unsigned char * CNDataTransformer_createBufferWithStringArray(CCArray * pArray,
															  unsigned long * pBufferLength)
{
	if (!pArray || pArray->count() == 0 || !pBufferLength)
	{
		return NULL;
	}
	CCAssert(pArray->count() < 65536 * 256, "too big array");
	
	unsigned int iMaxLength = 65536 * pArray->count();
	
	unsigned char * pBuffer = (unsigned char *)malloc(iMaxLength);
	memset(pBuffer, 0, iMaxLength);
	char * p = (char *)pBuffer;
	
	// save 'count' first
	unsigned long * pCount = (unsigned long *)p; // 0 - 4,294,967,295 (4G)
	p += sizeof(unsigned long);
	*pCount = pArray->count();
	
	unsigned short * pLen;
	for (int i = 0; i < *pCount; i++)
	{
		CCString * pString = (CCString *)pArray->objectAtIndex(i);
		CCAssert(pString->length() < 65536, "too long string");
		
		pLen = (unsigned short *)p; // 0 - 65535
		p += sizeof(unsigned short);
		*pLen = pString->length();
		
		sprintf(p, "%s", pString->getCString());
		p += *pLen;
	}
	
	*pBufferLength = (unsigned char *)p - pBuffer;
	return pBuffer;
}

int CNDataTransformer_indexForString(CCString * pString, CCArray * pArray)
{
	if (!pString)
	{
		return -1;
	}
	unsigned int iCount = pArray->count();
	unsigned int index = 0;
	for (; index < iCount; index++)
	{
		CCString * pValue = (CCString *)pArray->objectAtIndex(index);
		if (strcmp(pString->getCString(), pValue->getCString()) == 0)
		{
			break;
		}
	}
	if (index >= iCount)
	{
//		CNLog("adding new string %s to array, index: %d", pString->getCString(), pArray->count());
		pArray->addObject(pString);
	}
	
	return index;
}

int CNDataTransformer_processData(CNDataItem * pItemBuffer, unsigned int iPlaceLeft,
								  CCObject * pObject, CCArray * pStringsArray); // pre-defined

int CNDataTransformer_processString(CNDataItem * pItemBuffer, unsigned int iPlaceLeft,
									CCString * pString, CCArray * pStringsArray)
{
	if (CNString::isNumeric(pString->getCString()))
	{
		if (CNString::isInteger(pString->getCString()))
		{
			pItemBuffer->type = CNDataItemTypeInteger;
			pItemBuffer->intValue = pString->intValue();
		}
		else
		{
			pItemBuffer->type = CNDataItemTypeFloat;
			pItemBuffer->floatValue = pString->floatValue();
		}
		return 1;
	}
	
	int index = CNDataTransformer_indexForString(pString, pStringsArray);
	if (index < 0)
	{
		CNLog("could not happen");
		return 0;
	}
	pItemBuffer->type = CNDataItemTypeString;
	pItemBuffer->stringId = index;
	return 1;
}

int CNDataTransformer_processArray(CNDataItem * pItemBuffer, unsigned int iPlaceLeft,
								   CCArray * pArray, CCArray * pStringsArray)
{
	int iCount = 0;
	pItemBuffer->type = CNDataItemTypeArray;
	pItemBuffer->count = pArray->count();
	iCount++;
	
	CNDataItem * pChild = pItemBuffer + 1; // first child, starts from next space
	CCObject * pObject = NULL;
	CCARRAY_FOREACH(pArray, pObject)
	{
		if (!pObject)
		{
			CNLog("could not happen");
			continue;
		}
		int cnt = CNDataTransformer_processData(pChild, iPlaceLeft - iCount, pObject, pStringsArray);
		if (cnt <= 0)
		{
			CNLog("error");
			continue;
		}
		pChild += cnt;
		iCount += cnt;
	}
	return iCount;
}

int CNDataTransformer_processDictionary(CNDataItem * pItemBuffer, unsigned int iPlaceLeft,
										CCDictionary * pDict, CCArray * pStringsArray)
{
	int iCount = 0;
	pItemBuffer->type = CNDataItemTypeDictionary;
	pItemBuffer->count = pDict->count();
	iCount++;
	
	CNDataItem * pChild = pItemBuffer + 1; // first child, starts from next space
	CCDictElement * pElement = NULL;
	CCDICT_FOREACH(pDict, pElement)
	{
		CCString * pKey = new CCString(pElement->getStrKey());
		int index = CNDataTransformer_indexForString(pKey, pStringsArray);
		pKey->release();
		if (index < 0 || pElement->getObject() == NULL)
		{
			CNLog("could not happen");
			continue;
		}
		pChild->key = index;
		
		int cnt = CNDataTransformer_processData(pChild, iPlaceLeft - iCount, pElement->getObject(), pStringsArray);
		if (cnt <= 0)
		{
			CNLog("error");
			continue;
		}
		pChild += cnt;
		iCount += cnt;
	}
	return iCount;
}

int CNDataTransformer_processData(CNDataItem * pItemBuffer, unsigned int iPlaceLeft,
								   CCObject * pObject, CCArray * pStringsArray)
{
	if (iPlaceLeft == 0)
	{
		CNLog("not enough space");
		return -1;
	}
	int iCount = 0;
	if (!pItemBuffer || !pStringsArray)
	{
		CNLog("could not happen");
	}
	else if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pObject))
	{
		iCount += CNDataTransformer_processDictionary(pItemBuffer, iPlaceLeft, pDict, pStringsArray);
	}
	else if (CCArray * pArray = dynamic_cast<CCArray *>(pObject))
	{
		iCount += CNDataTransformer_processArray(pItemBuffer, iPlaceLeft, pArray, pStringsArray);
	}
	else if (CCString * pString = dynamic_cast<CCString *>(pObject))
	{
		iCount += CNDataTransformer_processString(pItemBuffer, iPlaceLeft, pString, pStringsArray);
	}
	else
	{
		CNLog("Warning: Unknown Object.");
		pItemBuffer->type = CNDataItemTypeUnknown;
		iCount++;
	}
	return iCount;
}

unsigned char * CNDataTransformer_createItemsBuffer(CCObject * pData, unsigned long * pBufferLength, CCArray * pStringsArray)
{
	if (!pData || !pBufferLength || !pStringsArray)
	{
		CNLog("error");
		return NULL;
	}
	
	unsigned int iMaxItems = 65536;
	unsigned long iBufferLength = sizeof(CNDataItem) * iMaxItems;
	
	CNDataItem * pItemsBuffer = (CNDataItem *)malloc(iBufferLength);
	if (!pItemsBuffer)
	{
		CNLog("not enough memory");
		return NULL;
	}
	memset(pItemsBuffer, 0, iBufferLength);
	
	int iCount = CNDataTransformer_processData(pItemsBuffer, iMaxItems, pData, pStringsArray);
	if (iCount <= 0)
	{
		CNLog("error");
		CC_SAFE_FREE(pItemsBuffer);
	}
	*pBufferLength = sizeof(CNDataItem) * iCount;
	return (unsigned char *)pItemsBuffer;
}

bool CNDataTransformer::init(const std::string & sPath)
{
	if (sPath.empty())
	{
		CNLog("path is NULL");
		return false;
	}
	
	std::size_t pos = sPath.rfind(".");
	if (pos == std::string::npos)
	{
		CNLog("error path: %s", sPath.c_str());
		return false;
	}
	std::string ext = sPath.substr(pos + 1);
	if (ext.empty())
	{
		CNLog("error path: %s", sPath.c_str());
		return false;
	}
	else if (strcasecmp(ext.c_str(), "plist") == 0)
	{
		CNLog("init sprite frame data as a dictionary: %s", sPath.c_str());
		CCDictionary * pDict = CCDictionary::dictionaryWithContentsOfFile(sPath.c_str());
		return init(pDict);
	}
	CNLog("init sprite frame data as binary file: %s", sPath.c_str());
	return CNData::init(sPath);
}

bool CNDataTransformer::init(CCDictionary * pDict)
{
	if (!pDict)
	{
		return false;
	}
	
	CCArray * pStringsArray = new CCArray();
	pStringsArray->initWithCapacity(65536);
	
	// items buffer
	unsigned long iItemsBufferLength = 0;
	unsigned char * pItemsBuffer = CNDataTransformer_createItemsBuffer(pDict, &iItemsBufferLength, pStringsArray);
	if (!pItemsBuffer || iItemsBufferLength == 0)
	{
		CNLog("error");
		CC_SAFE_FREE(pItemsBuffer);
		pStringsArray->release();
		return false;
	}
	
	// string array buffer
	unsigned long iStringsBufferLength = 0;
	unsigned char * pStringsBuffer = CNDataTransformer_createBufferWithStringArray(pStringsArray, &iStringsBufferLength);
	if (!pStringsBuffer || iStringsBufferLength == 0)
	{
		CNLog("error");
		CC_SAFE_FREE(pStringsBuffer);
		CC_SAFE_FREE(pItemsBuffer);
		pStringsArray->release();
		return false;
	}
	
	//---- OK!
	CNLog("iItemsBufferLength = %ld, iStringsBufferLength = %ld", iItemsBufferLength, iStringsBufferLength);
	
	unsigned long iBufferLength = sizeof(CNDataHead) + iItemsBufferLength + iStringsBufferLength;
	CNLog("iBufferLength = %ld", iBufferLength);
	
	if (!CNData::init(iBufferLength))
	{
		CC_SAFE_FREE(pStringsBuffer);
		CC_SAFE_FREE(pItemsBuffer);
		pStringsArray->release();
		return false;
	}
	
	// init head
	unsigned long iHeadOffset = 0;
	unsigned long iHeadLength = sizeof(CNDataHead);
	CNDataHead * pHead = (CNDataHead *)&m_pDataBuffer[iHeadOffset];
	
	// copy items buffer
	unsigned long iItemsBufferOffset = iHeadOffset + iHeadLength;
	memcpy(&m_pDataBuffer[iItemsBufferOffset], pItemsBuffer, iItemsBufferLength);
	pHead->body.itemsBuffer.offset = iItemsBufferOffset;
	pHead->body.itemsBuffer.length = iItemsBufferLength;
	
	// copy strings array buffer
	unsigned long iStringsBufferOffset = iItemsBufferOffset + iItemsBufferLength;
	memcpy(&m_pDataBuffer[iStringsBufferOffset], pStringsBuffer, iStringsBufferLength);
	pHead->body.stringsBuffer.offset = iStringsBufferOffset;
	pHead->body.stringsBuffer.length = iStringsBufferLength;
	
	CC_SAFE_FREE(pStringsBuffer);
	CC_SAFE_FREE(pItemsBuffer);
	pStringsArray->release();
	
	m_bIsDataValid = checkDataFormat();
	return m_bIsDataValid;
}

NS_CN_END
