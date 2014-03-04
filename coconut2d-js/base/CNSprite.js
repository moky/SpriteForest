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
	
	function replaceImageWithFile(filename) {
		
		var textureCache = cc.TextureCache.getInstance();
		var frameCache = cc.SpriteFrameCache.getInstance();
		
		var texture;
		var rect = cc.RectZero();
		var rotated = false;
		
		// get from texture cache
		texture = textureCache.textureForKey(filename);
		
		// get from frame cache
		if (!texture) {
			var pos = filename.lastIndexOf('/');
			var name = pos < 0 ? filename : filename.substring(pos + 1);
			
			var spriteFrame = frameCache.getSpriteFrame(name);
			if (spriteFrame) {
				texture = spriteFrame.getTexture();
				rect = spriteFrame.getRect();
				rotated = spriteFrame.isRotated();
			}
		}
		
		// get from file
		if (!texture) {
			// set not pop-up message box when load image failed
			var fileUtils = cc.FileUtils.getInstance();
			var bNotify = fileUtils.isPopupNotify();
			fileUtils.setPopupNotify(false);
			
			texture = textureCache.addImage(filename);
			if (!texture) {
				var image = this.getImageWithFile(filename);
				if (image) {
					texture = textureCache.addUIImage(image, filename);
				}
			}
			
			// reset the value of UIImage notify
			fileUtils.setPopupNotify(bNotify);
		}
		
		if (!texture) {
			cn.error('failed to load texture: ' + filename);
		} else {
			if (cc.rectEqualToRect(rect, cc.RectZero())) {
				var size = texture.getContentSize();
				rect.setWidth(size.width);
				rect.setHeight(size.height);
			}
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
	
	// CNNode Extensions
	cn.Node.extensions(cn.Sprite);
	
}(Coconut2D);
