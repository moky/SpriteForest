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
//  SFNodeFileParser.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 1, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	var NodeFileParser = function() {
		this._path = '';
		this._root = null;
	};
	
	//
	//  static functions
	//
	var create = function(path) {
		var parser = new sf.NodeFileParser();
		if (parser.initWithFile(path)) {
			return parser;
		}
		return null;
	};
	
	//
	//  instance functions
	//
	var init = function() {
		this._path = '';
		this._root = null;
		return true;
	};
	var initWithFile = function(path) {
		if (!this.init()) {
			return false;
		}
		cn.log('parsing file: ' + path);
		this.parse(path);
		return true;
	};
	
	var node = function() {
		return this._root ? this._root['SFNode'] : null;
	};
	
	var _attributesFromString = function(string) {
		var lowercase = string.toLowerCase();
		var pos = lowercase.indexOf('attributes=');
		if (pos >= 0) {
			string = string.substring(pos + 12);
			pos = string.indexOf('"');
			if (pos < 0) {
				pos = string.indexOf('\'');
			}
			if (pos >= 0) {
				string = string.substring(0, pos);
			}
		}
		string = string.trim();
		cn.log('attributes: ' + string);
		
		var out = {};
		
		var array = string.split(';');
		var key, value;
		for (var i = 0; i < array.length; ++i) {
			var pair = array[i];
			pos = pair.indexOf(':');
			if (pos < 0) {
				continue;
			}
			// key
			key = pair.substring(0, pos);
			key = key.trim();
			if (!key) {
				cn.error('invalid key');
				continue;
			}
			// value
			value = pair.substring(pos + 1);
			value = value.trim().replace(/[(^")(^')('$)("$)]/g, '');
			value = decodeURIComponent(value);
			
			out[key] = value;
		}
	};
	
	var traverse = function(obj) {
		var path = this._path ? this._path + '/' : '';
		
		if (!obj) {
			
		} else if (typeof obj === 'string') {
			// string node
			var string = obj.trim();
			var lowercase = string.toLowerCase();
			
			// include file
			var pos = lowercase.indexOf('include file=');
			if (pos >= 0) {
				// get filename
				var filename = string.substring(pos + 14);
				pos = filename.indexOf('"');
				if (pos < 0) {
					pos = filename.indexOf('\'');
				}
				if (pos >= 0) {
					filename = filename.substring(0, pos);
					filename = path + filename.trim();
					cn.log('filename = ' + filename);
					// load 'SFNode' from file
					var parser = sf.NodeFileParser.create(filename);
					obj = parser ? parser.node() : null;
					if (obj && typeof obj === 'object') {
						// reset attributes
						var attributes = _attributesFromString(string);
						// merge attributes into obj
						//...
						return obj;
					}
					return obj;
				}
			}
			return string; // trimed string
		} else if (obj instanceof Array) {
			// array node
			var array = [];
			for (var i = 0; i < obj.length; ++i) {
				array.push(traverse.call(this, obj[i]));
			}
			return array;
		} else if (typeof obj === 'object') {
			// dictionary node
			var dict = {};
			for (var key in obj) {
				if (key === 'File') {
					var filename = obj[key];
					var pos = filename.indexOf('://');
					if (pos < 0) {
						// not a URL, prefix current directory to the filename
						filename = path + filename;
						// simplify path
						//...
					}
					
					dict[key] = filename;
				} else {
					dict[key] = traverse.call(this, obj[key]);
				}
			}
			return dict;
		}
		
		return obj; // other type object
	};
	
	var parse = function(path) {
        var fileUtils = cc.FileUtils.getInstance();
		var dict = fileUtils.createDictionaryWithContentsOfFile(path);
		if (!dict) {
			cn.log('failed to load data from file: ' + path);
			return;
		}
		cn.log('traversing SFNode file: ' + path);
		
		// relative dir
		var pos = path.lastIndexOf('/');
		this._path = pos < 0 ? '' : path.substring(0, pos);
		
		// travers all nodes
		var obj = traverse.call(this, dict);
		if (!obj || !obj['SFNode']) {
			cn.error(obj);
			return;
		}
		
		cn.log('finish parsing SFNode file: ' + path);
		this._root = obj;
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: NodeFileParser,
		
		init: init,
		initWithFile: initWithFile,
		
		parse: parse,
		node: node,
		
		// properties
		_path: null,
		_root: null,
	};
	
	// extends
	sf.NodeFileParser = cc.Class.extend(prop);
	
	// static
	sf.NodeFileParser.create = create;
	
}(SpriteForest);
