//
//  CNSpriteFrameCache.cpp
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#include "CNSpriteFrameCache.h"

#include "CNSpriteFrameDataReader.h"
#include "CNSpriteFrameDataTransformer.h"
#include "../cocoa/CNFileManager.h"

NS_CN_BEGIN

#define CNSpriteFrameCache_BinaryFileExt "sfc"
#define CNSpriteFrameCache_PlistFileExt  "plist"

USING_NS_CC;

// copy from 'CCSpriteFrameCache.cpp'
CCTexture2D * CNSpriteFrameCache_loadTextureAndSpritesWithPlist(const std::string & sPlist)
{
    const char * pszPath = CCFileUtils::fullPathFromRelativePath(sPlist.c_str());
    CCDictionary *dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(pszPath);
    
	std::string texturePath("");
	
    CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
    if (metadataDict)
    {
        // try to read  texture file name from meta data
        texturePath = metadataDict->valueForKey("textureFileName")->getCString();
    }
	
    if (! texturePath.empty())
    {
        // build texture path relative to plist file
        texturePath = CCFileUtils::fullPathFromRelativeFile(texturePath.c_str(), pszPath);
    }
    else
    {
        // build texture path by replacing file extension
        texturePath = pszPath;
		
        // remove .xxx
        size_t startPos = texturePath.find_last_of("."); 
        texturePath = texturePath.erase(startPos);
		
        // append .png
        texturePath = texturePath.append(".png");
		
		if (!CNFileManager::isExists(texturePath.c_str()))
		{
			texturePath = texturePath.erase(startPos);
			texturePath.append(".pvr");
		}
		if (!CNFileManager::isExists(texturePath.c_str()))
		{
			texturePath = texturePath.erase(startPos);
			texturePath.append(".pvr.ccz");
		}
		if (!CNFileManager::isExists(texturePath.c_str()))
		{
			CNLog("error: %s", pszPath);
			return NULL;
		}
    }
	
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());
	
    if (pTexture)
    {
		CCSpriteFrameCache::sharedSpriteFrameCache()->
        addSpriteFramesWithDictionary(dict, pTexture);
		printf("texture loaded: %s\n", texturePath.c_str());
    }
	else
	{
		printf("failed to load texture: %s\n", texturePath.c_str());
	}
	
	return pTexture;
}

CCTexture2D * CNSpriteFrameCache_transform(const std::string &sPlistFile)
{
	std::string filename(sPlistFile);
	filename = CCFileUtils::fullPathFromRelativePath(filename.c_str());
	
	CCTexture2D * pTexture = CNSpriteFrameCache_loadTextureAndSpritesWithPlist(filename);
	
	do
	{
		// check directory whether writable
		std::size_t pos = filename.rfind("/");
		if (pos == std::string::npos)
		{
			CNLog("error, filename: %s", filename.c_str());
			break;
		}
		std::string dir = filename.substr(0, pos);
		if (!CNFileManager::isWritable(dir.c_str()))
		{
			CNLog("dir is not writable: %s", dir.c_str());
			break;
		}
		
		// transform
		pos = filename.rfind(".");
		if (pos == std::string::npos)
		{
			CNLog("error, filename: %s", filename.c_str());
			break;
		}
		std::string outfile = filename.substr(0, pos + 1) + CNSpriteFrameCache_BinaryFileExt;
		CNLog("transform data from %s to %s", filename.c_str(), outfile.c_str());
		CNSpriteFrameDataTransformer * pData = new CNSpriteFrameDataTransformer();
		if (pData && pData->init(filename))
		{
			pData->saveToFile(outfile);
		}
		CC_SAFE_DELETE(pData);
	}
	while (0);
	
	return pTexture;
}

CCTexture2D * CNSpriteFrameCache_loadTextureAndSpritesWithBinary(const std::string &sBinary)
{
	if (sBinary.empty())
	{
		CNLog("error");
		return NULL;
	}
	
	CCTexture2D * pTexture = NULL;
	
	CNSpriteFrameDataReader * pData = new CNSpriteFrameDataReader();
	if (pData && pData->init(sBinary))
	{
		pTexture = pData->getTexture();
		if (pTexture)
		{
			pTexture->retain();
			pTexture->autorelease();
		}
	}
	CC_SAFE_DELETE(pData);
	
	return pTexture;
}

CCTexture2D * CNSpriteFrameCache::loadTextureAndSprites(const std::string &sPath)
{
	std::string filename(sPath);
	
	// get file ext
	std::size_t pos = filename.rfind(".");
	if (pos == std::string::npos)
	{
		CNLog("error, filename: %s", filename.c_str());
		return NULL;
	}
	std::string ext = filename.substr(pos + 1);
	if (ext.empty())
	{
		CNLog("error ext, filename: %s", filename.c_str());
		return NULL;
	}
	
	if (strcasecmp(ext.c_str(), CNSpriteFrameCache_PlistFileExt) == 0)
	{
		// change the file ext from ".plist" to ".sfc"
		filename = filename.substr(0, pos + 1) + CNSpriteFrameCache_BinaryFileExt;
	}
	else if (strcasecmp(ext.c_str(), CNSpriteFrameCache_BinaryFileExt) == 0)
	{
		// do nothing
	}
	else
	{
		CNLog("unrecognized file extension: %s", ext.c_str());
		return NULL;
	}
	CNLog("filename: %s", filename.c_str());
	
	// try ".sfc"
	CCTexture2D * pTexture = CNSpriteFrameCache_loadTextureAndSpritesWithBinary(filename);
	if (pTexture)
	{
		CNLog("loaded from: %s", filename.c_str());
		return pTexture;
	}
	
	// try ".plist"
	filename = filename.substr(0, pos + 1) + CNSpriteFrameCache_PlistFileExt;
	pTexture = CNSpriteFrameCache_transform(filename);
	if (pTexture)
	{
		CNLog("loaded from: %s", filename.c_str());
		return pTexture;
	}
	
	CNLog("error, sPath: %s", sPath.c_str());
	return NULL;
}

NS_CN_END
