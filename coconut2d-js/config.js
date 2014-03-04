
var Coconut2D = Coconut2D || {};

!function(cn) {
	'use strict';
	
	cn.config = {
		dir: '/~Moky/GitHub/SpriteForest/coconut2d-js/',
		files: [
			'coconut2d.js',
			// platform
			'platform/CNRuntimeClass.js',
			// base
			'base/CNNode.js',
			'base/CNTouchObject.js',
			'base/CNScene.js',
			'base/CNLayer.js',
			'base/CNSprite.js',
			// controllers
			'controller/CNTouchController.js',
			// extensions
			'extension/CNSpriteFrameCache.js',
		],
		getFiles: function() {
			var array = [];
			var dir = this.dir;
			var files = this.files;
			files.forEach(function(e, i) {
				array.push(dir + e);
			});
			return array;
		}
	};
	
} (Coconut2D);
