;
/*!
 *
 *  Coconut-2D JavaScript Library v1.0.0
 *  http://github.com/moky/SpriteForest/coconut2d-js/
 *
 *  Copyright (c) 2014 moKy at slanissue.com
 *  Released under the MIT license
 *  http://en.wikipedia.org/wiki/MIT_License
 *
 */
//
//  CNNode.js
//  Coconut2D-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	//
	//  construtor
	//
	function Node() {
		cc.Node.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	function create() {
		var node = new cn.Node();
		node.init();
		return node;
	}
	
	//
	//  instance functions
	//
	
	//------------------------------------------------ Touch Location Extensions
	
	/**
	 *  Check whether the node contains a point
	 */
	function containsNodeSpacePoint(point, node) {
		node = node || this;
		for (var p = node; p; p = p.getParent()) {
			if (!p.isVisible()) {
				return false;
			}
		}
		var size = node.getContentSize();
		var rect = cc.RectZero();
		rect.setWidth(size.width);
		rect.setHeight(size.height);
		return cc.rectContainsPoint(rect, point);
	}
	
	/**
	 *  Check whether the point's pixel is visible in node space
	 */
	function containsVisiblePixelAtNodeSpacePoint(point, node) {
		node = node || this;
		var c = resetAndReadPixel(node, point);
		return c.a != 0;
	}
	
	/**
	 *  Check whether the current node was hit, transparent pixel will get through
	 */
	function containsTouchLocation(touch, node) {
		node = node || this;
		if (node.isKindOfClass(cn.Sprite) || node.isKindOfClass(cn.Layer)) {
			// call instance method
			return node.containsTouchLocation(touch);
		} else if (node.isKindOfClass(cn.Scene)) {
			// the current scene always contains any touch
			return node.isVisible();
		} else {
			// cc.Node
			return containsTouchLocationWithPixel(touch, false, node);
		}
	}
	function containsTouchLocationWithPixel(touch, checkPixel, node) {
		node = node || this;
		var point = node.convertTouchToNodeSpace(touch);
		if (node.isKindOfClass(cn.Sprite) || node.isKindOfClass(cn.Layer)) {
			if (!node.containsNodeSpacePoint(point)) {
				return false;
			}
		} else if (node.isKindOfClass(cn.Scene)) {
			// the current scene always contains any touch
			return node.isVisible();
		} else {
			// cc.Node
			if (!containsNodeSpacePoint(point, node)) {
				return false;
			}
		}
		if (!checkPixel) {
			return true;
		}
		return containsVisiblePixelAtNodeSpacePoint(point, node);
	}
	
	//---------------------------------------------------- Attributes Extensions
	
	/**
	 *  Set node's attributes from a dictionary
	 */
	function setAttributes(dict, node) {
		node = node || this;
		if (typeof dict !== 'object') {
			cn.error(dict, node);
			return false;
		}
		
		// size
		//if (CCSize::CCSizeEqualToSize(pNode->getContentSize(), CCSizeZero))
		{
			var size = dict['Size'];
			if (size) {
				node.setContentSize(cc.SizeFromString(size));
			} else {
				var width = dict['Width'];
				var height = dict['Height'];
				if (width !== undefined && height !== undefined) {
					node.setContentSize(width, height);
				}
			}
		}
		
		// position
		var position = dict['Position'];
		if (position) {
			node.setPosition(cc.PointFromString(position));
		} else {
			var x = dict['X'];
			var y = dict['Y'];
			if (x !== undefined && y !== undefined) {
				node.setPosition(x, y);
			}
		}
		
		// anchor point
		var anchorPoint = dict['AnchorPoint'];
		if (anchorPoint) {
			node.setAnchorPoint(cc.PointFromString(anchorPoint));
		} else {
			var ax = dict['AnchorX'];
			var ay = dict['AnchorY'];
			if (ax !== undefined && ay !== undefined) {
				node.setAnchorPoint(ax, ay);
			}
		}
		
		// rotation
		var rotation = dict['Rotation'];
		if (rotation !== undefined) {
			node.setRotation(rotation);
		}
		
		// scale
		var scale = dict['Scale'];
		if (scale !== undefined) {
			node.setScale(scale);
		} else {
			var sx = dict['ScaleX'];
			var sy = dict['ScaleY'];
			if (sx !== undefined && sy !== undefined) {
				node.setScale(sx, sy);
			}
		}
		
		// skew
		var skewX = dict['SkewX'];
		var skewY = dict['SkewY'];
		if (skewX !== undefined && skewY !== undefined) {
			node.setSkewX(skewX);
			node.setSkewY(skewY);
		}
		
		// tag
		var tag = dict['Tag'];
		if (tag !== undefined) {
			node.setTag(tag);
		}
		
		// visible
		var hidden = dict['Hidden'];
		if (hidden !== undefined) {
			node.setIsVisible(!hidden);
		}
		
		return true;
	}
	
	/**
	 *  Get the node's running scene
	 */
	function ancestorScene(node) {
		node = node || this;
		for (var p = node; p; p = p.getParent()) {
			if (p.isKindOfClass(cc.Scene)) {
				return p;
			}
		}
		cn.log('this node(tag:' + node.tag + ') is not in the running scene currently');
		return null;
	}
	
	//---------------------------------------------- Pixels and Image Extensions
	
	/**
	 *  read pixels in the rect
	 */
	function readPixels(rect, node) {
		node = node || this;
		//...
		return null;
	}
	
	function resetAndReadPixels(rect, node) {
		node = node || this;
		//...
		return null;
	}
	
	/**
	 *  read color at the pixel
	 */
	function readPixel(point, node) {
		node = node || this;
		//...
		return cc.Color4B(0, 0, 0, 255);
	}
	
	function resetAndReadPixel(point, node) {
		node = node || this;
		//...
		return cc.Color4B(0, 0, 0, 255);
	}
	
	/**
	 *  get Image from node
	 */
	function getImage(rect, node) {
		node = node || this;
		//...
		return null;
	}
	
	//------------------------------------------------------- cn.Node extensions
	
	function instanceExtensions(Node) {
		/* CNNode - Touch Location Extensions */
		Node.prototype.containsNodeSpacePoint = containsNodeSpacePoint;
		Node.prototype.containsVisiblePixelAtNodeSpacePoint = containsVisiblePixelAtNodeSpacePoint;
		Node.prototype.containsTouchLocation = function(touch) { containsTouchLocationWithPixel(touch, false, this); };
		Node.prototype.containsTouchLocationWithPixel = containsTouchLocationWithPixel;
		/* CNNode - Attributes Extensions */
		Node.prototype.setAttributes = setAttributes;
		Node.prototype.ancestorScene = ancestorScene;
		/* CNNode - Pixels and Image Extensions */
		Node.prototype.readPixels = readPixels;
		Node.prototype.resetAndReadPixels = resetAndReadPixels;
		Node.prototype.readPixel = readPixel;
		Node.prototype.resetAndReadPixel = resetAndReadPixel;
		Node.prototype.getImage = getImage;
		
		return Node;
	}
	
	function classExtensions(Node) {
		/* CNNode - Touch Location Extensions */
		Node.containsNodeSpacePoint = containsNodeSpacePoint;
		Node.containsVisiblePixelAtNodeSpacePoint = containsVisiblePixelAtNodeSpacePoint;
		Node.containsTouchLocation = containsTouchLocation;
		Node.containsTouchLocationWithPixel = containsTouchLocationWithPixel;
		/* CNNode - Attributes Extensions */
		Node.setAttributes = setAttributes;
		Node.ancestorScene = ancestorScene;
		/* CNNode - Pixels and Image Extensions */
		Node.readPixels = readPixels;
		Node.resetAndReadPixels = resetAndReadPixels;
		Node.readPixel = readPixel;
		Node.resetAndReadPixel = resetAndReadPixel;
		Node.getImage = getImage;
		
		return Node;
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Node,
		
		// properties
	};
	
	// extends
	cn.Node = cc.Node.extend(prop);
	
	// static
	cn.Node.create = create;
	
	cn.Node.extensions = instanceExtensions;
	classExtensions(cn.Node);
	
}(Coconut2D);
