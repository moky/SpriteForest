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
//  SFActionTransform.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 4, 2014.
//

//===================================================================== Rotation

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		this._angle = dict['Angle'] || dict['Rotation'];
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_angle: null,
	};
	
	function rotateTo() {
		return cc.RotateTo.create(this._duration, this._angle);
	}
	function rotateBy() {
		return cc.RotateBy.create(this._duration, this._angle);
	}
	
	prop.ccAction = rotateTo;
	sf.RotateTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = rotateBy;
	sf.RotateBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//===================================================================== Movement

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var position = dict['Position'];
		this._position = position ? cc.PointFromString(position) : cc.PointZero();
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_position: null,
	};
	
	function moveTo() {
		return cc.MoveTo.create(this._duration, this._position);
	}
	function moveBy() {
		return cc.MoveBy.create(this._duration, this._position);
	}
	
	prop.ccAction = moveTo;
	sf.MoveTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = moveBy;
	sf.MoveBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//======================================================================== Scale

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var scale = dict['Scale'];
		if (scale !== undefined) {
			this._scaleX = this._scaleY = scale;
		} else {
			var scaleX = dict['ScaleX'];
			var scaleY = dict['ScaleY'];
			this._scaleX = scaleX !== undefined ? scaleX : 1.0;
			this._scaleY = scaleY !== undefined ? scaleY : 1.0;
		}
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_scaleX: 1.0,
		_scaleY: 1.0,
	};
	
	function scaleTo() {
		return cc.ScaleTo.create(this._duration, this._scaleX, this._scaleY);
	}
	function scaleBy() {
		return cc.ScaleBy.create(this._duration, this._scaleX, this._scaleY);
	}
	
	prop.ccAction = scaleTo;
	sf.ScaleTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = scaleBy;
	sf.ScaleBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//========================================================================= Skew

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var skew = dict['Skew'];
		if (skew !== undefined) {
			this._skewX = this._skewY = skew;
		} else {
			var skewX = dict['SkewX'];
			var skewY = dict['SkewY'];
			this._skewX = skewX !== undefined ? skewX : 1.0;
			this._skewY = skewY !== undefined ? skewY : 1.0;
		}
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_skewX: 1.0,
		_skewY: 1.0,
	};
	
	function skewTo() {
		return cc.SkewTo.create(this._duration, this._skewX, this._skewY);
	}
	function skewBy() {
		return cc.SkewBy.create(this._duration, this._skewX, this._skewY);
	}
	
	prop.ccAction = skewTo;
	sf.SkewTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = skewBy;
	sf.SkewBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//========================================================================= Jump

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		
		var position = dict['Position'];
		this._position = position ? cc.PointFromString(position) : cc.PointZero();
		
		this._height = dict['Height'];
		this._jumps = dict['Jumps'];
		
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_position: null,
		_height: 0,
		_jumps: 0,
	};
	
	function jumpTo() {
		return cc.JumpTo.create(this._duration, this._position, this._height, this._jumps);
	}
	function jumpBy() {
		return cc.JumpBy.create(this._duration, this._position, this._height, this._jumps);
	}
	
	prop.ccAction = jumpTo;
	sf.JumpTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = jumpBy;
	sf.JumpBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//======================================================================= Bezier

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		
		var conf = {};
		
		var ep = dict['EndPosition'];
		conf.endPosition = ep ? cc.PointFromString(ep) : cc.PointZero();
		
		var p1 = dict['ControlPoint1'];
		conf.controlPoint_1 = p1 ? cc.PointFromString(p1) : cc.PointZero();
		
		var p2 = dict['ControlPoint2'];
		conf.controlPoint_2 = p2 ? cc.PointFromString(p2) : cc.PointZero();
		
		this._bezierConfig = conf;
		
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_bezierConfig: null,
	};
	
	function bezierTo() {
		return cc.BezierTo.create(this._duration, this._bezierConfig);
	}
	function bezierBy() {
		return cc.BezierBy.create(this._duration, this._bezierConfig);
	}
	
	prop.ccAction = bezierTo;
	sf.BezierTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = bezierBy;
	sf.BezierBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);
