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
//  SFScene.js
//  SpriteForest-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	var Scene = function() {
		cn.Scene.prototype.ctor.call(this);
	};
	
	//
	//  static functions
	//
	var create = function(dict) {
		if (arguments.length === 0 || !arguments[0]) {
			var node = new this();
			node.init();
			return node;
		} else if (typeof arguments[0] === 'string') {
			return sf.Node.create(arguments[0]);
		} else if (typeof arguments[0] === 'object') {
			var dict = arguments[0];
			var className = dict['Class'];
			while (!className) {
				dict['Class'] = 'SFScene';
				break;
			}
			return sf.Node.create(dict);
		} else {
			cn.error(arguments);
		}
		return null;
	};
	
	var addSpriteFramesWithFile = function(filename) {
		return cn.SpriteFrameCache.loadTextureAndSprites(filename);
	};
	
	var loadTextures = function(textures) {
		if (!textures || textures.length === 0) {
			return null;
		}
		var array = [];
		for (var i = 0; i < textures.length; ++i) {
			var filename = textures[i];
			if (typeof filename === 'object') {
				filename = filename['File'];
			}
			if (!filename) {
				cn.error(textures[i]);
				continue;
			}
			cn.log('texture filename = ' + filename);
			
			var texture = addSpriteFramesWithFile(filename);
			if (texture) {
				array.push(texture);
			} else {
				cn.log('failed to load texture: ' + filename);
			}
		}
		return array;
	};
	
	var cleanTextures = function(textures) {
		var frameCache = cc.SpriteFrameCache.getInstance();
		var textureCache = cc.TextureCache.getInstance();
		for (var i = textures.length - 1; i >= 0; --i) {
			var texture = textures[i];
			frameCache.removeSpriteFramesFromTexture(texture);
			TextureCache.removeTexture(texture);
		}
	};
	
	//
	//  instance functions
	//
	var initWithDictionary = function(dict) {
		if (!cn.Scene.prototype.init.call(this, dict)) {
			cn.error(this);
			return false;
		}
		
		// load textures
		var textures = dict['Textures'];
		loadTextures(textures);
		
		// add sub layers
		var layers = dict['Layers'];
		if (layers) {
			// scale top-level layers for N-Screen support
			for (var i = 0; i < layers.length; ++i) {
				var nodeDict = layers[i];
				if (nodeDict) {
					var scale = nodeDict['Scale'];
					var scaleX = nodeDict['ScaleX'];
					var scaleY = nodeDict['ScaleY'];
					if (scale === undefined && scaleX === undefined && scaleY === undefined) {
						nodeDict['Scale'] = 'ToFill';
					}
				}
			}
			this.addLayers(layers);
		}
		
		// add sub sprites
		//     WARNING: For simplify reason, I hope you should never use it!
		var sprites = dict['Sprites'];
		if (sprites) {
			this.addSprites(sprites);
		}
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Scene,
		
		initWithDictionary: initWithDictionary,
		
		// properties
	};
	
	// extends
	sf.Scene = cn.Scene.extend(prop);
	
	// static
	sf.Scene.create = create;
	
	sf.Scene.loadTextures = loadTextures;
	sf.Scene.cleanTextures = cleanTextures;
	
	// SFNode Extensions
	sf.Node.extensions(sf.Scene);
	
}(SpriteForest);
