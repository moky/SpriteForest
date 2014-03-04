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
//  SFLayer.js
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
	function Layer() {
		cn.Layer.prototype.ctor.call(this);
		this._textures = null;
	}
	
	//
	//  static functions
	//
	function create() {
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
				// extend scroll layer
				var scrollEnabled = dict['ScrollEnabled'];
				if (scrollEnabled) {
					dict['Class'] = 'SFScrollLayer';
					break;
				}
				// extend scale layer
				var scaleEnabled = dict['ScaleEnabled'];
				if (scaleEnabled) {
					dict['Class'] = 'SFScaleLayer';
					break;
				}
				
				dict['Class'] = 'SFLayer';
				break;
			}
			return sf.Node.create(dict);
		} else {
			cn.error(arguments);
		}
		return null;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!cn.Layer.prototype.init.call(this)) {
			cn.error(this);
			return false;
		}
		this._textures = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!cn.Layer.prototype.initWithDictionary.call(this, dict)) {
			cn.error(dict);
			return false;
		}
		
		// load textures
		//     WARNING: For simplify reason, I hope you should never use it!
		var textures = dict['Textures'];
		this.setTextures(sf.Scene.loadTextures(textures));
		
		// add sub layers
		//     WARNING: For simplify reason, I hope you should never use it!
		var layers = dict['Layers'];
		if (layers) {
			this.addLayers(layers);
		}
		
		// add sub sprites
		var sprites = dict['Sprites'];
		if (sprites) {
			this.addSprites(sprites);
		}
		
		return true;
	}
	
	function getTextures() {
		return this._textures;
	}
	function setTextures(textures) {
		if (this._textures != textures) {
			cn.log('cleaning textures');
			sf.Scene.cleanTextures(this._textures);
			
			this._textures = textures;
		}
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Layer,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		getTextures: getTextures,
		setTextures: setTextures,
		
		// properties
		_textures: null,
	};
	
	// extends
	sf.Layer = cn.Layer.extend(prop);
	
	// static
	sf.Layer.create = create;
	
	// SFNode Extensions
	sf.Node.extensions(sf.Layer);
	
}(SpriteForest);
