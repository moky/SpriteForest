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
//  CNTouchObject.js
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
	var TouchObject = function() {
	};
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	var init = function() {
		this.count = 0;
		this.maxTouches = -1; // unlimited
		this.claimedTouches = [];
		this.delegate = null;
		return true;
	};
	
	var removeAllClaimedTouches = function() {
		this.claimedTouches = [];
	};
	
	var isClaimedTouch = function(touch) {
		var array = this.claimedTouches;
		for (var i = array.length - 1; i >= 0; --i) {
			if (array[i] == touch) {
				return true;
			}
		}
		return false;
	};
	
	var removeClaimedTouch = function(touch) {
		var array = this.claimedTouches;
		for (var i = array.length - 1; i >= 0; --i) {
			if (array[i] == touch) {
				array.splice(i, 1);
				return true;
			}
		}
		return false;
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: TouchObject,
		
		init: init,
		
		removeAllClaimedTouches: removeAllClaimedTouches,
		isClaimedTouch: isClaimedTouch,
		removeClaimedTouch: removeClaimedTouch,
		
		// properties
		count: 0,
		maxTouches: 0,
		claimedTouches: null,
		delegate: null,
	};
	
	// extends
	cn.TouchObject = cc.Class.extend(prop);
	
}(Coconut2D);
