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
	
}(SpriteForest);

//==============================================================================

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	function MagicBuilder(name) {
		
		function ccAction() {
			var ccClass = cn.classFromString('CCAction' + name);
			return ccClass ? ccClass.create(this._dict) : null;
		}
		
		var prop = {
			ctor: sf.ActionMagic.prototype.ctor,
			ccAction: ccAction,
		};
		
		var sfClass = sf.ActionMagic.extend(prop);
		
		sf['Action' + name] = sfClass;
		return sfClass;
	}
	
	// magic
	MagicBuilder('Audio');
	MagicBuilder('Video');
	MagicBuilder('Particle');
	MagicBuilder('Web');
	MagicBuilder('Alert');
	MagicBuilder('AddChild');
	MagicBuilder('RemoveFromParent');
	MagicBuilder('StopAllActions');
	// magic slow
	MagicBuilder('LoadingIndicator');
	MagicBuilder('Forest');
	MagicBuilder('Scene');
	
}(SpriteForest);
