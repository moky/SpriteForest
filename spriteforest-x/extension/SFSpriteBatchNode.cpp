//
//  SFSpriteBatchNode.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFSpriteBatchNode.h"

#include "../base/SFScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFSpriteBatchNode::SFSpriteBatchNode(void)
: CNSpriteBatchNode()
{
	
}

SFSpriteBatchNode::~SFSpriteBatchNode(void)
{
	CCTexture2D * pTexture = getTexture();
	if (pTexture)
	{
		CNLog("clean texture");
		SFScene::cleanTextures(CCArray::arrayWithObject(pTexture));
	}
}

bool SFSpriteBatchNode::init(void)
{
	return true;
}

CCNode * SFSpriteBatchNode::nodeWithString(const char * pszString)
{
	if (!pszString || strlen(pszString) == 0)
	{
		pszString = "SFSpriteBatchNode";
	}
	return SFNode::nodeWithString(pszString);
}

CCNode * SFSpriteBatchNode::nodeWithDictionary(CCDictionary * pDict)
{
	CCString * pClassName = (CCString *)pDict->objectForKey("Class");
	if (!pClassName)
	{
		pDict->setObject(CCString::stringWithCString("SFSpriteBatchNode"), "Class");
	}
	return SFNode::nodeWithDictionary(pDict);
}

bool SFSpriteBatchNode::initWithDictionary(CCDictionary * pDict)
{
	if (!CNSpriteBatchNode::initWithDictionary(pDict))
	{
		CNLog("error");
		return false;
	}
	
	// load texture from 'File' tag in 'CNSpriteBatchNode::initWithDictionary(...)'
	// so do nothing here
	
	// add sub sprites
	CCArray * pSprites = CNDictionary::arrayForKey("Sprites", pDict);
	addSprites(pSprites);
	
	return true;
}

NS_SF_END
