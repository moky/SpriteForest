//
//  CNSprite.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-21.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNSprite.h"

#include "../cocoa/CNString.h"
#include "../cocoa/CNFileManager.h"

NS_CN_BEGIN

USING_NS_CC;

bool CNSprite::initWithFile(const char * pszFilename)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	replaceImageWithFile(pszFilename);
	return true;
}

bool CNSprite::initWithDictionary(CCDictionary * pDict)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	if (!pDict)
	{
		CNLog("invalid parameter: pDict");
		return false;
	}
	
	CCString * pFilename = (CCString *)pDict->objectForKey("File");
	if (pFilename)
	{
		replaceImageWithFile(pFilename->getCString());
	}
	
	CCString * pOpacity = (CCString *)pDict->objectForKey("Opacity");
	if (pOpacity)
	{
		setOpacity(pOpacity->intValue());
	}
	
	return setAttributes(pDict);
}

#pragma mark -

CCArray * CNSprite::createSprites(CCArray * pFilenames)
{
	CCArray * pArray = new CCArray();
	pArray->initWithCapacity(1);
	CNSprite * pSprite = NULL;
	
	CCObject * pObj = NULL;
	CCString * pFilename;
	CCARRAY_FOREACH(pFilenames, pObj)
	{
		pFilename = (CCString *)pObj;
		pSprite = spriteWithFile(pFilename->getCString());
		if (!pSprite)
		{
			CNLog("could not happen!");
			continue;
		}
		pSprite->getTexture()->setAliasTexParameters();
		pArray->addObject(pSprite);
	}
	pArray->autorelease();
	return pArray;
}

/**
 *  change the sprite's image
 */
void CNSprite::replaceImageWithFile(const char * pszFilename)
{
	if (!pszFilename || strlen(pszFilename) == 0)
	{
		return;
	}
	
	CCTextureCache * pTextureCache = CCTextureCache::sharedTextureCache();
	if (!pTextureCache)
	{
		CNLog("could not happen");
		return;
	}
	
	CCTexture2D * pTexture = pTextureCache->textureForKey(pszFilename);
	if (!pTexture)
	{
		// set not pop-up message box when load image failed
		bool bNotify = CCFileUtils::getIsPopupNotify();
		CCFileUtils::setIsPopupNotify(false);
		
		pTexture = pTextureCache->addImage(pszFilename);
		if (!pTexture)
		{
			CCImage * pImage = getImageWithFile(pszFilename);
			if (pImage)
			{
				// create texture from image and put it into the cache
				pTexture = pTextureCache->addUIImage(pImage, pszFilename);
			}
		}
		
		// reset the value of UIImage notify
		CCFileUtils::setIsPopupNotify(bNotify);
	}
	
	bool bRotated = false;
	CCRect tRect = CCRectZero;
	if (pTexture)
	{
		tRect.size = pTexture->getContentSize();
	}
	else
	{
		std::string filename(pszFilename);
		filename = CNString::lastPathComponent(filename);
		CCSpriteFrame * pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename.c_str());
		if (pSpriteFrame)
		{
			pTexture = pSpriteFrame->getTexture();
			tRect = pSpriteFrame->getRect();
			bRotated = pSpriteFrame->isRotated();
		}
		else
		{
			CNLog("could not get image: %s", pszFilename);
		}
	}
	
	if (pTexture && !CCRect::CCRectEqualToRect(tRect, CCRectZero))
	{
//		setBatchNode(NULL);
//		ccBlendFunc sBlendFunc;
//		sBlendFunc.src = CC_BLEND_SRC;
//		sBlendFunc.dst = CC_BLEND_DST;
//		setBlendFunc(sBlendFunc);
//		
//		setTexture(pTexture);
//		setTextureRect(tRect);
		initWithTexture(pTexture, tRect, bRotated);
	}
}

CCImage * CNSprite::getImageWithFile(const char * pszFilename)
{
	if (!pszFilename || strlen(pszFilename) == 0)
	{
		CNLog("error");
		return NULL;
	}
	if (strstr(pszFilename, "://"))
	{
		// this is a URL
		CNLog("not implement, url: %s", pszFilename);
		return NULL;
	}
	
	std::string filename = CCFileUtils::fullPathFromRelativePath(pszFilename);
	if (!CNFileManager::isExists(pszFilename))
	{
		filename = CNString::lastPathComponent(filename);
		filename = CNFileManager::fullFilePath(filename); // bundle file?
	}
	
	CCImage * pImage = new CCImage();
	if (pImage && pImage->initWithImageFile(filename.c_str()))
	{
		pImage->autorelease();
		return pImage;
	}
	CC_SAFE_DELETE(pImage);
	CNLog("cannot get image from %s", filename.c_str());
	return NULL;
}

NS_CN_END
