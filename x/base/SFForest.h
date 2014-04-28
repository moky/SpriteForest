//
//  SFForest.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFForest_h
#define SpriteForest_X_SFForest_h

#include "SFScene.h"

NS_SF_BEGIN

class SFForest : public cocos2d::CCObject
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, m_pPath, Path);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pScenes, Scenes);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, m_pDefaultScene, DefaultScene);
	
public:
	SFForest(void);
	virtual ~SFForest(void);
	virtual bool init(void);
	
	static SFForest * forest(const char * pszPath);
	virtual bool initWithPath(const char * pszPath);
	
	virtual cocos2d::CCScene * scene(const char * name) const;
	virtual bool performScene(cocos2d::CCObject * data) const;
};

NS_SF_END

#endif
