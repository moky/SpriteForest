//
//  SFNode.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFNode_h
#define SpriteForest_X_SFNode_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SF_DLL SFNode : public coconut2d::CNNode
{
public:
	SFNode(void) : CNNode() {}
	virtual ~SFNode(void) {}
	
	static cocos2d::CCNode * nodeWithString(const char * pszString);
	static cocos2d::CCNode * nodeWithDictionary(cocos2d::CCDictionary * pDict);
	
	static void addSprites(cocos2d::CCNode * pNode, cocos2d::CCArray * pArray);
	static void addLayers(cocos2d::CCNode * pNode, cocos2d::CCArray * pArray);
	
	static cocos2d::CCNode * getTarget(cocos2d::CCNode * pNode, const char * pszTarget);
};

#define SFNODE_EXTENSIONS(class) /* SFNode extensions begin */ \
	public: \
		void addSprites(cocos2d::CCArray * pArray) { spriteforest::SFNode::addSprites(this, pArray); } \
		void addLayers(cocos2d::CCArray * pArray) { spriteforest::SFNode::addLayers(this, pArray); } \
		CCNode * getTarget(const char * pTarget) { return spriteforest::SFNode::getTarget(this, pTarget); } \
/* SFNode extensions end */

#define SF_RUNTIME_NODE_INIT(name)    CN_RUNTIME_CLASS_INIT(name, node)

NS_SF_END

#endif
