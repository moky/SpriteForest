//
//  SFDragSprite.h
//  SpriteForest-X
//
//  Created by Moky on 12-12-8.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFDragSprite_h
#define SpriteForest_X_SFDragSprite_h

#include "SFTouchSprite.h"

NS_SF_BEGIN

#pragma mark SFDragSpriteProtocol

class SF_DLL SFDragSpriteProtocol
{
public:
	virtual cocos2d::CCRect getDragRange(void) const { return cocos2d::CCRectZero; }
	virtual bool getDragTied(void) const { return false; }
};

#pragma mark SFDragSprite

class SF_DLL SFDragSprite : public SFTouchSprite, public SFDragSpriteProtocol
{
	CC_SYNTHESIZE(cocos2d::CCRect, m_tDragRange, DragRange);
	CC_SYNTHESIZE(bool, m_bDragTied, DragTied);
	
public:
	SFDragSprite(void);
	virtual ~SFDragSprite(void);
	virtual bool init(void);
	
	virtual void appointHandler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	
	virtual bool setAttributes(cocos2d::CCDictionary * pDict);
	// CNSprite factories
	CNSPRITE_FACTORIES(SFDragSprite);
};

#pragma mark SFDragHandler

class SF_DLL SFDragHandler : public SFTouchHandler
{
public:
	static SFDragHandler * handler(cocos2d::CCDictionary * pEventTree, cocos2d::CCDictionary * pActionTree);
	// CNDragDelegate
	// 如果当前条件下不允许拖放，则返回 NO；默认返回 YES
	virtual bool onDragStart(cocos2d::CCNode * pNode);
	// 如果到达了边界需要禁止移动，则返回 NO；默认返回 YES
	virtual bool onDrag(cocos2d::CCNode * pNode);
	// 如果松手后需要复原位置，则返回 NO；默认返回 YES
	virtual bool onDragEnd(cocos2d::CCNode * pNode);
};

#pragma mark Run-Time Type Identification

SF_RUNTIME_SPRITE(SFDragSprite);

NS_SF_END

#endif
