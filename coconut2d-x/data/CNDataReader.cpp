//
//  CNDataReader.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNDataReader.h"

NS_CN_BEGIN

USING_NS_CC;

CCArray * CNDataReader_getStringArrayFromBufferThreadSafe(const unsigned char * pBuffer, const unsigned long iBufferLength)
{
	if (!pBuffer || iBufferLength == 0)
	{
		CNLog("could not happen");
		return NULL;
	}
	
	const char * p = (const char *)pBuffer;
	unsigned long * pCount = (unsigned long *)p; // 0 - 4,294,967,295 (4G)
	p += sizeof(unsigned long);
	
	CCArray * array = new CCArray();
	array->initWithCapacity(*pCount);
	char * str = new char[65536];
	
	unsigned short * pLen;
	for (int i = 0; i < *pCount; i++)
	{
		pLen = (unsigned short *)p; // 0 - 65535
		p += sizeof(unsigned short);
		
		memset(str, 0, 65536);
		snprintf(str, *pLen + 1, "%s", p); // would append '\0' to the end
		p += *pLen;
		
		CCString * pString = new CCString(str);
		array->addObject(pString);
		pString->release();
	}
	delete[] str;
	
	return array;
}

CNDataReader::CNDataReader(void)
: CNData()
, m_pStrings(NULL)
, m_pData(NULL)
, m_iItemIndex(0)
{
	
}

CNDataReader::~CNDataReader(void)
{
	CC_SAFE_RELEASE(m_pStrings);
	CC_SAFE_RELEASE(m_pData);
}

bool CNDataReader::init(void)
{
	if (!CNData::init())
	{
		return false;
	}
	CC_SAFE_RELEASE_NULL(m_pStrings);
	CC_SAFE_RELEASE_NULL(m_pData);
	m_iItemIndex = 0;
	return true;
}

bool CNDataReader::init(const std::string & sPath)
{
	if (!CNData::init(sPath))
	{
		CNLog("could not read from path: %s", sPath.c_str());
		return false;
	}
	
	// init string array
	unsigned long iStringsBufferLength = 0;
	unsigned char * pStringsBuffer = getStringsBuffer(&iStringsBufferLength); // CNData::getStringsBuffer(length)
	if (!pStringsBuffer || iStringsBufferLength == 0)
	{
		CNLog("failed to get frames buffer");
		return false;
	}
	m_pStrings = CNDataReader_getStringArrayFromBufferThreadSafe(pStringsBuffer, iStringsBufferLength);
	
	if (!m_pStrings || m_pStrings->count() == 0)
	{
		CNLog("string buffer empty");
		return false;
	}
	
	// parse items
	m_pData = parseRootThreadSafe();
	
	if (m_pData)
	{
		CNLog("OK, sPath: %s", sPath.c_str());
		return true;
	}
	else
	{
		CNLog("Error, sPath: %s", sPath.c_str());
		return false;
	}
}

CCObject * CNDataReader::getData(void) const
{
	return m_pData;
}

#pragma mark -

void CNDataReader::reset(void)
{
	m_iItemIndex = 0;
}

CNDataItem * CNDataReader::read(void)
{
	CNDataItem * pItem = getItem(m_iItemIndex);
	m_iItemIndex++;
	return pItem;
}

CCString * CNDataReader::getString(const unsigned int iLocation) const
{
	if (!m_pStrings || m_pStrings->count() <= iLocation)
	{
		CNLog("error, iLocation: %d", iLocation);
		return NULL;
	}
	return (CCString *)m_pStrings->objectAtIndex(iLocation);
}

#pragma mark -

CCObject * CNDataReader::parseRootThreadSafe(void)
{
	reset();
	CNDataItem * pItem = read();
	return parseItemThreadSafe(pItem);
}

CCObject * CNDataReader::parseItemThreadSafe(const CNDataItem * pItem)
{
	if (!pItem || pItem->reserved != '\0')
	{
		CNLog("error");
		return NULL;
	}
	
	if (pItem->type >= CNDataItemTypeUnknown)
	{
		CNLog("unrecognized type: %d", pItem->type);
		return NULL;
	}
	else if (pItem->type == CNDataItemTypeInteger)
	{
		CCString * pString = new CCString();
		pString->initWithFormat("%d", pItem->intValue);
		return pString;
	}
	else if (pItem->type == CNDataItemTypeFloat)
	{
		CCString * pString = new CCString();
		pString->initWithFormat("%f", pItem->floatValue);
		return pString;
	}
	else if (pItem->type == CNDataItemTypeString)
	{
		CCString * pString = getString(pItem->stringId);
		if (pString)
		{
			pString->retain();
		}
		return pString;
	}
	else if (pItem->type == CNDataItemTypeArray)
	{
		return parseArrayItemThreadSafe(pItem);
	}
	else if (pItem->type == CNDataItemTypeDictionary)
	{
		return parseDictionaryItemThreadSafe(pItem);
	}
	CNLog("could not happen");
	return NULL;
}

CCArray * CNDataReader::parseArrayItemThreadSafe(const CNDataItem * pItem)
{
	CCArray * pArray = new CCArray();
	pArray->initWithCapacity(pItem->count);
	
	for (int i = 0; i < pItem->count; i++)
	{
		CNDataItem * pChild = read();
		CCObject * pObj = parseItemThreadSafe(pChild);
		if (!pObj)
		{
			CNLog("error, i = %d", i);
			continue;
		}
		pArray->addObject(pObj);
		pObj->release();
	}
	
	return pArray;
}

CCDictionary * CNDataReader::parseDictionaryItemThreadSafe(const CNDataItem * pItem)
{
	CCDictionary * pDict = new CCDictionary();
	
	for (int i = 0; i < pItem->count; i++)
	{
		CNDataItem * pChild = read();
		CCString * pKey = pChild ? getString(pChild->key) : NULL;
		CCObject * pObj = parseItemThreadSafe(pChild);
		if (!pKey || pKey->length() == 0 || !pObj)
		{
			CNLog("error, i = %d", i);
			continue;
		}
		pDict->setObject(pObj, pKey->getCString());
		pObj->release();
	}
	
	return pDict;
}

NS_CN_END
