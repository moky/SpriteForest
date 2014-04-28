//
//  SFScene.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

CCNode * SFScene::nodeWithDictionary(CCDictionary * pDict)
{
	CCString * pClassName = (CCString *)pDict->objectForKey("Class");
	if (!pClassName)
	{
		pDict->setObject(CCString::stringWithCString("SFScene"), "Class");
	}
	return SFNode::nodeWithDictionary(pDict);
}

bool SFScene::initWithDictionary(CCDictionary * pDict)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	if (!pDict)
	{
		CNLog("error");
		return false;
	}
	
	
	// load textures
	CCArray * pTextures = CNDictionary::arrayForKey("Textures", pDict);
	SFScene::loadTextures(pTextures);
	
	// add sub layers
	CCArray * pLayers = CNDictionary::arrayForKey("Layers", pDict);
	if (pLayers)
	{
		// scale top-level layers for N-Screen support
		CCObject * pObj = NULL;
		CCARRAY_FOREACH(pLayers, pObj)
		{
			CCDictionary * pNodeDict = (CCDictionary *)pObj;
			if (pNodeDict)
			{
				CCString * pScale = (CCString *)pNodeDict->objectForKey("Scale");
				CCString * pScaleX = (CCString *)pNodeDict->objectForKey("ScaleX");
				CCString * pScaleY = (CCString *)pNodeDict->objectForKey("ScaleY");
				if (!pScale && !pScaleX && !pScaleY)
				{
					pNodeDict->setObject(CCString::stringWithCString("ToFill"), "Scale");
				}
			}
		}
	}
	addLayers(pLayers);
	
	// add sub sprites
	//     WARNING: For simplify reason, I hope you should never use it!
	CCArray * pSprites = CNDictionary::arrayForKey("Sprites", pDict);
	addSprites(pSprites);
	
	return true;
}

#pragma mark -

// copy from 'CCSpriteFrameCache.cpp'
CCTexture2D * SFScene_addSpriteFramesWithFile(const char * pszPlist)
{
	return coconut2d::CNSpriteFrameCache::loadTextureAndSprites(pszPlist); // high speed loader
//	
//    const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
//    CCDictionary *dict = CCDictionary::dictionaryWithContentsOfFileThreadSafe(pszPath);
//    
//	std::string texturePath("");
//	
//    CCDictionary* metadataDict = (CCDictionary*)dict->objectForKey("metadata");
//    if (metadataDict)
//    {
//        // try to read  texture file name from meta data
//        texturePath = metadataDict->valueForKey("textureFileName")->getCString();
//    }
//	
//    if (! texturePath.empty())
//    {
//        // build texture path relative to plist file
//        texturePath = CCFileUtils::fullPathFromRelativeFile(texturePath.c_str(), pszPath);
//    }
//    else
//    {
//        // build texture path by replacing file extension
//        texturePath = pszPath;
//		
//        // remove .xxx
//        size_t startPos = texturePath.find_last_of("."); 
//        texturePath = texturePath.erase(startPos);
//		
//        // append .png
//        texturePath = texturePath.append(".png");
//		
//        CNLog("Trying to use file %s as texture", texturePath.c_str());
//    }
//	
//    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());
//	
//    if (pTexture)
//    {
//		CCSpriteFrameCache::sharedSpriteFrameCache()->
//        addSpriteFramesWithDictionary(dict, pTexture);
//    }
//    else
//    {
//        CNLog("Couldn't load texture");
//    }
//	
//    dict->release();
//	
//	return pTexture;
}

CCArray * SFScene::loadTextures(CCArray * pTextures)
{
	if (!pTextures)
	{
		return NULL;
	}
	
	CCArray * pArray = CCArray::arrayWithCapacity(pTextures->count());
	
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(pTextures, pObj)
	{
		pm->push();
		
		CCString * pFilename = NULL;
		
		if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pObj))
		{
			pFilename = (CCString *)pDict->objectForKey("File");
		}
		else if ((pFilename = dynamic_cast<CCString *>(pObj)))
		{
			std::string str(pFilename->getCString());
			str = CNFileManager::fullFilePath(str);
			pFilename = CCString::stringWithCString(str.c_str());
		}
		if (!pFilename)
		{
			pm->pop();
			continue;
		}
		CNLog("filename = %s", pFilename->getCString());
		
		CCTexture2D * pTexture = SFScene_addSpriteFramesWithFile(pFilename->getCString());
		if (pTexture)
		{
			pArray->addObject(pTexture);
		}
		else
		{
			CNLog("failed to load texture: %s", pFilename->getCString());
		}
		
		pm->pop();
	}
	
	return pArray;
}

void SFScene::cleanTextures(CCArray * pTextures)
{
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(pTextures, pObj)
	{
		CCTexture2D * pTexture = dynamic_cast<CCTexture2D *>(pObj);
		if (!pTexture)
		{
			CNLog("error texture");
			continue;
		}
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromTexture(pTexture);
		CCTextureCache::sharedTextureCache()->removeTexture(pTexture);
	}
}

NS_SF_END
