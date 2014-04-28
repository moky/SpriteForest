;
/*!
 *
 *  SpriteForest JavaScript Library v1.0.0
 *  http://github.com/moky/SpriteForest/js/
 *
 *  Copyright (c) 2014 moKy at slanissue.com
 *  Released under the MIT license
 *  http://en.wikipedia.org/wiki/MIT_License
 *
 */
//
//  SFNode.js
//  SpriteForest-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  construtor
	//
	var Node = function() {
		cn.Node.prototype.ctor.call(this);
	};
	
	var nodeWithString = function(string) {
		var Class = cn.classFromString(string);
		if (typeof Class !== 'function') {
			cn.error(string);
			return null;
		}
		
		var node = new Class();
		if (typeof node.init === 'function') {
			node.init();
		}
		return node;
	};
	var nodeWithDictionary = function(dict) {
		var Class = cn.classFromString(dict['Class']);
		if (typeof Class !== 'function') {
			cn.error(dict);
			return null;
		}
		
		var node = new Class();
		if (typeof node.initWithDictionary === 'function') {
			node.initWithDictionary(dict);
		} else if (typeof node.init === 'function') {
			node.init();
		}
		return node;
	};
	
	//
	//  static functions
	//
	var create = function() {
		if (arguments.length === 0 || !arguments[0]) {
			var node = new sf.Node();
			node.init();
			return node;
		} else if (typeof arguments[0] === 'string') {
			return nodeWithString(arguments[0]);
		} else if (typeof arguments[0] === 'object') {
			return nodeWithDictionary(arguments[0]);
		} else {
			cn.error(arguments);
		}
		return null;
	};
	
	//
	//  instance functions
	//
	
	var _standard_string = function(string) {
		return string ? string.replace(/\s/g, '').toLowerCase() : '';
	};
	
	var processPositionAdjustment = function(child, dict, parent) {
		if (!child || child.getPositionX() == 0 || child.getPositionY() == 0) {
			return;
		}
		
		// standard string
		var position = _standard_string(dict['Position']);
		if (!position || position.length === 0) {
			return;
		} else if (position === 'topleft') {
			position = '{left,top}';
		} else if (position === 'topright') {
			position = '{right,top}';
		} else if (position === 'center') {
			position = '{center,middle}';
		} else if (position === 'bottomleft') {
			position = '{left,bottom}';
		} else if (position === 'bottomright') {
			position = '{right,bottom}';
		}
		
		// replace values
		if (position.length >= 7) { // "{0,top}"
			var parentSize = parent.getContentSize();
			
			var top = 0,
			left = 0,
			bottom = parentSize.height,
			right = parentSize.width,
			middle = bottom * 0.5,
			center = right * 0.5;
			
			var pos;
			// top
			pos = position.indexOf('top');
			if (pos >= 0)  {
				position = position.substr(0, pos) + top + position.substr(pos + 3);
			}
			// left
			pos = position.indexOf('left');
			if (pos >= 0)  {
				position = position.substr(0, pos) + left + position.substr(pos + 4);
			}
			// bottom
			pos = position.indexOf('bottom');
			if (pos >= 0)  {
				position = position.substr(0, pos) + bottom + position.substr(pos + 6);
			}
			// right
			pos = position.indexOf('right');
			if (pos >= 0)  {
				position = position.substr(0, pos) + right + position.substr(pos + 5);
			}
			// middle
			pos = position.indexOf('middle');
			if (pos >= 0)  {
				position = position.substr(0, pos) + middle + position.substr(pos + 6);
			}
			// center
			pos = position.indexOf('center');
			if (pos >= 0)  {
				position = position.substr(0, pos) + center + position.substr(pos + 6);
			}
		}
		
		// set it
		if (position.length >= 5) { // "{0,0}"
			child.setPosition(cc.PointFromString(position));
		}
	};
	
	var processScaleMode = function(child, dict, parent) {
		if (!child || child.getPositionX() == 1 || child.getPositionY() == 1) {
			return;
		}
		
		// standard string
		var scale = _standard_string(dict['Scale']);
		if (!scale || scale.length === 0) {
			return;
		}
		
		var parentSize = parent.getContentSize();
		var childSize = child.getContentSize();
		var scaleX = (parentSize.width * childSize.width == 0) ? 1 : parentSize.width / childSize.width;
		var scaleY = (parentSize.height * childSize.height == 0) ? 1 : parentSize.height / childSize.height;
		
		// replace values
		if (scale.length < 6 || scale.length > 10) {
			// do nothing
		} else if (scale === 'tofill') {
			child.setScale(scaleX, scaleY);
		} else if (scale === 'aspectfill') {
			child.setScale(scaleX > scaleY ? scaleX : scaleY);
		} else if (scale === 'aspectfit') {
			child.setScale(scaleX < scaleY ? scaleX : scaleY);
		} else if (scale === 'aspectx') {
			child.setScale(scaleX);
		} else if (scale === 'aspecty') {
			child.setScale(scaleY);
		}
	};
	
	var addChildren = function(array, spriteOrLayer, node) {
		node = node || this;
		
		var child, zOrder, count = array.length;
		for (var i = 0; i < count; ++i) {
			child = null;
			zOrder = 0;
			
			var data = array[i];
			if (!data || data.length === 0) {
				child = (spriteOrLayer === 0) ? sf.Sprite.create() : sf.Layer.create();
			} else if (typeof data === 'string') {
				cn.log('node from a string: ' + data);
				child = sf.Node.create(data);
			} else if (typeof data === 'object') {
				child = (spriteOrLayer === 0) ? sf.Sprite.create(data) : sf.Layer.create(data);
				// z-order
				zOrder = data['ZOrder'] ? data['ZOrder'] : 0;
				// support scale mode
				processScaleMode(child, data, node);
				// support position adjestment
				processPositionAdjustment(child, data, node);
			} else {
				cn.error(data);
			}
			
			if (child instanceof cc.Node) {
				node.addChild(child, zOrder);
			}
		}
	};
	
	var addSprites = function(array, node) {
		if (array && array.length > 0) {
			addChildren(array, 0, node || this);
		}
	};
	
	var addLayers = function(array, node) {
		if (array && array.length > 0) {
			addChildren(array, 1, node || this);
		}
	};
	
	var getTarget = function(string, node) {
		node = node || this;
		if (!string) {
			return node;
		}
		var target = _standard_string(string);
		
		// target by format: xxx.xxx.xxx
		var pos = target.indexOf('.');
		if (pos > 0) {
			var str1 = target.substring(0, pos);
			var str2 = target.substring(pos + 1);
			return getTarget(str2, getTarget(str1, node));
		}
		
		// target by simple name/tag
		if (target === 'scene') {
			return cn.Node.ancestorScene(node);
		} else if (target === 'self') {
			return node;
		} else if (target === 'parent') {
			return node.getParent();
		} else {
			// children sprite
			var children = node.getChildren();
			for (var i = children.length - 1; i >= 0; --i) {
				if (children[i].getTag() == target) {
					return children[i];
				}
			}
		}
		
		cn.log('no such target: ' + target);
		return null;
	};
	
	//------------------------------------------------------- sf.Node extensions
	
	var instanceExtensions = function(Node) {
		
		Node.prototype.addSprites = addSprites;
		Node.prototype.addLayers = addLayers;
		Node.prototype.getTarget = getTarget;
		
		return Node;
	};
	
	var classExtensions = function(Node) {
		
		Node.addSprites = addSprites;
		Node.addLayers = addLayers;
		Node.getTarget = getTarget;
		
		return Node;
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Node,
		
		// properties
	};
	
	// extends
	sf.Node = cn.Node.extend(prop);
	
	// static
	sf.Node.create = create;
	
	sf.Node.extensions = instanceExtensions;
	classExtensions(sf.Node);
	
}(SpriteForest);
