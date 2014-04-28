//
//  SFLord.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-4.
//  Copyright (c) 2012年 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFLord_h
#define SpriteForest_X_SFLord_h

#include "SFForest.h"

NS_SF_BEGIN

class SFLord : public cocos2d::CCObject
{
	CC_SYNTHESIZE_RETAIN(SFForest *, m_pCurrentForest, CurrentForest);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pHistory, History);
	
public:
	SFLord(void);
	virtual ~SFLord(void);
	virtual bool init(void);
	
	static SFLord * sharedLord(void);
	static void end(void);
	
	static bool isForestExists(const char * pszPath);
	
	bool runIntoForest(const char * pszPath, cocos2d::CCObject * scene/* = NULL */);
	bool performScene(cocos2d::CCObject * scene) const;
	
	bool goBack(void);
	
	// for loading indicator
	void showLoadingIndicator(void);
	void hideLoadingIndicator(void);
};

NS_SF_END

#endif
