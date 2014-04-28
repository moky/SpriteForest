//
//  CNSpriteBatchNode.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "CNSpriteBatchNode.h"

NS_CN_BEGIN

USING_NS_CC;

CNSpriteBatchNode * CNSpriteBatchNode::batchNodeWithFile(const char * pszImageFile)
{
	CNSpriteBatchNode * pNode = new CNSpriteBatchNode();
	if (pNode && pNode->initWithFile(pszImageFile))
	{
		pNode->autorelease();
		return pNode;
	}
	CC_SAFE_DELETE(pNode);
	return NULL;
}

bool CNSpriteBatchNode::initWithFile(const char * pszImageFile)
{
	if (!init())
	{
		CNLog("error");
		return false;
	}
	if (!pszImageFile || strlen(pszImageFile) == 0 || !CCSpriteBatchNode::initWithFile(pszImageFile, 29))
	{
		CNLog("error");
		return false;
	}
	setAnchorPoint(CCPointZero);
	setPosition(CCPointZero);
	return true;
}

bool CNSpriteBatchNode::initWithDictionary(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("invalid parameter: pDict");
		return false;
	}
	CCString * pFilename = (CCString *)pDict->objectForKey("File");
	if (!pFilename || !initWithFile(pFilename->getCString()))
	{
		CNLog("error");
		return false;
	}
	
	CNNode::setAttributes(this, pDict);
	return true;
}

NS_CN_END
