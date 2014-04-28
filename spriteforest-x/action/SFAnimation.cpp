//
//  SFAnimation.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-6.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFAnimation.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

CCAnimation * SFAnimation::animation(CCArray * pFrames, const CCFloat fDelay)
{
	if (!pFrames || pFrames->count() == 0 || fDelay <= 0)
	{
		CNLog("error");
		return NULL;
	}
	
	CCTextureCache * pTextureCache = CCTextureCache::sharedTextureCache();
	CCSpriteFrameCache * pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	
	std::string sFilename;
	CCSpriteFrame * pSpriteFrame;
	CCTexture2D * pTexture;
	
	CCArray * pArray = CCArray::arrayWithCapacity(pFrames->count());
	CCObject * pObj = NULL;
	CCARRAY_FOREACH(pFrames, pObj)
	{
		// get filename
		sFilename.clear();
		if (CCString * pString = dynamic_cast<CCString *>(pObj))
		{
			sFilename = pString->getCString();
		}
		else if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pObj))
		{
			CCString * pFile = (CCString *)pDict->objectForKey("File");
			if (pFile)
			{
				sFilename = pFile->getCString();
			}
		}
		if (sFilename.empty())
		{
			CNLog("invalid frame filename");
			continue;
		}
		sFilename = CNFileManager::fullFilePath(sFilename);
		
		// get sprite frame
		pSpriteFrame = NULL;
		if (CNFileManager::isExists(sFilename.c_str()))
		{
			pTexture = pTextureCache->addImage(sFilename.c_str());
			if (!pTexture)
			{
				CNLog("error");
				continue;
			}
			CCSize tSize = pTexture->getContentSize();
			CCRect tRect = CCRectMake(0, 0, tSize.width, tSize.height);
			pSpriteFrame = CCSpriteFrame::frameWithTexture(pTexture, tRect);
		}
		else
		{
			std::string string(sFilename);
			string = CNString::lastPathComponent(string);
			pSpriteFrame = pSpriteFrameCache->spriteFrameByName(string.c_str());
		}
		
		// done
		if (pSpriteFrame)
		{
			pArray->addObject(pSpriteFrame);
		}
	}
	
	if (pArray->count() == 0)
	{
		CNLog("no valid frame");
		return NULL;
	}
	
	return CCAnimation::animationWithSpriteFrames(pArray, fDelay);
}

NS_SF_END
