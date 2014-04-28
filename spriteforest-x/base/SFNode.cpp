//
//  SFNode.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFNode.h"

#include "SFSprite.h"
#include "SFLayer.h"
#include "SFScene.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

CCNode * SFNode::nodeWithString(const char * pszString)
{
	if (!pszString || strlen(pszString) == 0)
	{
		CNLog("could not happen!");
		return NULL;
	}
	
	std::string string(pszString);
	string = CNString::trim(string);
	if (CNString::hasPrefix(string, "include class=\""))
	{
		string = string.substr(15);
		std::size_t pos = string.find('"');
		if (pos == std::string::npos)
		{
			CNLog("parse error, string = %s", string.c_str());
			return NULL;
		}
		string = string.substr(0, pos);
	}
	CNLog("creating node from string: %s", string.c_str());
	
	CCObject * pObject = CNRuntimeClass::createObject(string.c_str());
	return dynamic_cast<CCNode *>(pObject);
}

CCNode * SFNode::nodeWithDictionary(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("could not happen!");
		return NULL;
	}
	
	CCString * pClassName = (CCString *)pDict->objectForKey("Class");
	if (!pClassName)
	{
		CNLog("could not happen!");
		return NULL;
	}
	
	CCObject * pObject = CNRuntimeClass::createObject(pClassName->getCString());
	if (SFSprite * pSprite = dynamic_cast<SFSprite *>(pObject))
	{
		pSprite->initWithDictionary(pDict);
		return pSprite;
	}
	else if (SFLayer * pLayer = dynamic_cast<SFLayer *>(pObject))
	{
		pLayer->initWithDictionary(pDict);
		return pLayer;
	}
	else if (SFScene * pScene = dynamic_cast<SFScene *>(pObject))
	{
		pScene->initWithDictionary(pDict);
		return pScene;
	}
	else if (CCNode * pNode = dynamic_cast<CCNode *>(pObject))
	{
		CNLog("user defined node: %s", pClassName->getCString());
		return pNode;
	}
	CNLog("unrecognized node: %s", pClassName->getCString());
	return NULL;
}

std::string & SFNode_stringByRemoveSpaces(std::string & string)
{
//	CNLog("before: [%s]", string.c_str());
	std::size_t p1, p2 = 0;
	while ((p1 = string.find_first_of(" \n\r\t", p2)) != std::string::npos)
	{
		p2 = string.find_first_not_of(" \n\r\t", p1 + 1);
		if (p2 == std::string::npos)
		{
			string = string.substr(0, p1);
			break;
		}
		
		string = string.substr(0, p1) + string.substr(p2);
		p2 = p1 + 1;
	}
//	CNLog(" after: [%s]", string.c_str());
	
	return string;
}

void SFNode_processPositionAdjustment(CCNode * pParent, CCNode * pChild, CCDictionary * pDict)
{
	if (!pChild || abs(pChild->getPositionX()) > 0.01f || abs(pChild->getPositionY()) > 0.01f)
	{
		return;
	}
	CCString * pPosition = (CCString *)pDict->objectForKey("Position");
	std::string position = pPosition ? pPosition->getCString() : "";
	position = SFNode_stringByRemoveSpaces(position);
	if (position.empty())
	{
		return;
	}
	//CNLog("position: %s", position.c_str());
	position = CNString::lowercaseString(position);
	
	// const strings
	if (position.length() < 6 || position.length() > 11)
	{
		// do nothing
	}
	else if (strcmp(position.c_str(), "topleft") == 0)
	{
		position = "{left,top}";
	}
	else if (strcmp(position.c_str(), "topright") == 0)
	{
		position = "{right,top}";
	}
	else if (strcmp(position.c_str(), "center") == 0)
	{
		position = "{center,middle}";
	}
	else if (strcmp(position.c_str(), "bottomleft") == 0)
	{
		position = "{left,bottom}";
	}
	else if (strcmp(position.c_str(), "bottomright") == 0)
	{
		position = "{right,bottom}";
	}
	
	// replacing values
	if (position.length() >= 7) // "{0,top}"
	{
		CCSize parentSize = pParent->getContentSize();
		
		std::string top("0");
		std::string middle("0");
		std::string bottom("0");
		std::string left("0");
		std::string center("0");
		std::string right("0");
		
		top = CNString::stringWithFormat(top, "%.0f", parentSize.height);
		middle = CNString::stringWithFormat(middle, "%.0f", parentSize.height / 2);
		center = CNString::stringWithFormat(center, "%.0f", parentSize.width / 2);
		right = CNString::stringWithFormat(right, "%.0f", parentSize.width);
		
		std::size_t pos;
		
		pos = position.find("top");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + top + position.substr(pos + 3);
		}
		pos = position.find("middle");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + middle + position.substr(pos + 6);
		}
		pos = position.find("bottom");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + bottom + position.substr(pos + 6);
		}
		pos = position.find("left");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + left + position.substr(pos + 4);
		}
		pos = position.find("center");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + center + position.substr(pos + 6);
		}
		pos = position.find("right");
		if (pos != std::string::npos)
		{
			position = position.substr(0, pos) + right + position.substr(pos + 5);
		}
	}
	//CNLog("position: %s", position.c_str());
	
	// set it
	if (position.length() >= 5) // "{0,0}"
	{
		pChild->setPosition(CCPointFromString(position.c_str()));
	}
}

void SFNode_processScaleMode(CCNode * pParent, CCNode * pChild, CCDictionary * pDict)
{
	if (!pChild || abs(pChild->getScaleX() - 1) > 0.01f || abs(pChild->getScaleY() - 1) > 0.01f)
	{
		return;
	}
	CCString * pScale = (CCString *)pDict->objectForKey("Scale");
	std::string scale = pScale ? pScale->getCString() : "";
	scale = SFNode_stringByRemoveSpaces(scale);
	if (scale.empty())
	{
		return;
	}
	//CNLog("scale: %s", scale.c_str());
	scale = CNString::lowercaseString(scale);
	
	CCSize parentSize = pParent->getContentSize();
	CCSize childSize = pChild->getContentSize();
	float fScaleX = (parentSize.width * childSize.width == 0) ? 1 : parentSize.width / childSize.width;
	float fScaleY = (parentSize.height * childSize.height == 0) ? 1 : parentSize.height / childSize.height;
	
	if (scale.length() < 6 || scale.length() > 10)
	{
		// do nothing
	}
	else if (strcmp(scale.c_str(), "tofill") == 0)
	{
		pChild->setScaleX(fScaleX);
		pChild->setScaleY(fScaleY);
	}
	else if (strcmp(scale.c_str(), "aspectfill") == 0)
	{
		pChild->setScale(MAX(fScaleX, fScaleY));
	}
	else if (strcmp(scale.c_str(), "aspectfit") == 0)
	{
		pChild->setScale(MIN(fScaleX, fScaleY));
	}
	else if (strcmp(scale.c_str(), "aspectx") == 0)
	{
		pChild->setScale(fScaleX);
	}
	else if (strcmp(scale.c_str(), "aspecty") == 0)
	{
		pChild->setScale(fScaleY);
	}
}

void SFNode_addChildren(CCNode * pNode, CCArray * pArray, const int spriteOrLayer)
{
	CCNode * pChild;
	int iZOrder;
	
	int count = pArray->count();
	for (int i = 0; i < count; i++)
	{
		CCPoolManager * pm = CCPoolManager::sharedPoolManager();
		pm->push();
		
		pChild = NULL;
		iZOrder = 0;
		
		CCObject * pData = pArray->objectAtIndex(i);
		if (CCString * pString = dynamic_cast<CCString *>(pData))
		{
			CNLog("node from a string: %s", pString->getCString());
			pChild = (spriteOrLayer == 0) ? SFSprite::nodeWithString(pString->getCString()) : SFLayer::nodeWithString(pString->getCString());
		}
		else if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pData))
		{
			pChild = (spriteOrLayer == 0) ? SFSprite::nodeWithDictionary(pDict) : SFLayer::nodeWithDictionary(pDict);
			CCString * pZOrder = (CCString *)pDict->objectForKey("ZOrder");
			iZOrder = (pZOrder) ? pZOrder->intValue() : 0;
			
			// support Scale Mode
			SFNode_processScaleMode(pNode, pChild, pDict);
			
			// support Position Adjustment
			SFNode_processPositionAdjustment(pNode, pChild, pDict);
		}
		else
		{
			CNLog("unrecongnized node");
		}
		
		if (pChild)
		{
			pNode->addChild(pChild, iZOrder);
		}
		else
		{
			CNLog("error");
		}
		
		pm->pop();
	}
}

void SFNode::addSprites(CCNode * pNode, CCArray * pArray)
{
	if (pNode && pArray)
	{
		SFNode_addChildren(pNode, pArray, 0);
	}
}

void SFNode::addLayers(CCNode * pNode, CCArray * pArray)
{
	if (pNode && pArray)
	{
		SFNode_addChildren(pNode, pArray, 1);
	}
}

CCNode * SFNode::getTarget(CCNode * pNode, const char * pszTarget)
{
	if (!pNode || !pszTarget || strlen(pszTarget) == 0)
	{
		return pNode;
	}
	
	// target by format: xxx.xxx.xxx
	std::string str(pszTarget);
	int pos = str.find('.');
	if (pos != std::string::npos)
	{
		std::string str1(str.substr(0, pos));
		std::string str2(str.substr(pos + 1));
		return getTarget(getTarget(pNode, str1.c_str()), str2.c_str());
	}
	
	// target by simple name/tag
	if (strcasecmp(pszTarget, "scene") == 0)
	{
		return CNNode::ancestorScene(pNode);
	}
	else if (strcasecmp(pszTarget, "self") == 0)
	{
		return pNode;
	}
	else if (strcasecmp(pszTarget, "parent") == 0)
	{
		return pNode->getParent();
	}
	else
	{
		// children sprite
		int iTag = atoi(pszTarget);
		CCObject * pChild = NULL;
		CCARRAY_FOREACH_REVERSE(pNode->getChildren(), pChild)
		{
			if (((CCNode *)pChild)->getTag() == iTag)
			{
				return (CCNode *)pChild;
			}
		}
	}
	
	CNLog("no such target: %s", pszTarget);
	return NULL;
}

NS_SF_END
