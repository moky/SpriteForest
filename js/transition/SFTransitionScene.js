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
//  SFTransitionScene.js
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
	function TransitionScene() {
		this._name = null;
		this._scene = null;
		this._duration = 0;
		this._orientation = 0;
		this._color = null;
		this._reverse = false;
	}
	
	//
	//  static functions
	//
	function create(dict) {
		var trans = new sf.TransitionScene();
		if (trans.initWithDictionary(dict)) {
			return trans;
		}
		return null;
	}
	
	//--------------------------------------------------------------------------
	var _names = [
	];
	
	_names[0] = [ // type: 0
		'Scene',
		'RotoZoom', 'JumpZoom',
		'MoveInL', 'MoveInR', 'MoveInT', 'MoveInB',
		'SlideInL', 'SlideInR', 'SlideInB', 'SlideInT',
		'ShrinkGrow',
		'CrossFade', 'TurnOffTiles',
		'SplitCols', 'SplitRows',
		'FadeTR', 'FadeBL', 'FadeUp', 'FadeDown',
		'Progress',
		'ProgressRadialCCW', 'ProgressRadialCW',
		'ProgressHorizontal', 'ProgressVertical',
		'ProgressInOut', 'ProgressOutIn',
	];
	
	_names[1] = [ // type: 1
		'SceneOriented',
		'FlipX', 'FlipY', 'FlipAngular',
		'ZoomFlipX', 'ZoomFlipY', 'ZoomFlipAngular',
	];
	
	_names[2] = [ // type: 2
		'Fade',
	];
	
	_names[3] = [ // type: 3
		'PageTurn',
	];
	
	function switchTrans(p, type) {
		if (type < 1 || type > 3) {
			type = 0;
		}
		
		if (type === 3 && typeof(gl.createFramebuffer) !== 'function') {
			// doesn't support 3d transition
			return null;
		}
		
		var array = _names[type];
		for (var i = 0; i < array.length; ++i) {
			var name = array[i];
			if (p.isNamed(name)) {
				var Class = cn.classFromString('CCTransition' + name);
				if (!Class) {
					cn.error(name);
					return null;
				}
				switch (type) {
					case 1 :
						return Class.create(p._duration, p._scene, p._orientation);
						break;
					case 2 :
						return Class.create(p._duration, p._scene, p._color);
						break;
					case 3 :
						return Class.create(p._duration, p._scene, p._reverse);
						break;
					default:
						return Class.create(p._duration, p._scene);
						break;
				}
			}
		}
		return null;
	}
	
	//--------------------------------------------------------------------------
	
	function scene(dict) {
		var transition = sf.TransitionScene.create(dict);
		if (!transition) {
			cn.error(dict);
			return null;
		}
		
		var out;
		
		for (var i = 0; i <= 3; ++i) {
			out = switchTrans(transition, i);
			if (out) {
				return out;
			}
		}
		
		cn.log('unrecognized transition name');
		return transition._scene;
	}
	
	//
	//  instance functions
	//
	function init() {
		this._name = null;
		this._scene = null;
		this._duration = 0;
		this._orientation = 0;
		this._color = cc.c3b(255, 255, 255);
		this._reverse = false;
		return true;
	}
	function initWithDictionary(dict) {
		if (!this.init()) {
			return false;
		}
		
		// transition name
		var name = dict['Transition'];
		if (name) {
			if (name.length > 10 && name.substring(0, 10) === 'Transition') {
				name = name.substring(10);
			}
			this._name = name;
		}
		
		// target scene
		var scene = dict['Scene'];
		if (!scene) {
			cn.error(dict);
			return false;
		}
		this._scene = scene;
		
		// other values
		
		// duration
		var duration = dict['Duration'];
		this._duration = duration;
		// orientation
		var orientation = dict['Orientation'];
		orientation = orientation ? orientation.toLowerCase() : null;
		if (!orientation) {
		} else if (orientation === 'leftover') {
			this._orientation = cc.TRANSITION_ORIENTATION_LEFT_OVER;
		} else if (orientation === 'rightover') {
			this._orientation = cc.TRANSITION_ORIENTATION_RIGHT_OVER;
		} else if (orientation === 'upover') {
			this._orientation = cc.TRANSITION_ORIENTATION_UP_OVER;
		} else if (orientation === 'downover') {
			this._orientation = cc.TRANSITION_ORIENTATION_DOWN_OVER;
		} else {
			cn.error('unknown orientation: ' + orientation);
		}
		// color
		var red = dict['Red'];
		var green = dict['Green'];
		var blue = dict['Blue'];
		if (red !== undefined && green !== undefined && blue !== undefined) {
			this._color = cc.c3b(red, green, blue);
		}
		// reverse
		var reverse = dict['Reverse'];
		this._reverse = reverse || false;
		
		return true;
	}
	
	function isNamed(name) {
		if (!name || !this._name) {
			return false;
		}
		return this._name === name;
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: TransitionScene,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		isNamed: isNamed,
		
		// properties
		_name: null,
		
		_scene: null,
		_duration: 0,
		_orientation: 0,
		_color: null,
		_reverse: false,
	};
	
	// extends
	sf.TransitionScene = cc.Class.extend(prop);
	
	// static
	sf.TransitionScene.create = create;
	sf.TransitionScene.scene = scene;
	
}(SpriteForest);
