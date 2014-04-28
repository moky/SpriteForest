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
//  SFSprite.js
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
	var Sprite = function() {
		cn.Sprite.prototype.ctor.call(this);
		this._textures = null;
		this._eventDelegate = null;
	};
	
	//
	//  static functions
	//
	var create = function() {
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
				// extend touch sprite
				var touchEnabled = dict['TouchEnabled'];
				if (touchEnabled) {
					dict['Class'] = 'SFTouchSprite';
					break;
				}
				// extend drag sprite
				var dragEnabled = dict['DragEnabled'];
				if (dragEnabled) {
					dict['Class'] = 'SFDragSprite';
					break;
				}
				// extend text sprite
				var text = dict['Text'];
				if (text) {
					dict['Class'] = 'SFTextSprite';
					break;
				}
				
				dict['Class'] = 'SFSprite';
				break;
			}
			return sf.Node.create(dict);
		} else {
			cn.error(arguments);
		}
		return null;
	};
	
	//
	//  instance functions
	//
	var init = function() {
		if (!cn.Sprite.prototype.init.call(this)) {
			return false;
		}
		this._textures = null;
		this._eventDelegate = null;
		return true;
	};
	var initWithDictionary = function(dict) {
		if (!cn.Sprite.prototype.initWithDictionary.call(this, dict)) {
			cn.error(dict);
			return false;
		}
		var eventTree = dict['EventTree'];
		var actionTree = dict['ActionTree'];
		this.appointHandler(eventTree, actionTree);
		
		// load textures
		//     WARNING: For simplify reason, I hope you should never use it!
		var textures = dict['Textures'];
		this.setTextures(sf.Scene.loadTextures(textures));
		
		// add sub layers
		//     WARNING: For simplify reason, I hope you should never use it!
		var layers = dict['Layers'];
		this.addLayers(layers);
		
		// add sub sprites
		var sprites = dict['Sprites'];
		this.addSprites(sprites);
		
		return true;
	};
	
	var getTextures = function() {
		return this._textures;
	};
	var setTextures = function(textures) {
		if (this._textures != textures) {
			sf.Scene.cleanTextures(this._textures);
			this._textures = textures;
		}
	};
	
	var getEventDelegate = function() {
		return this._eventDelegate;
	};
	var setEventDelegate = function(delegate) {
		this._eventDelegate = delegate;
	};
	
	var appointHandler = function(eventTree, actionTree) {
		var handler = sf.EventHandler.create(eventTree, actionTree);
		this._eventDelegate = handler;
	};
	
	var onEnter = function() {
		cn.Sprite.prototype.onEnter.call(this);
		
		if (this._eventDelegate) {
			this._eventDelegate.doEvent('onEnter', this);
		}
	};
	var onEnterTransitionDidFinish = function() {
		cn.Sprite.prototype.onEnterTransitionDidFinish.call(this);
		
		if (this._eventDelegate) {
			this._eventDelegate.doEvent('onEnterTransitionDidFinish', this);
		}
	};
	var onExitTransitionDidStart = function() {
		if (this._eventDelegate) {
			this._eventDelegate.doEvent('onExitTransitionDidStart', this);
		}
		
		cn.Sprite.prototype.onExitTransitionDidStart.call(this);
	};
	var onExit = function() {
		if (this._eventDelegate) {
			this._eventDelegate.doEvent('onExit', this);
		}
		
		if (this._eventDelegate instanceof sf.EventHandler) {
			this._eventDelegate.restore(); // for restore 'Target' from CCNode to CCString
		}
		
		cn.Sprite.prototype.onExit.call(this);
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Sprite,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		getTextures: getTextures,
		setTextures: setTextures,
		
		getEventDelegate: getEventDelegate,
		setEventDelegate: setEventDelegate,
		
		appointHandler: appointHandler,
		
		onEnter: onEnter,
		onEnterTransitionDidFinish: onEnterTransitionDidFinish,
		onExitTransitionDidStart: onExitTransitionDidStart,
		onExit: onExit,
		
		// properties
		_textures: null,
		_eventDelegate: null,
	};
	
	// extends
	sf.Sprite = cn.Sprite.extend(prop);
	
	// static
	sf.Sprite.create = create;
	
	// SFNode Extensions
	sf.Node.extensions(sf.Sprite);
	
}(SpriteForest);
