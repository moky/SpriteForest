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
//  CNRuntimeClass.js
//  Coconut2D-HTML5
//
//  Created by moKy on Feb. 28, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	var classNameFromString = function(string) {
		var start = string.indexOf('include class=');
		if (start >= 0) {
			start += 15;
			var stop = string.indexOf('"', start);
			if (stop < 0) {
				stop = string.indexOf('\'', start);
			}
			string = stop > 0 ? string.substring(start, stop) : string.substring(start);
		}
		return string.replace(/\s/g, '');
	};
	
	var classWithNameSpace = function(ns, path) {
		if (!ns) return null;
		var pos = path.indexOf('.');
		return pos < 0 ? ns[path] :
			classWithNameSpace(ns[path.substring(0, pos)],
							   path.substring(pos + 1));
	};
	
	var classFromString = function(string) {
		
		string = classNameFromString(string);
		var clazz;
		
		// direct class
		clazz = classWithNameSpace(window, string);
		if (clazz) {
			return clazz;
		}
		
		// class with namespace prefix
		if (string.length > 2) {
			var NS = string.substring(0, 2);
			if (cn.namespaces[NS]) {
				NS = cn.namespaces[NS]; // namespace map
			}
			
			clazz = classWithNameSpace(window[NS], string.substring(2));
			if (clazz) {
				return clazz;
			}
		}
		
		return null;
	};
	
	cn.classFromString = classFromString;
	
}(Coconut2D);
