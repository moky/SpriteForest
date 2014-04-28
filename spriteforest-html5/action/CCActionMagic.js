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
//  CCActionMagic.js
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
	var ActionMagic = function() {
		cc.ActionInstant.prototype.ctor.call(this);
		this._dict = null;
	};
	
	//
	//  static functions
	//
	var create = function() {
		var action = new this();
		var flag = false;
		if (arguments.length < 1) {
			flag = action.init();
		} else {
			flag = action.initWithDictionary(arguments[0]);
		}
		return flag ? action : null;
	};
	
	//
	//  instance functions
	//
	var init = function() {
		this._dict = null;
		return true;
	};
	var initWithDictionary = function(dict) {
		if (!this.init()) {
			return false;
		}
		this._dict = dict;
		return true;
	};
	
	var clone = function() {
		var action = new cc.ActionMagic();
		action.initWithDictionary(this._dict);
		return action;
	};
	
	var getTarget = function() {
		var target = this._dict['Target'];
		if (!target) {
			target = this._dict['ss_Target'];
		}
		if (!target) {
			return this._target;
		} else if (typeof target === 'string') {
			return sf.Node.getTarget(target, this._target);
		} else if (target instanceof cc.Node) {
			return target;
		}
		cn.error('could not happen');
		return null;
	};
	
	var startWithTarget = function(target) {
		cc.ActionInstant.prototype.startWithTarget.call(this, target);
		this.execute();
	};
	
	var execute = function() {
		var name = this._dict['Name'];
		if (!name) {
			cn.error('cannot find action name');
			return;
		}
		
		var target = this.getTarget();
		if (target instanceof sf.Sprite) {
		} else {
			cn.log('cannot execute this action on a non-sfsprite');
			return;
		}
		
		var worker = target.getEventDelegate();
		if (worker.doEvent(name, target)) {
			
		} else if (worker.doAction(name, target)) {
			
		} else {
			cn.log('no such action: ' + name);
		}
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: ActionMagic,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		clone: clone,
		
		getTarget: getTarget,
		
		startWithTarget: startWithTarget,
		execute: execute,
		
		// properties
		_dict: null,
	};
	
	// extends
	cc.ActionMagic = cc.ActionInstant.extend(prop);
	
	// static
	cc.ActionMagic.create = create;
	
}(SpriteForest);

//==========================================================================

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	var MagicBuilder = function(name, execute) {
		
		var prop = {
			ctor: cc.ActionMagic.prototype.ctor,
			execute: execute,
		};
		
		var ccClass = cc.ActionMagic.extend(prop);
		ccClass.create = cc.ActionMagic.create;
		
		cc['Action' + name] = ccClass;
		return ccClass;
	};
	
	// Audio
	var executeAudio = function() {
		if (!sf.Audio.perform(this._dict)) {
			cn.error(this._dict);
		}
	};
	MagicBuilder('Audio', executeAudio);
	
	// Video
	
	// Particle
	
	// Web
	
	// Alert
	
	// AddChild
	
	// RemoveFromParent
	
	// StopAllActions
	
}(SpriteForest);
