//
//  CNSpriteFrameData.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNSpriteFrameData_h
#define Coconut2D_X_CNSpriteFrameData_h

#include "../cnMacros.h"

NS_CN_BEGIN

#pragma pack(1)

typedef struct {
	unsigned long  offset; // offset in memory buffer
	unsigned long  length; // length of the sub buffer
} CNBufferRange;

typedef unsigned short CNSpriteFrameID; // 0 - 65535

typedef struct {
	CNSpriteFrameID id;
	bool rotated; // 8 bits
	bool reserved; // reserved & for bytes alignment
	float x;
	float y;
	float width;
	float height;
	float offsetX;
	float offsetY;
	int originalWidth;
	int originalHeight;
} CNSpriteFrameInfo;

typedef struct {
	unsigned short textureFileId;
	unsigned short reserved[2]; // reserved & for bytes alignment
	CNBufferRange framesBuffer;
	CNBufferRange stringsBuffer; // strings array
} CNSpriteFrameDataInfo;

typedef struct {
	// protocol
	unsigned char format[4]; // "SFC"
	unsigned char headVersion;
	unsigned char version;
	unsigned char reserved[10]; // reserved & for bytes alignment
	unsigned long fileLength;
	// descriptions
	unsigned char description[64];
	unsigned char copyright[32];
	unsigned char author[32];
	// index info
	CNSpriteFrameDataInfo info;
} CNSpriteFrameDataHead;

#pragma pack()

class CNSpriteFrameData
{
protected:
	unsigned char * m_pDataBuffer;
	unsigned long m_iBufferLength;
	
	bool m_bIsDataValid;
	
public:
	CNSpriteFrameData(void);
	virtual ~CNSpriteFrameData(void);
	virtual bool init(void);
	
	virtual bool init(const unsigned long iBufferLength); // create an initialized buffer
	virtual bool init(const std::string & sDataFile); // load data from a 'sfc' file
	
	bool checkDataFormat(void) const;
	
	bool saveToFile(const std::string & sDataFile) const; // save buffer into a 'sfc' file
	
#pragma mark Data Interfaces
	
public: // info
	int getTextureFileId(void) const;
protected: // buffers
	unsigned char * getFramesBuffer(unsigned long * pBufferLength) const;
	unsigned char * getStringsBuffer(unsigned long * pBufferLength) const;
public: // frames
	CNSpriteFrameInfo * getFrame(const unsigned int iLocation) const;
};

NS_CN_END

#endif
