//
//  CNNode.h
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "cocos2d.h"


#pragma mark Touch Location Extensions

@interface CCNode (TouchLocationExtend)

/**
 *  Check whether the current node contains a point
 */
- (BOOL) containsNodeSpacePoint:(CGPoint)point;

/**
 *  Check whether the point's pixel is visible in current node space
 */
- (BOOL) containsVisiblePixelAtNodeSpacePoint:(CGPoint)point;

/**
 *  Check whether the current node was hit, transparent pixel will get through
 */
- (CGPoint) convertsTouchToNodeSpace:(UITouch *)touch;
- (BOOL) containsTouchLocation:(UITouch *)touch;
- (BOOL) containsTouchLocation:(UITouch *)touch checkPixel:(BOOL)check;

@end


#pragma mark Attributes Extensions

@interface CCNode (AttributesExtend)

/**
 *  Set node's attributes from a dictionary
 */
- (void) setAttributes:(NSDictionary *)dict;

/**
 *  Get the node's running scene
 */
- (CCScene *) scene;

@end


#pragma mark Pixels and Image Extensions

@interface CCNode (TextureExtend)

/**
 *  read pixels in the rect
 */
- (void) readPixels:(CGRect)rect buffer:(ccColor4B *)buffer;
- (void) resetAndReadPixels:(CGRect)rect buffer:(ccColor4B *)buffer;

/**
 *  read color at the pixel
 */
- (ccColor4B) readPixel:(CGPoint)point;
- (ccColor4B) resetAndReadPixel:(CGPoint)point;

/**
 *  get UIImage from node
 */
- (UIImage *) getUIImage;
- (UIImage *) getUIImageInRect:(CGRect)rect;

@end

