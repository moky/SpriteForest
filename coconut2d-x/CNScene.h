//
//  CNScene.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-21.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNScene_h
#define Coconut2D_X_CNScene_h

#include "CNNode.h"
#include "cocoa/CNSelector.h"

NS_CN_BEGIN

class CNTouchObject;

class CN_DLL CNScene : public cocos2d::CCScene, public cocos2d::CCStandardTouchDelegate, public CNSelectorDelegate
{
protected:
	cocos2d::CCDictionary * m_pTouchNodes;
	cocos2d::CCSet * m_pAllClaimedKeys;
	
	void addClaimedKey(const char * pszKey) const;
	void removeClaimedKey(const char * pszKey) const;
	bool isKeyClaimed(const char * pszKey) const;
	
public:
	CNScene(void);
	virtual ~CNScene(void);
	virtual bool init(void);
	
	virtual void onEnter();
	virtual void onExit();
	
	// call CCDirector: runWithScene / replaceScene
	static void perform(CCScene * scene);
	void perform(void); // perform self
	
#pragma mark Touch
	//---- for touch dispatching
	void addTouchNode(cocos2d::CCNode * node, cocos2d::CCTargetedTouchDelegate * delegate) const;
	void addTouchNode(cocos2d::CCNode * node, cocos2d::CCTargetedTouchDelegate * delegate, const int maxTouches) const;
	void removeTouchNode(cocos2d::CCNode * node) const;
	
protected:
	CNTouchObject * objectByNode(const cocos2d::CCNode * node) const;
	bool cnTouch(cocos2d::CCTouch * touch, cocos2d::CCEvent * event, const unsigned int touchType, CNTouchObject * touchObject);
	bool cnTouch(cocos2d::CCTouch * touch, cocos2d::CCEvent * event, const unsigned int touchType, cocos2d::CCNode * node);
	void cnTouches(cocos2d::CCSet * touches, cocos2d::CCEvent * event, const unsigned int touchType);
	
public:
    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(cocos2d::CCSet * pTouches, cocos2d::CCEvent * pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet * pTouches, cocos2d::CCEvent * pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet * pTouches, cocos2d::CCEvent * pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet * pTouches, cocos2d::CCEvent * pEvent);
	
	// CNNode Extensions
	CNNODE_EXTENSIONS(CNScene);
	// factory
	CN_INLINE_FACTORY(CNScene, node, init);
};

#pragma mark - CNTouchObject

class CN_DLL CNTouchObject : public cocos2d::CCObject
{
	CC_SYNTHESIZE(int, m_iCount, Count);
	CC_SYNTHESIZE(int, m_iMaxTouches, MaxTouches);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSet *, m_pClaimedTouches, ClaimedTouches);
	CN_SYNTHESIZE_RETAIN(cocos2d::CCTargetedTouchDelegate *, m_pDelegate, Delegate);
	
public:
	CNTouchObject(void);
	virtual ~CNTouchObject(void);
	virtual bool init(void);
	
	void removeAllClaimedTouches(void);
};

NS_CN_END

#endif
