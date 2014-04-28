//
//  SFSpriteBatchNode.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFSpriteBatchNode_h
#define SpriteForest_X_SFSpriteBatchNode_h

#include "../base/SFNode.h"

NS_SF_BEGIN

class SFSpriteBatchNode : public coconut2d::CNSpriteBatchNode
{
public:
	SFSpriteBatchNode(void);
	virtual ~SFSpriteBatchNode(void);
	virtual bool init(void);
	
	static cocos2d::CCNode * nodeWithString(const char * pszString);
	static cocos2d::CCNode * nodeWithDictionary(cocos2d::CCDictionary * pDict);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	// CNNode Extensions
	SFNODE_EXTENSIONS(SFSpriteBatchNode);
};

NS_SF_END

#endif
