;
/*!
 *
 *  Coconut-2D JavaScript Library v1.0.0
 *  http://github.com/moky/SpriteForest/coconut2d-js/
 *
 *  Copyright (c) 2014 moKy at slanissue.com
 *  Released under the MIT license
 *  http://en.wikipedia.org/wiki/MIT_License
 *
 */
//
//  CNSprite.js
//  Coconut2D-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	//
	//  construtor
	//
	function Sprite() {
		cc.Sprite.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	function create() {
		var node = new cn.Sprite();
		if (arguments.length === 0) {
			node.init();
		} else if (typeof arguments[0] === 'string') {
			node.initWithFile(arguments[0]);
		} else if (typeof arguments[0] === 'object') {
			node.initWithDictionary(arguments[0]);
		} else {
			cn.error(arguments);
		}
		return node;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!cc.Sprite.prototype.init.call(this)) {
			cn.error(this);
			return false;
		}
		
		return true;
	}
	function initWithFile(filename) {
		if (!this.init()) {
			return false;
		}
		this.replaceImageWithFile(filename);
		return true;
	}
	function initWithDictionary(dict) {
		if (!this.init()) {
			return false;
		}
		
		var filename = dict['File'];
		if (filename) {
			this.replaceImageWithFile(filename);
		}
		
		var opacity = dict['Opacity'];
		if (opacity !== undefined) {
			this.setOpacity(opacity);
		}
		
		return this.setAttributes(dict);
	}
	
	function createSprites(filenames) {
		var array = [];
		for (var i = 0; i < filenames.length; ++i) {
			var sprite = create(filenames[i]);
			sprite.getTexture().setAliasTexParameters();
			array.push(sprite);
		}
		return array;
	}
	
	function getImageWithFile(filename) {
		var image = new Image();
		image.src = filename;
		return image;
	}
	
	function getSpriteFrameWithFile(filename) {
		//
		//  try texture cache
		//
		var textureCache = cc.TextureCache.getInstance();
		
		var texture = textureCache.textureForKey(filename);
		if (texture) {
			var size = texture.getContentSize();
			var rect = cc.rect(0, 0, size.width, size.height);
			return cc.SpriteFrame.createWithTexture(texture, rect);
		}
		
		//
		//  try sprite frame cache
		//
		var frameCache = cc.SpriteFrameCache.getInstance();
		
		// try full path
		var frame = frameCache.getSpriteFrame(filename);
		if (frame) {
			return frame;
		}
		
		var pos = filename.lastIndexOf('/');
		if (pos >= 0) {
			// try file name
			frame = frameCache.getSpriteFrame(filename.substring(pos + 1));
			if (frame) {
				return frame;
			}
		}
		
		//
		//  try file
		//
		var fileUtils = cc.FileUtils.getInstance();
		
		// set not pop-up message box when load image failed
		var bNotify = fileUtils.isPopupNotify();
		fileUtils.setPopupNotify(false);
		
		texture = textureCache.addImage(filename);
		if (!texture) {
			var image = getImageWithFile(filename);
			if (image) {
				texture = textureCache.addUIImage(image, filename);
			}
		}
		
		// reset the value of UIImage notify
		fileUtils.setPopupNotify(bNotify);
		
		// got it
		if (texture) {
			var size = texture.getContentSize();
			var rect = cc.rect(0, 0, size.width, size.height);
			return cc.SpriteFrame.createWithTexture(texture, rect);
		}
		
		return null;
	}
	
	function replaceImageWithFile(filename) {
		var spriteFrame = getSpriteFrameWithFile(filename);
		
		if (!spriteFrame) {
			cn.error('failed to load sprite texture: ' + filename);
		} else {
			var texture = spriteFrame.getTexture();
			var rect = spriteFrame.getRect();
			var rotated = spriteFrame.isRotated();
			this.initWithTexture(texture, rect, rotated);
		}
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Sprite,
		
		init: init,
		initWithFile: initWithFile,
		initWithDictionary: initWithDictionary,
		
		replaceImageWithFile: replaceImageWithFile,
		
		// properties
	};
	
	// extends
	cn.Sprite = cc.Sprite.extend(prop);
	
	// static
	cn.Sprite.create = create;
	cn.Sprite.createSprites = createSprites;
	cn.Sprite.getImageWithFile = getImageWithFile;
	cn.Sprite.getSpriteFrameWithFile = getSpriteFrameWithFile;
	
	// CNNode Extensions
	cn.Node.extensions(cn.Sprite);
	
}(Coconut2D);
