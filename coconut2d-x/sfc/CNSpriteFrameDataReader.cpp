//
//  CNSpriteFrameDataReader.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "../cocoa/CNFileManager.h"

#include "CNSpriteFrameDataReader.h"

NS_CN_BEGIN

USING_NS_CC;

CCArray * CNSpriteFrameDataReader_getStringArrayFromBuffer(const unsigned char * pBuffer, const unsigned long iBufferLength)
{
	if (!pBuffer || iBufferLength == 0)
	{
		CNLog("could not happen");
		return NULL;
	}
	
	const char * p = (const char *)pBuffer;
	unsigned short * pCount = (unsigned short *)p; // 0 - 65535
	p += sizeof(unsigned short);
	
	CCArray * array = CCArray::arrayWithCapacity(*pCount);
	char * str = new char[256];
	
	unsigned char * pLen;
	for (int i = 0; i < *pCount; i++)
	{
		pLen = (unsigned char *)p; // 0 - 255
		p += sizeof(unsigned char);
		
		memset(str, 0, 256);
		snprintf(str, *pLen + 1, "%s", p); // would append '\0' to the end
		p += *pLen;
		
		CCString * pString = new CCString(str);
		array->addObject(pString);
		pString->release();
	}
	delete[] str;
	
	return array;
}

CNSpriteFrameDataReader::CNSpriteFrameDataReader(void)
: CNSpriteFrameData()
, m_pStringArray(NULL)
, m_pTexture(NULL)
{
	
}

CNSpriteFrameDataReader::~CNSpriteFrameDataReader(void)
{
	setStringArray(NULL);
	setTexture(NULL);
}

bool CNSpriteFrameDataReader::init(void)
{
	if (!CNSpriteFrameData::init())
	{
		CNLog("could not happen");
		return false;
	}
	setStringArray(NULL);
	setTexture(NULL);
	return true;
}

bool CNSpriteFrameDataReader::init(const std::string & sPath)
{
	if (!CNSpriteFrameData::init(sPath))
	{
		CNLog("could not read from path: %s", sPath.c_str());
		return false;
	}
	
	// init string array
	unsigned long iStringsBufferLength = 0;
	unsigned char * pStringsBuffer = getStringsBuffer(&iStringsBufferLength); // CNSpriteFrameData::getStringsBuffer(length)
	if (!pStringsBuffer || iStringsBufferLength == 0)
	{
		CNLog("failed to get frames buffer");
		return false;
	}
	setStringArray(CNSpriteFrameDataReader_getStringArrayFromBuffer(pStringsBuffer, iStringsBufferLength));
	
	// load texture & sprite frames onto the caches
	return loadTexture(sPath) && loadSpriteFrames();
}

bool CNSpriteFrameDataReader::loadTexture(const std::string &sRelativeFile)
{
	if (!checkDataFormat())
	{
		CNLog("error");
		return false;
	}
	
	std::string sTextureFilePath;
	int iTextureFileId = getTextureFileId();
	if (iTextureFileId < 0 || iTextureFileId >= m_pStringArray->count())
	{
		CNLog("error, iTextureFileId: %d", iTextureFileId);
		return false;
	}
	CCString * pTextureName = (CCString *)m_pStringArray->objectAtIndex(iTextureFileId);
	if (!pTextureName || pTextureName->length() == 0)
	{
		// replace file ext
		std::size_t pos = sRelativeFile.rfind(".");
		if (pos == std::string::npos)
		{
			CNLog("error path: %s", sRelativeFile.c_str());
			return false;
		}
		sTextureFilePath = sRelativeFile.substr(0, pos) + ".png";
		
		if (!CNFileManager::isExists(sTextureFilePath.c_str()))
		{
			sTextureFilePath = sRelativeFile.substr(0, pos) + ".pvr";
		}
		if (!CNFileManager::isExists(sTextureFilePath.c_str()))
		{
			sTextureFilePath = sRelativeFile.substr(0, pos) + ".pvr.ccz";
		}
		if (!CNFileManager::isExists(sTextureFilePath.c_str()))
		{
			CNLog("error: %s", sRelativeFile.c_str());
			return false;
		}
	}
	else
	{
		// replace file name
		std::size_t pos = sRelativeFile.rfind("/");
		if (pos == std::string::npos)
		{
			CNLog("error path: %s", sRelativeFile.c_str());
			return false;
		}
		sTextureFilePath = sRelativeFile.substr(0, pos + 1) + pTextureName->getCString();
	}
	
	// load texture image
	CNLog("loading texture image: %s", sTextureFilePath.c_str());
	setTexture(CCTextureCache::sharedTextureCache()->addImage(sTextureFilePath.c_str()));
	CNLog("texture image loaded: %s", sTextureFilePath.c_str());
	
	return m_pTexture != NULL;
}

bool CNSpriteFrameDataReader::loadSpriteFrames(void) const
{
	if (!checkDataFormat())
	{
		CNLog("error");
		return false;
	}
	if (!m_pTexture || !m_pStringArray || m_pStringArray->count() == 0)
	{
		CNLog("error");
		return false;
	}
	
	// load frames
	unsigned long iFramesBufferLength = 0;
	unsigned char * pFramesBuffer = getFramesBuffer(&iFramesBufferLength); // CNSpriteFrameData::getFramesBuffer(length)
	if (!pFramesBuffer || iFramesBufferLength == 0)
	{
		CNLog("failed to get frames buffer");
		return false;
	}
	
	CCSpriteFrameCache * pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCString * pSpriteName = NULL;
	CCSpriteFrame * pSpriteFrame = NULL;
	
	unsigned int iFrameCount = iFramesBufferLength / sizeof(CNSpriteFrameInfo);
	CNSpriteFrameInfo * pFrame = (CNSpriteFrameInfo *)pFramesBuffer;
	for (int pos = 0; pos < iFrameCount; pos++, pFrame++)
	{
		//CNLog("loading frame: %d", pos);
		if (pFrame->id >= m_pStringArray->count())
		{
			CNLog("error, frame id: %d", pFrame->id);
			continue;
		}
		// name
		pSpriteName = (CCString *)m_pStringArray->objectAtIndex(pFrame->id);
		if (!pSpriteName || pSpriteName->length() == 0)
		{
			CNLog("could not happen");
			continue;
		}
		// frame
		pSpriteFrame = new CCSpriteFrame();
		pSpriteFrame->initWithTexture(m_pTexture,
									  CCRect(pFrame->x, pFrame->y, pFrame->width, pFrame->height),
									  pFrame->rotated,
									  CCPoint(pFrame->offsetX, pFrame->offsetY),
									  CCSize(pFrame->originalWidth, pFrame->originalHeight)
									  );
		// add to cache
		pCache->addSpriteFrame(pSpriteFrame, pSpriteName->getCString());
		pSpriteFrame->release();
	}
	
	return iFrameCount > 0;
}

NS_CN_END
