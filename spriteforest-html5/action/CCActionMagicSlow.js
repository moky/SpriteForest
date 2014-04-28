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
//  CCActionMagicSlow.js
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
	var ActionMagicSlow = function() {
		cc.ActionMagic.prototype.ctor.call(this);
	};
	
	//
	//  static functions
	//
	
	var showIndicator = function() {
		
	};
	
	var hideIndicator = function() {
		
	};
	
	//
	//  instance functions
	//
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: ActionMagicSlow,
		
		// properties
	};
	
	// extends
	cc.ActionMagicSlow = cc.ActionMagic.extend(prop);
	
	// static
	cc.ActionMagicSlow.create = cc.ActionMagic.create;
	
	cc.ActionMagicSlow.showIndicator = showIndicator;
	cc.ActionMagicSlow.hideIndicator = hideIndicator;
	
}(SpriteForest);

//==============================================================================

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	var MagicBuilder = function(name, execute) {
		
		var prop = {
			ctor: cc.ActionMagicSlow.prototype.ctor,
			execute: execute,
		};
		
		var ccClass = cc.ActionMagicSlow.extend(prop);
		ccClass.create = cc.ActionMagicSlow.create;
		ccClass.showIndicator = cc.ActionMagicSlow.showIndicator;
		ccClass.hideIndicator = cc.ActionMagicSlow.hideIndicator;
		
		cc['Action' + name] = ccClass;
		return ccClass;
	};
	
	// LoadingIndicator
	var executeLoadingIndicator = function() {
		// do nothing
	};
	MagicBuilder('LoadingIndicator', executeLoadingIndicator);
	
	var performForestWithDictonary = function(dict) {
		var myLord = sf.Lord.getInstance();
		var history = dict['History'];
		if (history) {
			if (history === 'goBack()') {
				if (myLord.goBack()) {
					cn.log('back to previous forest/scene');
				} else {
					cn.log('failed to go back');
				}
			} else {
				cn.log('unrecognized history info');
			}
			return;
		}
		
		var path = dict['Path'];
		var scene = dict['Scene'];
		
		if (path) {
			if (!scene || typeof scene === 'string') {
				scene = dict;
			}
			if (myLord.runIntoForest(path, scene)) {
				cn.log('run into forest ok, path: ' + path + ', scene: ' + scene);
			} else {
				cn.log('invalid forest');
			}
		} else if (scene) {
			if (myLord.performScene(scene)) {
				cn.log('perform scene ok, scene: ' + scene)
			} else {
				cn.log('failed to perform scene');
			}
		} else {
			cn.error(dict);
		}
	};
	
	// Forest
	var executeForest = function() {
		performForestWithDictonary(this._dict);
	};
	MagicBuilder('Forest', executeForest);
	
	// Scene
	var executeScene = function() {
		// this is a 'Scene' action info, transform it to a 'Forest' action
		var dict = { 'Scene' : this._dict };
		performForestWithDictonary(dict);
	};
	MagicBuilder('Scene', executeScene);
	
}(SpriteForest);
