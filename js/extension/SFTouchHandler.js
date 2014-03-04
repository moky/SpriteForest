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
	function TouchHandler() {
		sf.EventHandler.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	function create(eventTree, actionTree) {
		var handler = new sf.TouchHandler();
		if (handler.init(eventTree, actionTree)) {
			return handler;
		}
		return null;
	}
	
	//
	//  instance functions
	//
	
	// CNTouchDelegate
	// button
	function onFingerDown(node) {
		this.doEvent('onFingerDown', node);
		this.doEvent('onMouseDown', node); // deprecated
	}
	function onFingerUp(node) {
		this.doEvent('onFingerUp', node);
		this.doEvent('onMouseUp', node); // deprecated
	}
	function onFingerOver(node) {
		this.doEvent('onFingerOver', node);
		this.doEvent('onMouseOver', node); // deprecated
	}
	function onFingerOut(node) {
		this.doEvent('onFingerOut', node);
		this.doEvent('onMouseOut', node); // deprecated
	}
	function onFingerMove(node) {
		this.doEvent('onFingerMove', node);
		this.doEvent('onMouseMove', node); // deprecated
	}
	function onClick(node) {
		this.doEvent('onClick', node);
	}
	function onDoubleClick(node) {
		this.doEvent('onDoubleClick', node);
	}
	// guesture
	function onSwipeLeft(node) {
		this.doEvent('onSwipeLeft', node);
	}
	function onSwipeRight(node) {
		this.doEvent('onSwipeRight', node);
	}
	function onSwipeUp(node) {
		this.doEvent('onSwipeUp', node);
	}
	function onSwipeDown(node) {
		this.doEvent('onSwipeDown', node);
	}
	
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
