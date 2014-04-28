//
//  CNNode.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-20.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNNode_h
#define Coconut2D_X_CNNode_h

#include "cnMacros.h"

NS_CN_BEGIN

class CN_DLL CNNode
{
public:
	CNNode(void) {}
	virtual ~CNNode(void) {}
	
#pragma mark Touch Location Extensions
	
	/**
	 *  Check whether the node contains a point
	 */
	static bool containsNodeSpacePoint(cocos2d::CCNode * pNode, const cocos2d::CCPoint & tPoint);
	
	/**
	 *  Check whether the point's pixel is visible in node space
	 */
	static bool containsVisiblePixelAtNodeSpacePoint(cocos2d::CCNode * pNode, const cocos2d::CCPoint & tPoint);
	
	/**
	 *  Check whether the current node was hit, transparent pixel will get through
	 */
	static bool containsTouchLocation(cocos2d::CCNode * pNode, cocos2d::CCTouch * pTouch, const bool bCheckPixel);
	static bool containsTouchLocation(cocos2d::CCNode * pNode, cocos2d::CCTouch * pTouch);
	
#pragma mark Attributes Extensions
	
	/**
	 *  Set node's attributes from a dictionary
	 */
	static bool setAttributes(cocos2d::CCNode * pNode, cocos2d::CCDictionary * pDict);
	
	/**
	 *  Get the node's running scene
	 */
	static cocos2d::CCScene * ancestorScene(cocos2d::CCNode * pNode);
	
#pragma mark Pixels and Image Extensions
	
	/**
	 *  read pixels in the rect
	 */
	static void readPixels(cocos2d::CCNode * pNode, const cocos2d::CCRect & tRect, cocos2d::ccColor4B ** pBuffer);
	static void resetAndReadPixels(cocos2d::CCNode * pNode, const cocos2d::CCRect & tRect, cocos2d::ccColor4B ** pBuffer);
	
	/**
	 *  read color at the pixel
	 */
	static cocos2d::ccColor4B readPixel(cocos2d::CCNode * pNode, const cocos2d::CCPoint & tPoint);
	static cocos2d::ccColor4B resetAndReadPixel(cocos2d::CCNode * pNode, const cocos2d::CCPoint & tPoint);
	
	/**
	 *  get Image from node
	 */
	static cocos2d::CCImage * getImage(cocos2d::CCNode * pNode);
	static cocos2d::CCImage * getImage(cocos2d::CCNode * pNode, const cocos2d::CCRect & tRect);
	
	static cocos2d::CCImage * getImageThreadSafe(cocos2d::CCNode * pNode);
	static cocos2d::CCImage * getImageThreadSafe(cocos2d::CCNode * pNode, const cocos2d::CCRect & tRect);
};

#define CNNODE_EXTENSIONS(class) /* CNNode extensions begin */ \
	public: \
		/* CNNode - Touch Location Extensions */ \
		virtual bool containsNodeSpacePoint(const cocos2d::CCPoint & tPoint) { return CNNode::containsNodeSpacePoint(this, tPoint); } \
		virtual bool containsVisiblePixelAtNodeSpacePoint(const cocos2d::CCPoint & tPoint) { return CNNode::containsVisiblePixelAtNodeSpacePoint(this, tPoint); } \
		virtual bool containsTouchLocation(cocos2d::CCTouch * pTouch, const bool bCheckPixel) { return CNNode::containsTouchLocation(this, pTouch, bCheckPixel); } \
		virtual bool containsTouchLocation(cocos2d::CCTouch * pTouch) { return CNNode::containsTouchLocation(this, pTouch, false); } \
		/* CNNode - Attributes Extensions */ \
		virtual bool setAttributes(cocos2d::CCDictionary * pDict) { return CNNode::setAttributes(this, pDict); } \
		virtual cocos2d::CCScene * ancestorScene(void) { return CNNode::ancestorScene(this); } \
		/* CNNode - Pixels and Image Extensions */ \
		virtual void readPixels(const cocos2d::CCRect & tRect, cocos2d::ccColor4B ** pBuffer) { CNNode::readPixels(this, tRect, pBuffer); } \
		virtual void resetAndReadPixels(const cocos2d::CCRect & tRect, cocos2d::ccColor4B ** pBuffer) { CNNode::resetAndReadPixels(this, tRect, pBuffer); } \
		virtual cocos2d::ccColor4B readPixel(const cocos2d::CCPoint & tPoint) { return CNNode::readPixel(this, tPoint); } \
		virtual cocos2d::ccColor4B resetAndReadPixel(const cocos2d::CCPoint & tPoint) { return CNNode::resetAndReadPixel(this, tPoint); } \
		virtual cocos2d::CCImage * getImage(void) { return CNNode::getImage(this); } \
		virtual cocos2d::CCImage * getImage(const cocos2d::CCRect & tRect) { return CNNode::getImage(this, tRect); } \
/* CNNode extensions end */

NS_CN_END

#endif // Coconut2D_X_CNNode_h
