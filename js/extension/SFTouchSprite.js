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
//  SFTouchSprite.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 1, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function TouchSprite() {
		sf.Sprite.prototype.ctor.call(this);
		this._controller = null;
		this._irregular = false;
		this._touchBounds = null;
	}
	
	//
	//  static functions
	//
	function create() {
		sf.Sprite.create.apply(this, arguments);
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.Sprite.prototype.init.call(this)) {
			return false;
		}
		
		if (!this._controller) { // no need to create the touch controller again
			var controller = new cn.TouchController();
			if (controller.init()) {
				this._controller = controller;
			}
		}
		
		this._irregular = false;
		this._touchBounds = cc.RectZero();
		
		return true;
	}
	
	function appointHandler(eventTree, actionTree) {
		var handler = sf.TouchHandler.create(eventTree, actionTree);
		this.setEventDelegate(handler);
	}
	
	function onEnter() {
		sf.Sprite.prototype.onEnter.call(this);
		
		var controller = this._controller;
		var delegate = this.getEventDelegate();
		
		if (controller) {
			controller.setNode(this);
			//if (delegate instanceof cn.TouchDelegate)
			controller.setDelegate(delegate);
		}
	}
	function onExit() {
		var controller = this._controller;
		
		if (controller) {
			controller.setDelegate(null);
			controller.setNode(null);
		}
		
		sf.Sprite.prototype.onExit.call(this);
	}
	
	// CNNode extensions
	function containsNodeSpacePoint(point) {
		if (!cc.rectEqualToRect(this._touchBounds, cc.RectZero()) &&
			!cc.rectContainsPoint(this._touchBounds, point)) {
			return false;
		}
		return sf.Sprite.prototype.containsNodeSpacePoint.call(this, point);
	}
	function containsTouchLocation(touch) {
		return sf.Sprite.prototype.containsTouchLocationWithPixel.call(this, touch, this._irregular);
	}
	function setAttributes(dict) {
		if (!sf.Sprite.prototype.setAttributes.call(this, dict)) {
			return false;
		}
		
		// Irregular
		var irregular = dict['Irregular'];
		this._irregular = irregular;
		
		// TouchBounds
		var touchBounds = dict['TouchBounds'];
		this._touchBounds = touchBounds ? cc.RectFromString(touchBounds) : cc.RectZero();
		
		return true;
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: TouchSprite,
		
		init: init,
		
		appointHandler: appointHandler,
		
		onEnter: onEnter,
		onExit: onExit,
		
		// CNNode extensions
		containsNodeSpacePoint: containsNodeSpacePoint,
		containsTouchLocation: containsTouchLocation,
		setAttributes: setAttributes,
		
		// properties
		_controller: null,
		_irregular: false,
		_touchBounds: null,
	};
	
	// extends
	sf.TouchSprite = sf.Sprite.extend(prop);
	
	// static
	sf.TouchSprite.create = sf.Sprite.create;
	
}(SpriteForest);
