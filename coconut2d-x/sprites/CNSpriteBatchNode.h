//
//  CNSpriteBatchNode.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-30.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNSpriteBatchNode_h
#define Coconut2D_X_CNSpriteBatchNode_h

#include "../CNNode.h"

NS_CN_BEGIN

class CNSpriteBatchNode : public cocos2d::CCSpriteBatchNode
{
public:
	virtual bool init(void) { return true; }
	
	static CNSpriteBatchNode * batchNodeWithFile(const char * pszImageFile);
	virtual bool initWithFile(const char * pszImageFile);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	// CNNode Extensions
	CNNODE_EXTENSIONS(CNSpriteBatchNode);
};

NS_CN_END

#endif
