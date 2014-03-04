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
//  CNLayer.js
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
	function Layer() {
		cc.Layer.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	function create() {
		var node = new cn.Layer();
		if (arguments.length === 0) {
			node.init();
		} else if (typeof arguments[0] === 'string') {
			node.initWithFile(arguments[0]);
		} else if (arguments[0] instanceof cc.Node) {
			node.initWithNode(arguments[0]);
		} else if (arguments[0] instanceof cc.Rect) {
			node.initWithFrame(arguments[0]);
		} else if (typeof arguments[0] === 'object') {
			node.initWithDictionary(arguments[0]);
		} else {
			cn.log('unknown arguments: ' + arguments);
		}
		return node;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!cc.Layer.prototype.init.call(this)) {
			cn.error(this);
			return false;
		}
		this.setAnchorPoint(cc.PointZero());
		this.ignoreAnchorPointForPosition(true); //this.setIsRelativeAnchorPoint(true);
		this.setPosition(cc.PointZero());
		return true;
	}
	function initWithFile(filename) {
		if (!this.init()) {
			return false;
		}
		var bg = cn.Sprite.create(filename);
		bg.setAnchorPoint(cc.PointZero());
		bg.setPosition(cc.PointZero());
		return this.initWithNode(bg);
	}
	function initWithNode(node) {
		var size = node.getContentSize();
		var anchor = node.getAnchorPointInPoints();
		var position = node.getPosition();
		
		var frame = cc.rect(position.x - anchor.x, position.y - anchor.y,
							size.width, size.height);
		if (!this.initWithFrame(frame)) {
			return false;
		}
		node.setAnchorPoint(cc.PointZero());
		node.setPosition(cc.PointZero());
		this.addChild(node);
		return true;
	}
	function initWithFrame(frame) {
		if (!this.init()) {
			return false;
		}
		this.setContentSize(frame.getWidth(), frame.getHeight());
		this.setPosition(frame.getX(), frame.getY());
		return true;
	}
	function initWithDictionary(dict) {
		if (!this.init()) {
			return false;
		}
		return this.setAttributes(dict);
	}
	
	function focus(point) {
		var winSize = cc.Director.getInstance().getWinSize();
		var center = cc.p(winSize.width * 0.5, winSize.height * 0.5);
		if (point) {
			// set focus
			var anchor = this.getAnchorPointInPoints();
			var distance = cc.p(anchor.x - point.x, anchor.y - point.y);
			this.setPosition(center.x - distance.x, center.y - distance.y);
		} else {
			// get focus
			var position = this.getPosition();
			return cc.p(center.x - position.x, center.y - position.y);
		}
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Layer,
		
		init: init,
		initWithFile: initWithFile,
		initWithNode: initWithNode,
		initWithFrame: initWithFrame,
		initWithDictionary: initWithDictionary,
		
		focus: focus,
		
		// properties
	};
	
	// extends
	cn.Layer = cc.Layer.extend(prop);
	
	// static
	cn.Layer.create = create;
	
	// CNNode Extensions
	cn.Node.extensions(cn.Layer);
	
}(Coconut2D);
