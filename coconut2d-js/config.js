
var Coconut2D = Coconut2D || {};

!function(cn) {
	'use strict';
	
	cn.config = {
		root: '/~Moky/GitHub/SpriteForest/coconut2d-js/',
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
		getFiles: function(files, root) {
			var files = arguments.length > 0 ? files : this.files;
			var dir = arguments.length > 0 ? root : this.root;
			if (!dir || !files) {
				return files;
			} else if (dir.charAt(dir.length - 1) != '/') {
				dir += '/';
			}
			var array = [];
			var len = files.length;
			for (var i = 0; i < len; ++i) {
				array.push(dir + files[i]);
			}
			return array;
		}
	};
	
} (Coconut2D);
