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
//  CNSpriteFrameCache.js
//  Coconut2D-HTML5
//
//  Created by moKy on Mar. 2, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	//
	//  construtor
	//
	function SpriteFrameCache() {
		cc.SpriteFrameCache.prototype.ctor.call(this);
	}
	
	//
	//  static functions
	//
	
	function loadTextureAndSprites(filePath) {
		var frameCache = cc.SpriteFrameCache.getInstance();
		
        var fileUtils = cc.FileUtils.getInstance();
		var dict = fileUtils.createDictionaryWithContentsOfFile(filePath);
		
		var texturePath = "";
		var metadataDict = dict["metadata"] || dict["meta"];
		if (metadataDict) {
			// try to read texture file name from meta data
			texturePath = metadataDict["textureFileName"] || metadataDict["image"];
		} else {
			// build texture path by replacing file extension
			texturePath = filePath;
			// remove .xxx
			var startPos = texturePath.lastIndexOf(".", texturePath.length);
			texturePath = texturePath.substr(0, startPos);
			// append .png
			texturePath = texturePath + ".png";
		}
		
		if (texturePath != "") {
			// build texture path relative to plist file
			texturePath = fileUtils.fullPathFromRelativeFile(texturePath, filePath);
		}
		
		var textureCache = cc.TextureCache.getInstance();
		var texture = textureCache.addImage(texturePath);
		if (texture) {
			if (!cc.ArrayContainsObject(frameCache._loadedFileNames, filePath)) {
				frameCache._addSpriteFramesWithDictionary(dict, texture);
				frameCache._loadedFileNames.push(filePath);
			}
		}
		return texture;
	}
	
	//
	//  instance functions
	//
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: SpriteFrameCache,
		
		// properties
	};
	
	// extends
	cn.SpriteFrameCache = cc.SpriteFrameCache.extend(prop);
	
	cn.SpriteFrameCache.loadTextureAndSprites = loadTextureAndSprites;
	
}(Coconut2D);
