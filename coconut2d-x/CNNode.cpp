//
//  CNNode.cpp
//  Coconut2D-X
//
//  Created by Moky on 12-11-20.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#include "CNNode.h"

#include "CNScene.h"
#include "layers/CNLayer.h"
#include "sprites/CNSprite.h"

NS_CN_BEGIN

USING_NS_CC;

#pragma mark Touch Location Extensions

bool CNNode::containsNodeSpacePoint(CCNode * pNode, const CCPoint & tPoint)
{
	if (!pNode)
	{
		CNLog("error");
		return false;
	}
	// if a node or its ancestors is not visible, that it would not contain any point.
	for (CCNode * p = pNode; p; p = p->getParent())
	{
		if (!p->getIsVisible())
		{
			return false;
		}
	}
	CCRect tRect = CCRectZero;
	tRect.size = pNode->getContentSize();
	return CCRect::CCRectContainsPoint(tRect, tPoint);
}

bool CNNode::containsVisiblePixelAtNodeSpacePoint(CCNode * pNode, const CCPoint & tPoint)
{
	ccColor4B c = resetAndReadPixel(pNode, tPoint);
	return c.a != 0;
}

bool CNNode::containsTouchLocation(CCNode * pNode, CCTouch * pTouch)
{
	if (CNSprite * pSprite = dynamic_cast<CNSprite *>(pNode))
	{
		return pSprite->containsTouchLocation(pTouch);
	}
	else if (CNLayer * pLayer = dynamic_cast<CNLayer *>(pNode))
	{
		return pLayer->containsTouchLocation(pTouch);
	}
	else if (CNScene * pScene = dynamic_cast<CNScene *>(pNode))
	{
		// the current scene always contains any touch
		return pScene->getIsVisible();
	}
	else // for CCNode
	{
		return containsTouchLocation(pNode, pTouch, false);
	}
}

bool CNNode::containsTouchLocation(CCNode * pNode, CCTouch * pTouch, const bool bCheckPixel)
{
	if (!pNode)
	{
		CNLog("error");
		return false;
	}
	CCPoint tPoint = pNode->convertTouchToNodeSpace(pTouch);
	if (CNSprite * pSprite = dynamic_cast<CNSprite *>(pNode))
	{
		if (!pSprite->containsNodeSpacePoint(tPoint))
		{
			return false;
		}
	}
	else if (CNLayer * pLayer = dynamic_cast<CNLayer *>(pNode))
	{
		if (!pLayer->containsNodeSpacePoint(tPoint))
		{
			return false;
		}
	}
	else if (CNScene * pScene = dynamic_cast<CNScene *>(pNode))
	{
		// the current scene always contains any touch
		return pScene->getIsVisible();
	}
	else // for CCNode
	{
		if (!containsNodeSpacePoint(pNode, tPoint))
		{
			return false;
		}
	}
	if (!bCheckPixel)
	{
		return true;
	}
	return containsVisiblePixelAtNodeSpacePoint(pNode, tPoint);
}

#pragma mark Attributes Extensions

bool CNNode::setAttributes(CCNode * pNode, CCDictionary * pDict)
{
	if (!pNode || !pDict)
	{
		CNLog("error");
		return false;
	}
	
	// size
	//if (CCSize::CCSizeEqualToSize(pNode->getContentSize(), CCSizeZero))
	{
		CCString * pSize = (CCString *)pDict->objectForKey("Size");
		if (pSize)
		{
			pNode->setContentSize(CCSizeFromString(pSize->getCString()));
		}
		else
		{
			CCString * pWidth = (CCString *)pDict->objectForKey("Width");
			CCString * pHeight = (CCString *)pDict->objectForKey("Height");
			if (pWidth && pHeight)
			{
				pNode->setContentSize(CCSizeMake(pWidth->floatValue(), pHeight->floatValue()));
			}
		}
	}
	
	// position
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	if (pPosition)
	{
		pNode->setPosition(CCPointFromString(pPosition->getCString()));
	}
	else
	{
		CCString * pX = (CCString *)pDict->objectForKey("X");
		CCString * pY = (CCString *)pDict->objectForKey("Y");
		if (pX && pY)
		{
			pNode->setPosition(pX->floatValue(), pY->floatValue());
		}
	}
	
	// anchor point
	CCString * pAnchorPoint = (CCString *)pDict->objectForKey("AnchorPoint");
	if (pAnchorPoint)
	{
		pNode->setAnchorPoint(CCPointFromString(pAnchorPoint->getCString()));
	}
	else
	{
		CCString * pAnchorX = (CCString *)pDict->objectForKey("AnchorX");
		CCString * pAnchorY = (CCString *)pDict->objectForKey("AnchorY");
		if (pAnchorX && pAnchorY)
		{
			pNode->setAnchorPoint(ccp(pAnchorX->floatValue(), pAnchorY->floatValue()));
		}
	}
	
	// rotation
	CCString * pRotation = (CCString *)pDict->objectForKey("Rotation");
	if (pRotation)
	{
		pNode->setRotation(pRotation->floatValue());
	}
	
	// scale
	CCString * pScale = (CCString *)pDict->objectForKey("Scale");
	if (pScale)
	{
		if (pScale->floatValue() != 0 || strcmp(pScale->getCString(), "0") == 0)
		{
			pNode->setScale(pScale->floatValue());
		}
	}
	else
	{
		CCString * pScaleX = (CCString *)pDict->objectForKey("ScaleX");
		CCString * pScaleY = (CCString *)pDict->objectForKey("ScaleY");
		if (pScaleX && pScaleY)
		{
			pNode->setScaleX(pScaleX->floatValue());
			pNode->setScaleY(pScaleY->floatValue());
		}
	}
	
	// skew
	CCString * pSkewX = (CCString *)pDict->objectForKey("SkewX");
	CCString * pSkewY = (CCString *)pDict->objectForKey("SkewY");
	if (pSkewX && pSkewY)
	{
		pNode->setSkewX(pSkewX->floatValue());
		pNode->setSkewY(pSkewY->floatValue());
	}
	
	// tag
	CCString * pTag = (CCString *)pDict->objectForKey("Tag");
	if (pTag)
	{
		pNode->setTag(pTag->intValue());
	}
	
	// visible
	CCString * pHidden = (CCString *)pDict->objectForKey("Hidden");
	if (pHidden)
	{
		pNode->setIsVisible(!pHidden->boolValue());
	}
	
	return true;
}

CCScene * CNNode::ancestorScene(CCNode * pNode)
{
	if (!pNode)
	{
		CNLog("error");
		return NULL;
	}
	for (CCNode * p = pNode; p; p = p->getParent())
	{
		if (CCScene * pScene = dynamic_cast<CCScene *>(p))
		{
			return pScene;
		}
	}
	CNLog("the node is not perform currently");
	return NULL;
}

#pragma mark Pixels and Image Extensions

void CNNode::readPixels(CCNode * pNode, const CCRect & tRect, ccColor4B ** pBuffer)
{
	if (!pNode)
	{
		CNLog("error");
		return ;
	}
	CCFloat width = tRect.size.width * CC_CONTENT_SCALE_FACTOR();
	CCFloat height = tRect.size.height * CC_CONTENT_SCALE_FACTOR();
	if (width <= 0 || height <= 0)
	{
		CNLog("size error");
		return ;
	}
	if (CCDirector::sharedDirector()->isPaused())
	{
		CNLog("sgx error: background gpu access not permitted");
		return;
	}
	
	CCRenderTexture * rt = new CCRenderTexture();
	CCAssert(rt, "");
	rt->initWithWidthAndHeight(tRect.size.width, tRect.size.height, kCCTexture2DPixelFormat_RGBA8888);
	rt->beginWithClear(0, 0, 0, 0);
	{
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		CCPoint position = pNode->getPosition();
		pNode->setPosition(ccpSub(pNode->getAnchorPointInPoints(), tRect.origin));
		pNode->visit();
		pNode->setPosition(position);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, *pBuffer);
	}
	rt->end();
	rt->release();
	
	// to get the actual texture data
	// #640 the image read from rendertexture is upseted
	int tx = width;
	int ty = height;
	int bytesPerRow = sizeof(ccColor4B) * tx;
	ccColor4B * pLineBuffer = (ccColor4B *)malloc(bytesPerRow);
	if (!pLineBuffer)
	{
		CNLog("not enough memory");
		return;
	}
	ccColor4B * p1, * p2;
	for (int i = ty / 2 - 1; i >= 0; i--)
	{
		p1 = *pBuffer + i * tx;
		p2 = *pBuffer + (ty - 1 - i) * tx;
		bzero(pLineBuffer, bytesPerRow);
		memcpy(pLineBuffer, p1, bytesPerRow);
		memcpy(p1, p2, bytesPerRow);
		memcpy(p2, pLineBuffer, bytesPerRow);
	}
	CC_SAFE_FREE(pLineBuffer);
}

void CNNode::resetAndReadPixels(CCNode * pNode, const CCRect & tRect, ccColor4B ** pBuffer)
{
	if (!pNode)
	{
		CNLog("error");
		return ;
	}
	// save original values
	CCPoint originalPosition = pNode->getPosition();
	CCPoint originalAnchorPoint = pNode->getAnchorPoint();
	CCFloat originalRotation = pNode->getRotation();
	CCFloat originalScaleX = pNode->getScaleX();
	CCFloat originalScaleY = pNode->getScaleY();
	CCFloat originalSkewX = pNode->getSkewX();
	CCFloat originalSkewY = pNode->getSkewY();
	
	// reset values
	pNode->setPosition(CCPointZero);
	pNode->setAnchorPoint(CCPointZero);
	//pNode->setPosition(pNode->getAnchorPointInPoints());
	pNode->setRotation(0.0f);
	pNode->setScaleX(1.0f);
	pNode->setScaleY(1.0f);
	pNode->setSkewX(0.0f);
	pNode->setSkewY(0.0f);
	
	readPixels(pNode, tRect, pBuffer);
	
	// restore original values
	pNode->setSkewY(originalSkewY);
	pNode->setSkewX(originalSkewX);
	pNode->setScaleY(originalScaleY);
	pNode->setScaleX(originalScaleX);
	pNode->setRotation(originalRotation);
	pNode->setAnchorPoint(originalAnchorPoint);
	pNode->setPosition(originalPosition);
}

ccColor4B CNNode::readPixel(CCNode * pNode, const CCPoint & tPoint)
{
	CCRect tRect = CCRectMake(tPoint.x, tPoint.y, 1, 1);
	size_t iLen = sizeof(ccColor4B);
	ccColor4B * pBuffer = (ccColor4B *)malloc(iLen);
	bzero(pBuffer, iLen);
	readPixels(pNode, tRect, &pBuffer);
	ccColor4B c = pBuffer[0];
	CC_SAFE_FREE(pBuffer);
	return c;
}

ccColor4B CNNode::resetAndReadPixel(CCNode * pNode, const CCPoint & tPoint)
{
	CCRect tRect = CCRectMake(tPoint.x, tPoint.y, 1, 1);
	size_t iLen = sizeof(ccColor4B);
	ccColor4B * pBuffer = (ccColor4B *)malloc(iLen);
	bzero(pBuffer, iLen);
	resetAndReadPixels(pNode, tRect, &pBuffer);
	ccColor4B c = pBuffer[0];
	CC_SAFE_FREE(pBuffer);
	return c;
}

CCImage * CNNode::getImage(CCNode * pNode)
{
	if (!pNode)
	{
		CNLog("error");
		return NULL;
	}
	CCSize contentSize = pNode->getContentSize();
	if (contentSize.width <= 0 || contentSize.height <= 0)
	{
		return NULL;
	}
	
	CCRect tRect = CCRectMake(0, 0, contentSize.width, contentSize.height);
	return getImage(pNode, tRect);
}

CCImage * CNNode::getImage(CCNode * pNode, const CCRect & tRect)
{
	CCImage * pImage = getImageThreadSafe(pNode, tRect);
	if (pImage)
	{
		pImage->autorelease();
	}
	return pImage;
}

CCImage * CNNode::getImageThreadSafe(CCNode * pNode)
{
//	return NULL; // TODO: cannot get texture in thread!!
	if (!pNode)
	{
		CNLog("error");
		return NULL;
	}
	CCSize contentSize = pNode->getContentSize();
	if (contentSize.width <= 0 || contentSize.height <= 0)
	{
		return NULL;
	}
	
	CCRect tRect = CCRectMake(0, 0, contentSize.width, contentSize.height);
	return getImageThreadSafe(pNode, tRect);
}

CCImage * CNNode::getImageThreadSafe(CCNode * pNode, const CCRect & tRect)
{
	int tx = tRect.size.width * CC_CONTENT_SCALE_FACTOR();
	int ty = tRect.size.height * CC_CONTENT_SCALE_FACTOR();
	
	int bitsPerComponent = 8 * sizeof(GLubyte);
	int bytesPerPixel    = sizeof(ccColor4B);
	int bytesPerRow      = bytesPerPixel * tx;
	size_t iBufferLen    = bytesPerRow * ty;
	
	ccColor4B * pBuffer = (ccColor4B *)malloc(iBufferLen);
	if (!pBuffer)
	{
		CNLog("not enough momory!");
		CC_SAFE_FREE(pBuffer);
		return NULL;
	}
	bzero(pBuffer, iBufferLen);
	
	// read original pixels in rect
	resetAndReadPixels(pNode, tRect, &pBuffer);
	
	// make data privider with data
	CCImage * pImage = new CCImage();
	if (pImage && pImage->initWithImageData(pBuffer, iBufferLen, CCImage::kFmtRawData, tx, ty, bitsPerComponent))
	{
		CC_SAFE_FREE(pBuffer);
		return pImage;
	}
	CNLog("error");
	CC_SAFE_RELEASE(pImage);
	CC_SAFE_FREE(pBuffer);
	return NULL;
}

NS_CN_END
