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
//  SFActionMagic.js
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
	function ActionMagic() {
		sf.Action.prototype.ctor.call(this);
		this._dict = null;
	}
	
	//
	//  static functions
	//
	function create() {
		var action = new this();
		var flag = false;
		if (arguments.length < 1) {
			flag = action.init();
		} else {
			flag = action.initWithDictionary(arguments[0]);
		}
		return flag ? action : null;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.Action.prototype.init.call(this)) {
			return false;
		}
		this._dict = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.Action.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		this._dict = dict;
		return true;
	}
	
	function ccAction() {
		return cc.ActionMagic.create(dict);
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: ActionMagic,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		// properties
		_dict: null,
	};
	
	// extends
	sf.ActionMagic = sf.Action.extend(prop);
	
	// static
	sf.ActionMagic.create = create;
	
	//==========================================================================
	
	function MagicBuilder(name) {
		
		function ccAction() {
			var Class = cn.classFromString('CCAction' + name);
			return Class ? Class.create(this._dict) : null;
		}
		
		var prop = {
			ctor: ActionMagic,
			ccAction: ccAction,
		}
		
		var Class = sf.ActionMagic.extend(prop);
		Class.create = create;
		
		sf['Action' + name] = Class;
	}
	
	// magic
	MagicBuilder('Audio');
	// magic slow
	MagicBuilder('Forest');
	MagicBuilder('Scene');
	
}(SpriteForest);
