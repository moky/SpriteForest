//
//  CNSpriteFrameData.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNSpriteFrameData.h"

#include "../cocoa/CNFileManager.h"

NS_CN_BEGIN

#define CN_SFC_HEAD_VERSION 0x01
#define CN_SFC_VERSION      0x01

USING_NS_CC;

CNSpriteFrameData::CNSpriteFrameData(void)
: m_pDataBuffer(NULL)
, m_iBufferLength(0)
, m_bIsDataValid(false)
{
	
}

CNSpriteFrameData::~CNSpriteFrameData(void)
{
	CC_SAFE_FREE(m_pDataBuffer);
}

bool CNSpriteFrameData::init(void)
{
	CC_SAFE_FREE(m_pDataBuffer);
	m_pDataBuffer = NULL;
	m_iBufferLength = 0;
	m_bIsDataValid = false;
	return true;
}

bool CNSpriteFrameData::init(const unsigned long iBufferLength)
{
	if (iBufferLength <= sizeof(CNSpriteFrameDataHead))
	{
		CNLog("not enough buffer length: %ld", iBufferLength);
		return false;
	}
	
	if (!init())
	{
		return false;
	}
	
	m_pDataBuffer = (unsigned char *)malloc(iBufferLength);
	if (!m_pDataBuffer)
	{
		CNLog("not enough memory");
		return NULL;
	}
	m_iBufferLength = iBufferLength;
	
	// init the buffer
	memset(m_pDataBuffer, 0, m_iBufferLength);
	
	CNSpriteFrameDataHead * pHeadInfo = (CNSpriteFrameDataHead *)m_pDataBuffer;
	
	// protocol
	pHeadInfo->format[0] = 'S';
	pHeadInfo->format[1] = 'F';
	pHeadInfo->format[2] = 'C';
	pHeadInfo->format[3] = '\0';
	
	pHeadInfo->headVersion = CN_SFC_HEAD_VERSION;
	pHeadInfo->version     = CN_SFC_VERSION;
	
	pHeadInfo->fileLength = m_iBufferLength;
	
	// descriptions
	time_t now = time(NULL);
	tm * tm = gmtime(&now);
	
	snprintf((char *)pHeadInfo->description, sizeof(pHeadInfo->description),
			 "SpriteFrameCache File. Generated at %d-%d-%d %d:%d:%d",
			 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	
	snprintf((char *)pHeadInfo->copyright, sizeof(pHeadInfo->copyright),
			 "Copyright %d Slanissue Inc.", tm->tm_year + 1900);
	
	snprintf((char *)pHeadInfo->author, sizeof(pHeadInfo->author),
			 "Author: Moky@Beva.com, %d-%d-%d", 2013, 1, 3);
	
	return true;
}

bool CNSpriteFrameData::init(const std::string & sPath)
{
	if (!init())
	{
		return false;
	}
	std::string filename(sPath);
	filename = CCFileUtils::fullPathFromRelativePath(filename.c_str());
	if (!CNFileManager::isExists(filename.c_str()))
	{
		CNLog("file not found: %s", filename.c_str());
		return false;
	}
	
	CCFileData data(filename.c_str(), "rb");
	unsigned char * pBuffer = data.getBuffer();
	unsigned long lSize = data.getSize();
	if (!pBuffer || lSize <= sizeof(CNSpriteFrameDataHead))
	{
		CNLog("invalid data file: %s, size: %ld", filename.c_str(), lSize);
		return false;
	}
	CNLog("read %ld bytes from file: %s", lSize, filename.c_str());
	
	m_pDataBuffer = (unsigned char *)malloc(lSize);
	if (!m_pDataBuffer)
	{
		CNLog("not enough memory, size: %ld", lSize);
		return false;
	}
	m_iBufferLength = lSize;
	memset(m_pDataBuffer, 0, m_iBufferLength);
	memcpy(m_pDataBuffer, pBuffer, m_iBufferLength);
	
	m_bIsDataValid = checkDataFormat();
	return m_bIsDataValid;
}

bool CNSpriteFrameData::saveToFile(const std::string & sPath) const
{
	if (sPath.empty())
	{
		return false;
	}
	if (!checkDataFormat())
	{
		CNLog("data format error");
		return false;
	}
	
	CNLog("saving to binary file: %s", sPath.c_str());
	
	FILE * fp = fopen(sPath.c_str(), "wb");
	if (!fp)
	{
		CNLog("failed to open file for write: %s", sPath.c_str());
		return false;
	}
	unsigned long length = fwrite(m_pDataBuffer, sizeof(unsigned char), m_iBufferLength, fp);
	fclose(fp);
	CNLog("buffer length: %ld, written length: %ld", m_iBufferLength, length);
	return length == m_iBufferLength;
}

bool CNSpriteFrameData::checkDataFormat(void) const
{
	if (m_bIsDataValid)
	{
		// the data had been checked before
		// quick return here
		return true;
	}
	
	if (!m_pDataBuffer || m_iBufferLength <= sizeof(CNSpriteFrameDataHead))
	{
		CNLog("data buffer not init");
		return false;
	}
	
	// check head
	CNSpriteFrameDataHead * pHead = (CNSpriteFrameDataHead *)m_pDataBuffer;
	if (pHead->format[0] != 'S' || pHead->format[1] != 'F' || pHead->format[2] != 'C' || pHead->format[3] != '\0')
	{
		CNLog("format sign error: [%c%c%c%c]", pHead->format[0], pHead->format[1], pHead->format[2], pHead->format[3]);
		return false;
	}
	
	if (pHead->headVersion != CN_SFC_HEAD_VERSION || pHead->version != CN_SFC_VERSION)
	{
		CNLog("versions error: %d.%d", pHead->headVersion, pHead->version);
		return false;
	}
	
	if (pHead->fileLength != m_iBufferLength)
	{
		CNLog("file length error: %ld != %ld", pHead->fileLength, m_iBufferLength);
		return false;
	}
	
	// check buffer info
	if (pHead->info.framesBuffer.offset != sizeof(CNSpriteFrameDataHead) ||
		pHead->info.framesBuffer.length == 0)
	{
		CNLog("frames buffer info error");
		return false;
	}
	
	if (pHead->info.stringsBuffer.offset != pHead->info.framesBuffer.offset + pHead->info.framesBuffer.length ||
		pHead->info.stringsBuffer.length == 0)
	{
		CNLog("strings array buffer info error");
		return false;
	}
	
	unsigned long fileLength = sizeof(CNSpriteFrameDataHead)
	+ pHead->info.framesBuffer.length
	+ pHead->info.stringsBuffer.length;
	
	if (fileLength != m_iBufferLength)
	{
		CNLog("file length error");
		return false;
	}
	
	return true;
}

#pragma mark Interfaces

// meta data: textureName
int CNSpriteFrameData::getTextureFileId(void) const
{
	if (!checkDataFormat())
	{
		return -1;
	}
	CNSpriteFrameDataHead * pHead = (CNSpriteFrameDataHead *)m_pDataBuffer;
	return pHead->info.textureFileId;
}

// buffers
unsigned char * CNSpriteFrameData::getFramesBuffer(unsigned long * pBufferLength) const
{
	if (!checkDataFormat())
	{
		return NULL;
	}
	CNSpriteFrameDataHead * pHead = (CNSpriteFrameDataHead *)m_pDataBuffer;
	*pBufferLength = pHead->info.framesBuffer.length;
	return &m_pDataBuffer[pHead->info.framesBuffer.offset];
}

unsigned char * CNSpriteFrameData::getStringsBuffer(unsigned long * pBufferLength) const
{
	if (!checkDataFormat())
	{
		return NULL;
	}
	CNSpriteFrameDataHead * pHead = (CNSpriteFrameDataHead *)m_pDataBuffer;
	*pBufferLength = pHead->info.stringsBuffer.length;
	return &m_pDataBuffer[pHead->info.stringsBuffer.offset];
}

// frames
CNSpriteFrameInfo * CNSpriteFrameData::getFrame(const unsigned int iLocation) const
{
	unsigned long iBufferLength = 0;
	CNSpriteFrameInfo * pArray = (CNSpriteFrameInfo *)getFramesBuffer(&iBufferLength);
	if (!pArray || iBufferLength < sizeof(CNSpriteFrameInfo) * (iLocation + 1))
	{
		CNLog("failed to get frame, location: %d, element size: %ld, buffer length: %ld", iLocation, sizeof(CNSpriteFrameInfo), iBufferLength);
		return NULL;
	}
	return &pArray[iLocation];
}

NS_CN_END
