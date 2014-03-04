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
//  SFActionVisible.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 4, 2014.
//

//======================================================================== Blink

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		this._times = dict['Times'];
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_times: null,
	};
	
	function blink() {
		return cc.Blink.create(this._duration, this._angle);
	}
	
	prop.ccAction = blink;
	sf.Blink = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//========================================================================= Fade

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		this._opacity = dict['Opacity'];
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_opacity: null,
	};
	
	function fadeIn() {
		return cc.FadeIn.create(this._duration);
	}
	function fadeOut() {
		return cc.FadeOut.create(this._duration);
	}
	function fadeTo() {
		return cc.FadeTo.create(this._duration, this._opacity);
	}
	
	prop.ccAction = fadeIn;
	sf.FadeIn = sf.ActionInterval.extend(prop);
	
	prop.ccAction = fadeOut;
	sf.FadeOut = sf.ActionInterval.extend(prop);
	
	prop.ccAction = fadeTo;
	sf.FadeTo = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//========================================================================= Tint

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		this._red = dict['Red'];
		this._green = dict['Green'];
		this._blue = dict['Blue'];
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_red: 0,
		_green: 0,
		_blue: 0,
	};
	
	function tintTo() {
		return cc.TintTo.create(this._duration, this._red, this._green, this._blue);
	}
	function tintBy() {
		return cc.TintBy.create(this._duration, this._red, this._green, this._blue);
	}
	
	prop.ccAction = tintTo;
	sf.TintTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = tintBy;
	sf.TintBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//========================================================================= Mask

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		
		var rect = dict['Rect'];
		this._rect = rect ? cc.RectFromString(rect) : cc.RectZero();
		
		return true;
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		initWithDictionary: initWithDictionary,
		// properties
		_rect: null,
	};
	
	function maskTo() {
		return cc.MaskTo.create(this._duration, this._rect);
	}
	function maskBy() {
		return cc.MaskBy.create(this._duration, this._rect);
	}
	
	prop.ccAction = maskTo;
	sf.MaskTo = sf.ActionInterval.extend(prop);
	
	prop.ccAction = maskBy;
	sf.MaskBy = sf.ActionInterval.extend(prop);
	
}(SpriteForest);
