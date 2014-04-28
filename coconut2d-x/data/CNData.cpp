//
//  CNData.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNData.h"

#include "../cocoa/CNFileManager.h"

NS_CN_BEGIN

#define CN_DATA_HEAD_VERSION 0x01
#define CN_DATA_VERSION      0x01

CNData::CNData(void)
: m_pDataBuffer(NULL)
, m_iBufferLength(0)
, m_bIsDataValid(false)
{
	
}

CNData::~CNData(void)
{
	CC_SAFE_FREE(m_pDataBuffer);
}

bool CNData::init(void)
{
	CC_SAFE_FREE(m_pDataBuffer);
	m_pDataBuffer = NULL;
	m_iBufferLength = 0;
	m_bIsDataValid = false;
	return true;
}

bool CNData::init(const unsigned long iBufferLength)
{
	if (iBufferLength <= sizeof(CNDataHead))
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
	
	CNDataHead * pHead = (CNDataHead *)m_pDataBuffer;
	
	// protocol
	pHead->format[0] = 'P';
	pHead->format[1] = 'B';
	pHead->format[2] = 'F';
	pHead->format[3] = '\0';
	
	pHead->headVersion = CN_DATA_HEAD_VERSION;
	pHead->version     = CN_DATA_VERSION;
	
	pHead->fileLength = m_iBufferLength;
	
	// descriptions
	time_t now = time(NULL);
	tm * tm = gmtime(&now);
	
	snprintf((char *)pHead->description, sizeof(pHead->description),
			 "Binary File for Plist. Generated at %d-%d-%d %d:%d:%d",
			 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	
	snprintf((char *)pHead->copyright, sizeof(pHead->copyright),
			 "Copyright %d Slanissue Inc.", tm->tm_year + 1900);
	
	snprintf((char *)pHead->author, sizeof(pHead->author),
			 "Author: Moky@Beva.com, %d-%d-%d", 2013, 1, 4);
	
	return true;
}

bool CNData::init(const std::string & sPath)
{
	if (sPath.empty() || !init())
	{
		return false;
	}
	if (!CNFileManager::isExists(sPath.c_str()))
	{
		CNLog("file not found: %s", sPath.c_str());
		return false;
	}
	
	cocos2d::CCFileData data(sPath.c_str(), "rb");
	unsigned char * pBuffer = data.getBuffer();
	unsigned long lSize = data.getSize();
	if (!pBuffer || lSize <= sizeof(CNDataHead))
	{
		CNLog("invalid data file: %s, size: %ld", sPath.c_str(), lSize);
		return false;
	}
	CNLog("read %ld bytes from file: %s", lSize, sPath.c_str());
	
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

bool CNData::saveToFile(const std::string & sPath) const
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

bool CNData::checkDataFormat(void) const
{
	if (m_bIsDataValid)
	{
		// the data had been checked before
		// quick return here
		return true;
	}
	
	if (!m_pDataBuffer || m_iBufferLength <= sizeof(CNDataHead))
	{
		CNLog("data buffer not init");
		return false;
	}
	
	// check head
	CNDataHead * pHead = (CNDataHead *)m_pDataBuffer;
	if (pHead->format[0] != 'P' || pHead->format[1] != 'B' || pHead->format[2] != 'F' || pHead->format[3] != '\0')
	{
		CNLog("format sign error: [%c%c%c%c]", pHead->format[0], pHead->format[1], pHead->format[2], pHead->format[3]);
		return false;
	}
	
	if (pHead->headVersion != CN_DATA_HEAD_VERSION || pHead->version != CN_DATA_VERSION)
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
	if (pHead->body.itemsBuffer.offset != sizeof(CNDataHead) ||
		pHead->body.itemsBuffer.length == 0)
	{
		CNLog("frames buffer info error");
		return false;
	}
	
	if (pHead->body.stringsBuffer.offset != pHead->body.itemsBuffer.offset + pHead->body.itemsBuffer.length ||
		pHead->body.stringsBuffer.length == 0)
	{
		CNLog("strings array buffer info error");
		return false;
	}
	
	unsigned long fileLength = sizeof(CNDataHead)
	+ pHead->body.itemsBuffer.length
	+ pHead->body.stringsBuffer.length;
	
	if (fileLength != m_iBufferLength)
	{
		CNLog("file length error");
		return false;
	}
	
	return true;
}

unsigned char * CNData::getItemsBuffer(unsigned long * pBufferLength) const
{
	if (!checkDataFormat())
	{
		return NULL;
	}
	CNDataHead * pHead = (CNDataHead *)m_pDataBuffer;
	*pBufferLength = pHead->body.itemsBuffer.length;
	return &m_pDataBuffer[pHead->body.itemsBuffer.offset];
}

unsigned char * CNData::getStringsBuffer(unsigned long * pBufferLength) const
{
	if (!checkDataFormat())
	{
		return NULL;
	}
	CNDataHead * pHead = (CNDataHead *)m_pDataBuffer;
	*pBufferLength = pHead->body.stringsBuffer.length;
	return &m_pDataBuffer[pHead->body.stringsBuffer.offset];
}

CNDataItem * CNData::getItem(const unsigned int iLocation) const
{
	unsigned long iBufferLength = 0;
	CNDataItem * pArray = (CNDataItem *)getItemsBuffer(&iBufferLength);
	if (!pArray || iBufferLength < sizeof(CNDataItem) * (iLocation + 1))
	{
		CNLog("failed to get item, location: %d, element size: %ld, buffer length: %ld", iLocation, sizeof(CNDataItem), iBufferLength);
		return NULL;
	}
	return &pArray[iLocation];
}

NS_CN_END
