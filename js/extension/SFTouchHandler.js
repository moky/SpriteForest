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
//  SFTouchHandler.js
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
	var TouchHandler = function() {
		sf.EventHandler.prototype.ctor.call(this);
	};
	
	//
	//  static functions
	//
	var create = function(eventTree, actionTree) {
		var handler = new sf.TouchHandler();
		if (handler.init(eventTree, actionTree)) {
			return handler;
		}
		return null;
	};
	
	//
	//  instance functions
	//
	
	// CNTouchDelegate
	// button
	var onFingerDown = function(node) {
		this.doEvent('onFingerDown', node);
		this.doEvent('onMouseDown', node); // deprecated
	};
	var onFingerUp = function(node) {
		this.doEvent('onFingerUp', node);
		this.doEvent('onMouseUp', node); // deprecated
	};
	var onFingerOver = function(node) {
		this.doEvent('onFingerOver', node);
		this.doEvent('onMouseOver', node); // deprecated
	};
	var onFingerOut = function(node) {
		this.doEvent('onFingerOut', node);
		this.doEvent('onMouseOut', node); // deprecated
	};
	var onFingerMove = function(node) {
		this.doEvent('onFingerMove', node);
		this.doEvent('onMouseMove', node); // deprecated
	};
	var onClick = function(node) {
		this.doEvent('onClick', node);
	};
	var onDoubleClick = function(node) {
		this.doEvent('onDoubleClick', node);
	};
	// guesture
	var onSwipeLeft = function(node) {
		this.doEvent('onSwipeLeft', node);
	};
	var onSwipeRight = function(node) {
		this.doEvent('onSwipeRight', node);
	};
	var onSwipeUp = function(node) {
		this.doEvent('onSwipeUp', node);
	};
	var onSwipeDown = function(node) {
		this.doEvent('onSwipeDown', node);
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: TouchHandler,
		
		// CNTouchDelegate
		// button
		onFingerDown: onFingerDown,
		onFingerUp: onFingerUp,
		onFingerOver: onFingerOver,
		onFingerOut: onFingerOut,
		onFingerMove: onFingerMove,
		onClick: onClick,
		onDoubleClick: onDoubleClick,
		// guesture
		onSwipeLeft: onSwipeLeft,
		onSwipeRight: onSwipeRight,
		onSwipeUp: onSwipeUp,
		onSwipeDown: onSwipeDown,
		
		// properties
	};
	
	// extends
	sf.TouchHandler = sf.EventHandler.extend(prop);
	
	// static
	sf.TouchHandler.create = create;
	
}(SpriteForest);
