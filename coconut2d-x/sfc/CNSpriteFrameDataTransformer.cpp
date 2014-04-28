//
//  CNSpriteFrameDataTransformer.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNSpriteFrameDataTransformer.h"

NS_CN_BEGIN

USING_NS_CC;

unsigned char * CNSpriteFrameDataTransformer_createBufferWithStringArray(CCArray * pArray,
																		 unsigned long * pBufferLength)
{
	if (!pArray || pArray->count() == 0)
	{
		return NULL;
	}
	CCAssert(pArray->count() < 65536, "too big array");
	
	unsigned long iMaxLength = 256 * pArray->count();
	
	unsigned char * pBuffer = (unsigned char *)malloc(iMaxLength);
	memset(pBuffer, 0, iMaxLength);
	char * p = (char *)pBuffer;
	
	// save 'count' first
	unsigned short * pCount = (unsigned short *)p; // 0 - 65535
	p += sizeof(unsigned short);
	*pCount = pArray->count();
	
	unsigned char * pLen;
	for (int i = 0; i < *pCount; i++)
	{
		CCString * pString = (CCString *)pArray->objectAtIndex(i);
		CCAssert(pString->length() < 256, "too long string");
		
		pLen = (unsigned char *)p; // 0 - 255
		p += sizeof(unsigned char);
		*pLen = pString->length();
		
		sprintf(p, "%s", pString->getCString());
		p += *pLen;
	}
	
	*pBufferLength = (unsigned char *)p - pBuffer;
	return pBuffer;
}

int CNSpriteFrameDataTransformer_indexForString(CCString * pString, CCArray * pArray)
{
	if (!pString)
	{
		return -500;
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
		CNLog("could not happen, %s not exists in this array!", pString->getCString());
		return -1;
	}
	
	return index;
}

void CNSpriteFrameDataTransformer_processFrame(const int format,
											   CCDictionary * pFrameDict,
											   CNSpriteFrameInfo * pFrameBuffer)
{
	if (format == 0)
	{
		pFrameBuffer->x = pFrameDict->valueForKey("x")->floatValue();
		pFrameBuffer->y = pFrameDict->valueForKey("y")->floatValue();
		pFrameBuffer->width = pFrameDict->valueForKey("width")->floatValue();
		pFrameBuffer->height = pFrameDict->valueForKey("height")->floatValue();
		
		pFrameBuffer->offsetX = pFrameDict->valueForKey("offsetX")->floatValue();
		pFrameBuffer->offsetY = pFrameDict->valueForKey("offsetY")->floatValue();
		
		pFrameBuffer->originalWidth = pFrameDict->valueForKey("originalWidth")->intValue();
		pFrameBuffer->originalHeight = pFrameDict->valueForKey("originalHeight")->intValue();
		// check ow/oh
		if(!pFrameBuffer->originalWidth || !pFrameBuffer->originalHeight)
		{
			CNLog("WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
		}
		// abs ow/oh
		pFrameBuffer->originalWidth = abs(pFrameBuffer->originalWidth);
		pFrameBuffer->originalHeight = abs(pFrameBuffer->originalHeight);
		
		pFrameBuffer->rotated = false;
	}
	else if (format == 1 || format == 2)
	{
		CCRect frame = CCRectFromString(pFrameDict->valueForKey("frame")->getCString());
		CCPoint offset = CCPointFromString(pFrameDict->valueForKey("offset")->getCString());
		CCSize sourceSize = CCSizeFromString(pFrameDict->valueForKey("sourceSize")->getCString());
		bool rotated = (format == 2) ? pFrameDict->valueForKey("rotated")->boolValue() : false;
		
		pFrameBuffer->x = frame.origin.x;
		pFrameBuffer->y = frame.origin.y;
		pFrameBuffer->width = frame.size.width;
		pFrameBuffer->height = frame.size.height;
		
		pFrameBuffer->offsetX = offset.x;
		pFrameBuffer->offsetY = offset.y;
		
		pFrameBuffer->originalWidth = sourceSize.width;
		pFrameBuffer->originalHeight = sourceSize.height;
		
		pFrameBuffer->rotated = rotated;
	}
	else if (format == 3)
	{
		CCSize spriteSize = CCSizeFromString(pFrameDict->valueForKey("spriteSize")->getCString());
		CCPoint spriteOffset = CCPointFromString(pFrameDict->valueForKey("spriteOffset")->getCString());
		CCSize spriteSourceSize = CCSizeFromString(pFrameDict->valueForKey("spriteSourceSize")->getCString());
		CCRect textureRect = CCRectFromString(pFrameDict->valueForKey("textureRect")->getCString());
		bool textureRotated = pFrameDict->valueForKey("textureRotated")->boolValue();
		
		pFrameBuffer->x = textureRect.origin.x;
		pFrameBuffer->y = textureRect.origin.y;
		pFrameBuffer->width = spriteSize.width;
		pFrameBuffer->height = spriteSize.height;
		
		pFrameBuffer->offsetX = spriteOffset.x;
		pFrameBuffer->offsetY = spriteOffset.y;
		
		pFrameBuffer->originalWidth = spriteSourceSize.width;
		pFrameBuffer->originalHeight = spriteSourceSize.height;
		
		pFrameBuffer->rotated = textureRotated;
	}
	else
	{
		CNLog("unsupported format: %d", format);
	}
}

unsigned char * CNSpriteFrameDataTransformer_createFramesBuffer(const int format,
																CCDictionary * pFrames,
																unsigned long * pBufferLength,
																CCArray * pStrings)
{
	if (!pFrames || !pStrings || !pBufferLength)
	{
		CNLog("error");
		return NULL;
	}
	
	CCArray * pKeys = pFrames->allKeys();
	
	// create buffer
	unsigned long iBufferLength = sizeof(CNSpriteFrameInfo) * pKeys->count();
	unsigned char * pBuffer = (unsigned char *)malloc(iBufferLength);
	if (!pBuffer)
	{
		CNLog("not enough memory");
		return NULL;
	}
	memset(pBuffer, 0, iBufferLength);
	CNSpriteFrameInfo * pFrameBuffer = (CNSpriteFrameInfo *)pBuffer;
	
	// start processing frames
	for (int index = 0; index < pKeys->count(); index++, pFrameBuffer++)
	{
		CCString * pKey = (CCString *)pKeys->objectAtIndex(index);
		CCDictionary * pFrameDict = (CCDictionary *)pFrames->objectForKey(pKey->getCString());
		CCAssert(pKey && pFrameDict, "");
		int iFrameId = CNSpriteFrameDataTransformer_indexForString(pKey, pStrings);
		if (iFrameId < 0)
		{
			CNLog("could not happen!");
			continue;
		}
		pFrameBuffer->id = iFrameId;
		CNSpriteFrameDataTransformer_processFrame(format, pFrameDict, pFrameBuffer);
	}
	
	*pBufferLength = iBufferLength;
	return pBuffer;
}

bool CNSpriteFrameDataTransformer::init(const std::string & sPath)
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
	return CNSpriteFrameData::init(sPath);
}

bool CNSpriteFrameDataTransformer::init(CCDictionary * pDict)
{
	if (!pDict)
	{
		return false;
	}
	
	CCDictionary * pMetaData = (CCDictionary *)pDict->objectForKey("metadata");
	CCDictionary * pFrames = (CCDictionary *)pDict->objectForKey("frames");
	if (!pMetaData || !pFrames)
	{
		CNLog("error");
		return false;
	}
	
	int format = 0;
	if (pMetaData)
	{
		format = pMetaData->valueForKey("format")->intValue();
	}
	
	// textureFileName
	CCString * pTextureFilename = (CCString *)pMetaData->objectForKey("textureFileName");
	if (!pTextureFilename)
	{
		pTextureFilename = CCString::stringWithCString("");
	}
	
	CCArray * pStrings = pFrames->allKeys();
	pStrings->addObject(pTextureFilename);
	
	// string array
	unsigned long iStringsBufferLength = 0;
	unsigned char * pStringsBuffer = CNSpriteFrameDataTransformer_createBufferWithStringArray(pStrings, &iStringsBufferLength);
	if (!pStringsBuffer || iStringsBufferLength == 0)
	{
		CNLog("error");
		CC_SAFE_FREE(pStringsBuffer);
		return false;
	}
	
	// frames
	unsigned long iFramesBufferLength = 0;
	unsigned char * pFramesBuffer = CNSpriteFrameDataTransformer_createFramesBuffer(format, pFrames, &iFramesBufferLength, pStrings);
	if (!pFramesBuffer || iFramesBufferLength == 0)
	{
		CNLog("error");
		CC_SAFE_FREE(pFramesBuffer);
		CC_SAFE_FREE(pStringsBuffer);
		return false;
	}
	
	//---- OK!
	CNLog("iStringsBufferLength = %ld, iFramesBufferLength = %ld", iStringsBufferLength, iFramesBufferLength);
	
	unsigned long iBufferLength = sizeof(CNSpriteFrameDataHead) + iStringsBufferLength + iFramesBufferLength;
	CNLog("iBufferLength = %ld", iBufferLength);
	
	if (!CNSpriteFrameData::init(iBufferLength))
	{
		CC_SAFE_FREE(pFramesBuffer);
		CC_SAFE_FREE(pStringsBuffer);
		return false;
	}
	
	// init head
	unsigned long iHeadOffset = 0;
	unsigned long iHeadLength = sizeof(CNSpriteFrameDataHead);
	CNSpriteFrameDataHead * pHead = (CNSpriteFrameDataHead *)&m_pDataBuffer[iHeadOffset];
	
	// texture file id
	pHead->info.textureFileId = pStrings->indexOfObject(pTextureFilename);
	
	// copy frames buffer
	unsigned long iFramesBufferOffset = iHeadOffset + iHeadLength;
	memcpy(&m_pDataBuffer[iFramesBufferOffset], pFramesBuffer, iFramesBufferLength);
	pHead->info.framesBuffer.offset = iFramesBufferOffset;
	pHead->info.framesBuffer.length = iFramesBufferLength;
	
	// copy strings array buffer
	unsigned long iStringsBufferOffset = iFramesBufferOffset + iFramesBufferLength;
	memcpy(&m_pDataBuffer[iStringsBufferOffset], pStringsBuffer, iStringsBufferLength);
	pHead->info.stringsBuffer.offset = iStringsBufferOffset;
	pHead->info.stringsBuffer.length = iStringsBufferLength;
	
	CC_SAFE_FREE(pStringsBuffer);
	CC_SAFE_FREE(pFramesBuffer);
	
	m_bIsDataValid = checkDataFormat();
	return m_bIsDataValid;
}

NS_CN_END
