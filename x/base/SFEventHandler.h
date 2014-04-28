//
//  SFEventHandler.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFEventHandler_h
#define SpriteForest_X_SFEventHandler_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFEventDelegate
{
public:
	virtual bool doEvent(const char * pszEventName, cocos2d::CCNode * pNode) { CC_UNUSED_PARAM(pszEventName); CC_UNUSED_PARAM(pNode); return false; }
	virtual bool doAction(const char * pszActionName, cocos2d::CCNode * pNode) { CC_UNUSED_PARAM(pszActionName); CC_UNUSED_PARAM(pNode); return false; }
};

class SFEventHandler : public cocos2d::CCObject, public SFEventDelegate
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pEventTree, EventTree);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pActionTree, ActionTree);
	
public:
	SFEventHandler(void);
	virtual ~SFEventHandler(void);
	virtual bool init(void);
	
	static SFEventHandler * handler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	
	virtual bool init(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	
	virtual bool doEvent(const char * pszEventName, cocos2d::CCNode * pNode);
	virtual bool doAction(const char * pszActionName, cocos2d::CCNode * pNode);
	
	// for restore node reference to string, which usally in 'Target'
	void restore(void) const;
protected:
	void snapshot(void) const;
};

NS_SF_END

#endif
