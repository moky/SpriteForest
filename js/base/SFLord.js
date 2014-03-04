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
//  SFLord.js
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
	function Lord() {
		this._currentForest = null;
		this._histories = null;
	}
	
	//
	//  static functions
	//
	var _sharedLoard = null;
	
	function getInstance() {
		if (!_sharedLoard) {
			_sharedLoard = new sf.Lord();
			_sharedLoard.init();
		}
		return _sharedLoard;
	}
	
	function isForestExists() {
		//...
		return true;
	}
	
	//
	//  instance functions
	//
	function init() {
		this._currentForest = null;
		this._histories = [];
		return true;
	}
	
	function runIntoForest(path, scene) {
		
		if (!sf.Lord.isForestExists(path)) {
			cn.log('forest not exists at path: ' + path);
			return false;
		}
		
		var his = {};
		his['File'] = path;
		this._histories.push(his);
		
		cn.log('running into forest: ' + path);
		this._currentForest = sf.Forest.create(path);
		return this.performScene(scene);
	}
	
	function performScene(scene) {
		if (!this._currentForest) {
			cn.error(scene);
			return false;
		}
		
		var obj = null;
		if (!scene) {
		} else if (scene instanceof cc.Scene) {
			obj = scene;
		} else if (typeof scene === 'object') {
			obj = scene['Scene'];
		}
		var his = {};
		his['Scene'] = obj;
		this._histories.push(his);
		
		return this._currentForest.performScene(scene);
	}
	
	//////////////////////////////////
	//
	//  history stack:
	//
	//        (0)   File : "/path/to/forest/root/default.bundle/main.plist"
	//        (1)   Scene: [NSNull null]
	//        (2)   Scene: "scene2"
	//        (x)   ...
	//        (x+1) File : "/path/to/forest/root/forest2.bundle/main.plist"
	//        (x+2) Scene: [NSNull null]
	//
	function goBack() {
		// lock begin
		
		var histories = this._histories;
		
		if (histories.length <= 2) {
			cn.log('reach the first scene');
			return false;
		}
		
		histories.pop(); // remove last object
		
		var last = histories[histories.length - 1];
		
		var path;
		if (last['File']) {
			// it's the bounds of anthor forest
			histories.pop();
			
			// search the previous forest's path
			for (var i = histories.length - 1; i >= 0; --i) {
				var dict = histories[i];
				path = dict['File'];
				if (path) {
					cn.log('path = ' + path);
					break;
				}
			}
		}
		
		last = histories[histories.length - 1];
		var data = last ? last['Scene'] : null;
		
		histories.pop();
		
		// do it!
		if (path) {
			this.runIntoForest(path, data);
			if (histories.length > 2) {
				// remove duplicated 'File' record
				histories.splice(histories.length - 2, 1);
			}
		} else {
			this.performScene(data);
		}
		
		// lock end
		return true;
	}
	
	function showLoadingIndicator() {
		// do nothing
	}
	
	function hideLoadingIndicator() {
		// do nothing
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Lord,
		
		init: init,
		
		runIntoForest: runIntoForest,
		performScene: performScene,
		
		goBack: goBack,
		
		// for loading indicator
		showLoadingIndicator: showLoadingIndicator,
		hideLoadingIndicator: hideLoadingIndicator,
		
		// properties
		_currentForest: null,
		_histories: [],
	};
	
	// extends
	sf.Lord = cc.Class.extend(prop);
	
	// static
	sf.Lord.getInstance = getInstance;
	
	sf.Lord.isForestExists = isForestExists;
	
}(SpriteForest);
