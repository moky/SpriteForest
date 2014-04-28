//
//  CNData.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNData_h
#define Coconut2D_X_CNData_h

#include "../cnMacros.h"

NS_CN_BEGIN

#pragma pack(1)

typedef enum {
	CNDataItemTypeString,     // 0
	CNDataItemTypeArray,      // 1
	CNDataItemTypeDictionary, // 2
	CNDataItemTypeInteger,    // 3
	CNDataItemTypeFloat,      // 4
	CNDataItemTypeUnknown     // ?
} CNDataItemType;

typedef struct {
	unsigned char type;         // 0 - 255
	unsigned char reserved;     // reserved & for bytes alignment
	unsigned short key;         // 0 - 65,535 (64K)
	union {
		// string
		unsigned long stringId; // 0 - 4,294,967,295 (4G)
		// dictionary/array
		unsigned short count;   // 0 - 65,535 (64K)
		// numeric
		unsigned long value;
		int intValue;
		unsigned int uintValue;
		float floatValue;
		bool boolValue;
	};
} CNDataItem;

typedef struct {
	struct {
		unsigned long  offset; // offset in memory buffer
		unsigned long  length; // length of the sub buffer
	} itemsBuffer;
	struct {
		unsigned long  offset; // offset in memory buffer
		unsigned long  length; // length of the sub buffer
	} stringsBuffer;
} CNDataBody;

typedef struct {
	// protocol
	unsigned char format[4]; // "PBF"
	unsigned char headVersion;
	unsigned char version;
	unsigned char reserved[10]; // reserved & for bytes alignment
	unsigned long fileLength;
	// descriptions
	unsigned char description[64];
	unsigned char copyright[32];
	unsigned char author[32];
	// body
	CNDataBody body;
} CNDataHead;

#pragma pack()

class CNData
{
protected:
	unsigned char * m_pDataBuffer;
	unsigned long m_iBufferLength;
	
	bool m_bIsDataValid;
	
public:
	CNData(void);
	virtual ~CNData(void);
	virtual bool init(void);
	
	virtual bool init(const unsigned long iBufferLength); // create an initialized buffer
	virtual bool init(const std::string & sDataFile); // load data from a 'pbf' file
	
	bool checkDataFormat(void) const;
	
	bool saveToFile(const std::string & sDataFile) const; // save buffer into a 'pbf' file
	
#pragma mark Data Interfaces
	
protected:
	CNDataItem * getItem(const unsigned int iLocation) const;
	unsigned char * getItemsBuffer(unsigned long * pBufferLength) const;
	unsigned char * getStringsBuffer(unsigned long * pBufferLength) const;
};

NS_CN_END

#endif
