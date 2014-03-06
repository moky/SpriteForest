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
//  SFActionInstant.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 4, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: sf.FiniteTimeAction.prototype.ctor,
		
		// properties
	};
	
	// extends
	sf.ActionInstant = sf.FiniteTimeAction.extend(prop);
	
}(SpriteForest);

//==============================================================================

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function MagicBuilder(name) {
		
		function ccAction() {
			var ccClass = cc[name];
			return ccClass ? ccClass.create() : null;
		}
		
		var prop = {
			ctor: sf.ActionInstant.prototype.ctor,
			ccAction: ccAction,
		};
		
		var sfClass = sf.ActionInstant.extend(prop);
		
		sf['Action' + name] = sfClass;
		return sfClass;
	}
	
	// Show
	MagicBuilder('Show');
	// Hide
	MagicBuilder('Hide');
	// ToggleVisibility
	MagicBuilder('ToggleVisibility');
	// FlipX
	MagicBuilder('FlipX');
	// FlipY
	MagicBuilder('FlipY');
	
}(SpriteForest);

//======================================================================== Place

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function Place() {
		sf.ActionInstant.prototype.ctor.call(this);
		this._position = null;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInstant.prototype.init.call(this)) {
			return false;
		}
		this._position = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInstant.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var position = dict['Position'];
		if (position) {
			this._position = cc.PointFromString(position);
		}
		return true;
	}
	
	function ccAction() {
		return cc.Place.create(this._position);
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Place,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_position: null,
	};
	
	// extends
	sf.Place = sf.ActionInstant.extend(prop);
	
}(SpriteForest);

//===================================================================== CallFunc
//...

//==================================================================== CallFuncO
//...
