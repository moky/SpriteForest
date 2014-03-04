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
//  coconut2d.js
//  Coconut2D-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

var Cocos2D = cc || {};

var Coconut2D = Coconut2D || {};
// refer to cocos2d
Coconut2D.cc = Cocos2D;

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	cn.namespaces = {};
	// add namespaces
	cn.namespaces['CC'] = 'Cocos2D';
	cn.namespaces['CN'] = 'Coconut2D';
	
	cn.version = 'Coconut-2D v1.0.0';
	
	// utils
	cn.log = cc.log;
	cn.error = function(message) {
		if (!cc.IS_SHOW_DEBUG_ON_PAGE) {
			console.error.apply(console, arguments);
		} else {
			cc._logToWebPage(message);
		}
	}
	
	// isKindOfClass
	cc.Class.prototype.isKindOfClass = function(superClass) {
		return this instanceof superClass;
	}
	
} (Coconut2D);
