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
//  SFForest.js
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
	var Forest = function() {
		this._path = null;
		this._scenes = null;
		this._defaultScene = null;
	};
	
	//
	//  static functions
	//
	var create = function(path) {
		var obj = new sf.Forest();
		if (obj.initWithPath(path)) {
			return obj;
		}
		return null;
	};
	
	//
	//  instance functions
	//
	
	var init = function() {
		this._path = null;
		this._scenes = null;
		this._defaultScene = null;
		return true;
	};
	
	var initWithPath = function(path) {
		if (!this.init()) {
			return false;
		}
		
		var pos = path.lastIndexOf('/');
		if (pos >= 0) {
			this._path = path.substring(0, pos);
		}
		
		// parse it
		var parser = sf.NodeFileParser.create(path);
		var dict = parser ? parser.node() : null;
		if (!dict) {
			cn.error(path);
			return false;
		}
		
		// default scene name
		this._defaultScene = dict['DefaultScene'];
		if (!this._defaultScene) {
			this._defaultScene = 'default';
		}
		cn.log('DefaultScene: ' + this._defaultScene);
		
		// scene dictionary
		this._scenes = dict['Scenes'];
		if (!this._scenes || this._scenes.length < 1) {
			cn.error(dict);
			return false;
		}
		
		// check default scene
		var contains = false;
		var key;
		for (key in this._scenes) {
			if (key === this._defaultScene) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			this._defaultScene = key;
		}
		cn.log('default scene = ' + this._defaultScene);
		
		return true;
	};
	
	var scene = function(name) {
		name = name || this._defaultScene;
		cn.log('scene name = ' + name);
		
		// get scene filename
		var filename = this._scenes[name];
		if (!filename) {
			cn.error(name);
			return null;
		}
		
		// load scene data by filename
		filename = this._path + '/' + filename;
		cn.log('loading scene from file: ' + filename);
		
		var parser = sf.NodeFileParser.create(filename);
		var dict = parser ? parser.node() : null;
		if (!dict) {
			cn.error('failed to load scene data from file: ' + filename);
			return false;
		}
		
		return sf.Scene.create(dict);
	};
	
	var performScene = function(data) {
		var scene;
		
		if (typeof data === 'string') {
			scene = this.scene(data);
		} else if (typeof data === 'object') {
			scene = data['Scene'];
			if (!scene) {
				scene = this.scene();
			} else if (typeof scene === 'string') {
				scene = this.scene(scene);
			}
			if (scene instanceof cc.Scene) {
				// transit the scene
				data['Scene'] = scene;
				scene = sf.TransitionScene.scene(data);
			} else {
				cn.error(data, scene);
				return false;
			}
		} else {
			scene = this.scene();
		}
		
		if (scene instanceof cc.Scene) {
			cn.Scene.perform(scene);
			return true;
		} else {
			cn.error('failed to create scene');
			return false;
		}
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Forest,
		
		init: init,
		initWithPath: initWithPath,
		
		scene: scene,
		performScene: performScene,
		
		// properties
		_path: null,
		_scenes: null,
		_defaultScene: null,
	};
	
	// extends
	sf.Forest = cc.Class.extend(prop);
	
	// static
	sf.Forest.create = create;
	
}(SpriteForest);
