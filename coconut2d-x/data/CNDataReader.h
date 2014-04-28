//
//  CNDataReader.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNDataReader_h
#define Coconut2D_X_CNDataReader_h

#include "CNData.h"

NS_CN_BEGIN

class CNDataReader : public CNData
{
	cocos2d::CCArray * m_pStrings;   // strings array
	cocos2d::CCObject * m_pData; // data
	
	unsigned int m_iItemIndex;
	
public:
	CNDataReader(void);
	virtual ~CNDataReader(void);
	virtual bool init(void);
	
	virtual bool init(const std::string & sPath);
	
	cocos2d::CCObject * getData(void) const;
	
protected:
	void reset(void);
	CNDataItem * read(void);
	
	inline cocos2d::CCString * getString(const unsigned int iLocation) const;
	
private:
	cocos2d::CCObject * parseRootThreadSafe(void);
	
	inline cocos2d::CCObject * parseItemThreadSafe(const CNDataItem * pItem);
	
	cocos2d::CCArray * parseArrayItemThreadSafe(const CNDataItem * pItem);
	cocos2d::CCDictionary * parseDictionaryItemThreadSafe(const CNDataItem * pItem);
};

NS_CN_END

#endif
