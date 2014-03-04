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
//  SFDragSprite.js
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
	function DragSprite() {
		sf.TouchSprite.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.TouchSprite.prototype.init.call(this)) {
			return false;
		}
		
		return true;
	}
	
	function appointHandler(eventTree, actionTree) {
//		var handler = sf.TouchHandler.create(eventTree, actionTree);
//		this.setEventDelegate(handler);
	}
	
	function setAttributes(dict) {
		if (!sf.TouchSprite.prototype.setAttributes.call(this, dict)) {
			return false;
		}
		
		return true;
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: DragSprite,
		
		init: init,
		
		appointHandler: appointHandler,
		
		setAttributes: setAttributes,
		
		// properties
		_dragRange: null,
		_dragTied: false,
	};
	
	// extends
	sf.DragSprite = sf.TouchSprite.extend(prop);
	
	// static
	sf.DragSprite.create = sf.TouchSprite.create;
	
}(SpriteForest);
