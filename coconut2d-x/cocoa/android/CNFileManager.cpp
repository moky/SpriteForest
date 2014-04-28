//
//  CNFileManager.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-12-4.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include "support/zip_support/unzip.h"

#include "../CNFileManager.h"
#include "../CNString.h"

NS_CN_BEGIN

USING_NS_CC;

CNFileManager::CNFileManager(void)
: CCObject()
, m_sResourceDirectory("")
, m_sDocumentDirectory("")
, m_sCachesDirectory("")
, m_sTemporaryDirectory("")
{
	
}

CNFileManager::~CNFileManager(void)
{
	
}

const char * CNFileManager::fullFilePath(std::string & sResourceFilename)
{
	// Android app contains the resource directory in the .apk package
	// with the 'assets/' prefix.
	// no need to add anything to the resource path
	return sResourceFilename.c_str();
}

bool CNFileManager::init(void)
{
	std::string dataPath(CCFileUtils::getWriteablePath());
	m_sResourceDirectory = "";
	m_sDocumentDirectory = "/sdcard/.slanissue"; // save docs to external storage
	m_sCachesDirectory = dataPath + "caches";
	m_sTemporaryDirectory = dataPath + "tmp";
	
	// make sure all directory exists
	if (!mkdir(m_sDocumentDirectory.c_str()))
	{
		CCMessageBox("/sdcard/ is not available!", "External Storage Error");
	}
	if (!mkdir(m_sCachesDirectory.c_str()))
	{
		CNLog("could not happen");
	}
	if (!mkdir(m_sTemporaryDirectory.c_str()))
	{
		CNLog("could not happen");
	}
	
	return true;
}

bool CNFileManager::init(const char * pszAppName)
{
	if (!init())
	{
		return false;
	}
	if (pszAppName && strlen(pszAppName) > 0)
	{
		// make document directory for app
		m_sDocumentDirectory.append("/").append(pszAppName);
		mkdir(m_sDocumentDirectory.c_str());
	}
	return false;
}

static CNFileManager * s_pSharedManager = NULL;

CNFileManager * CNFileManager::sharedManager(void)
{
	if (!s_pSharedManager)
	{
		s_pSharedManager = new CNFileManager();
		s_pSharedManager->init();
	}
	return s_pSharedManager;
}

bool CNFileManager::isExists(const char * pszFilePath)
{
	if (!pszFilePath || strlen(pszFilePath) == 0)
	{
		return false;
	}
	if (pszFilePath[0] == '/')
	{
		CNLog("checking absolute file: %s", pszFilePath);
		return access(pszFilePath, 0) == 0;
	}
	
	// assets file in apk?
	const char * apk = CCFileUtils::getResourcePath();
	if (!apk || strlen(apk) == 0)
	{
		CNLog("could not happen");
		return false;
	}
	
	unzFile pFile = unzOpen(apk);
	if (!pFile)
	{
		CNLog("could not happen");
		return false;
	}
	
	std::string filename(pszFilePath);
	filename.insert(0, "assets/");
	bool exists = (unzLocateFile(pFile, filename.c_str(), 1) == UNZ_OK);
	
	unzClose(pFile);
	
	if (exists)
	{
		CNLog("%s exists in apk.", pszFilePath);
	}
	else
	{
		CNLog("%s not exists in apk.", pszFilePath);
	}
	return exists;
}

bool CNFileManager::isWritable(const char * pszFilePath)
{
	if (!pszFilePath || strlen(pszFilePath) == 0)
	{
		return false;
	}
	if (pszFilePath[0] != '/')
	{
		return false;
	}
	return true;
}

CCDictionary * CNFileManager::getAttributes(const char * pszFilePath)
{
	CNLog("not implement");
	return NULL;
}

#pragma mark -

bool CNFileManager::copy(const char * pszSourcePath, const char * pszTargetPath)
{
	CNLog("copying %s to %s", pszSourcePath, pszTargetPath);
	// open source file for reading
	FILE * fp = fopen(pszSourcePath, "rb");
	if (!fp)
	{
		CNLog("failed to read file: %s", pszSourcePath);
		return false;
	}
	
	// get source file size
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	if (size <= 0)
	{
		CNLog("error, file size: %ld", size);
		fclose(fp);
		return false;
	}
	
	unsigned char * buffer = (unsigned char *)malloc(size);
	memset(buffer, 0, size);
	
	// reading
	long length = fread(buffer, sizeof(unsigned char), size, fp);
	fclose(fp);
	
	if (length != size)
	{
		CNLog("read error, size = %ld, read = %ld, filename = %s", size, length, pszSourcePath);
		free(buffer);
		return false;
	}
	
	// open target file for writting
	fp = fopen(pszTargetPath, "wb");
	if (!fp)
	{
		CNLog("failed to write file: %s", pszTargetPath);
		free(buffer);
		return false;
	}
	
	// writting
	length = fwrite(buffer, sizeof(unsigned char), size, fp);
	free(buffer);
	fclose(fp);
	
	if (length != size)
	{
		CNLog("write error, size = %ld, write = %ld, filename = %s", size, length, pszTargetPath);
		return false;
	}
	
	CNLog("SUCCESS, %s copied to %s", pszSourcePath, pszTargetPath);
	return true;
}

bool CNFileManager::move(const char * pszSourcePath, const char * pszTargetPath)
{
	CNLog("moving %s to %s", pszSourcePath, pszTargetPath);
	if (rename(pszSourcePath, pszTargetPath) == 0)
	{
		CNLog("OK");
		return true;
	}
	CNLog("cannot rename %s to %s, try copying...", pszSourcePath, pszTargetPath);
	
	if (!copy(pszSourcePath, pszTargetPath))
	{
		CNLog("copy failed");
		return false;
	}
	
	return remove(pszSourcePath);
}

bool CNFileManager::remove(const char * pszFilePath)
{
	CNLog("removing path: %s", pszFilePath);
	if (unlink(pszFilePath) == 0)
	{
		CNLog("SUCCESS");
		return true;
	}
	else
	{
		CNLog("Failed");
		return false;
	}
}

bool CNFileManager_mkdir(const char * pszPath)
{
	return mkdir(pszPath, 0755) == 0;
}

bool CNFileManager::mkdir(const char * pszDir)
{
	if (!pszDir || strlen(pszDir) == 0)
	{
		CNLog("Error");
		return false;
	}
	std::string path(pszDir);
	if (path[path.length() - 1] == '/')
	{
		path = path.substr(0, path.length() - 1);
	}
	if (path.empty() || isExists(pszDir))
	{
		CNLog("directory exists: %s", pszDir);
		return true;
	}
	
	// check upper dir
	std::size_t pos = path.rfind("/");
	if (pos != std::string::npos)
	{
		// create upper directory
		if (!mkdir(path.substr(0, pos).c_str()))
		{
			CNLog("failed to create upper directory!");
			return false;
		}
	}
	
	CNLog("creating directory: %s", path.c_str());
	if (CNFileManager_mkdir(path.c_str()))
	{
		CNLog("OK");
		return true;
	}
	else
	{
		CNLog("Failed");
		return false;
	}
}

NS_CN_END
