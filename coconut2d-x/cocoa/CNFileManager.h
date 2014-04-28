//
//  CNFileManager.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-30.
//  Copyright (c) 2012年 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNFileManager_h
#define Coconut2D_X_CNFileManager_h

#include "../cnMacros.h"

NS_CN_BEGIN

class CNFileManager : public cocos2d::CCObject
{
	// main bundle
	std::string m_sResourceDirectory;
	// sdcard/caches
	std::string m_sDocumentDirectory;
	std::string m_sCachesDirectory;
	std::string m_sTemporaryDirectory;
	
public:
	CNFileManager(void);
	virtual ~CNFileManager(void);
	virtual bool init(void);
	
	virtual bool init(const char * pszAppName);
	
	static CNFileManager * sharedManager(void);
	
	// DOS
	static bool isExists(const char * pszFilePath);
	static bool isWritable(const char * pszFilePath);
	static cocos2d::CCDictionary * getAttributes(const char * pszFilePath);
	
	static bool copy(const char * pszSourcePath, const char * pszTargetPath);
	static bool move(const char * pszSourcePath, const char * pszTargetPath);
	static bool remove(const char * pszFilePath);
	static bool mkdir(const char * pszDir);
	
	// directories
	const char * resourceDirectory(void) const { return m_sResourceDirectory.c_str(); }
	const char * documentDirectory(void) const { return m_sDocumentDirectory.c_str(); }
	const char * cachesDirectory(void) const { return m_sCachesDirectory.c_str(); }
	const char * temporaryDirectory(void) const { return m_sTemporaryDirectory.c_str(); }
	
	static const char * fullFilePath(std::string & sResourceFilename);
};

NS_CN_END

#endif
