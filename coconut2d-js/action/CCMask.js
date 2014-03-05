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
//  CCMask.js
//  Coconut2D-HTML5
//
//  Created by moKy on Mar. 5, 2014.
//

!function(cc) {
	'use strict';
	
	//
	//  construtor
	//
	function MaskTo() {
		cc.ActionInterval.prototype.ctor.call(this);
		this._startRect = null;
		this._endRect = null;
		this._delta = null;
	}
	
	//
	//  static functions
	//
	function create(duration, rect) {
		var action = new cc.MaskTo();
		if (action.initWithDuration(duration, rect)) {
			return action;
		}
		return null;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!cc.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._startRect = null;
		this._endRect = null;
		this._delta = null;
		return true;
	}
	function initWithDuration(duration, rect) {
		if (!cc.ActionInterval.prototype.initWithDuration.call(this, duration)) {
			return false;
		}
		this._endRect = cc.RECT_PIXELS_TO_POINTS(rect);
		return true;
	}
	
	function clone() {
		return create(this._duration, this._endRect);
	}
	
	function startWithTarget(target) {
		cc.ActionInterval.prototype.startWithTarget.call(this, target);
		var sprite = target;
		if (sprite instanceof cc.Sprite) {
			var rect1 = sprite.getTextureRect();
			var rect2 = this._endRect;
			
			var _x = rect2.getX() - rect1.getX();
			var _y = rect2.getY() - rect1.getY();
			var _w = rect2.getWidth() - rect1.getWidth();
			var _h = rect2.getHeight() - rect1.getHeight();
			
			this._startRect = rect1;
			this._delta = cc.rect(_x, _y, _w, _h);
		}
	}
	
	function update(time) {
		if (isNaN(time)) {
			this.update(1);
			this.stop();
		}
		var sprite = this._target;
		if (sprite instanceof cc.Sprite) {
			var rect1 = this._startRect;
			var rect2 = this._delta;
			
			var _x = rect1.getX() + rect2.getX() * time;
			var _y = rect1.getY() + rect2.getY() * time;
			var _w = rect1.getWidth() + rect2.getWidth() * time;
			var _h = rect1.getHeight() + rect2.getHeight() * time;
			
			sprite.setTextureRect(cc.rect(_x, _y, _w, _h));
		}
	}
	
	var prop = {
		ctor: MaskTo,
		
		init: init,
		initWithDuration: initWithDuration,
		
		clone: clone,
		
		startWithTarget: startWithTarget,
		update: update,
		
		// properties
		_startRect: null,
		_endRect: null,
		_delta: null,
	};
	
	// extends
	cc.MaskTo = cc.ActionInterval.extend(prop);
	
	// static
	cc.MaskTo.create = create;
	
}(cc);

//==============================================================================

!function(cc) {
	'use strict';
	
	//
	//  construtor
	//
	
	//
	//  static functions
	//
	function create(duration, rect) {
		var action = new cc.MaskBy();
		if (action.initWithDuration(duration, rect)) {
			return action;
		}
		return null;
	}
	
	//
	//  instance functions
	//
	
	function clone() {
		return create(this._duration, this._endRect);
	}
	
	function startWithTarget(target) {
		cc.MaskTo.prototype.startWithTarget.call(this, target);
		
		var rect = this._endRect;
		rect.setWidth(0);
		rect.setHeight(0);
		
		this._delta = rect;
	}
	
	var prop = {
		ctor: cc.MaskTo.prototype.ctor,
		
		clone: clone,
		
		startWithTarget: startWithTarget,
		
		// properties
	};
	
	// extends
	cc.MaskBy = cc.MaskTo.extend(prop);
	
	// static
	cc.MaskBy.create = create;
	
}(cc);
