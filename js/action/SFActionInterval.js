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
//  SFActionInterval.js
//  SpriteForest-HTML5
//
//  Created by moKy on Mar. 4, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	
	var prop = {
		ctor: sf.FiniteTimeAction.prototype.ctor,
		
		// properties
	};
	
	// extends
	sf.ActionInterval = sf.FiniteTimeAction.extend(prop);
	
}(SpriteForest);

//===================================================================== Sequence

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function Sequence() {
		sf.ActionInterval.prototype.ctor.call(this);
		this._actions = null;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._actions = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary(dict)) {
			return false;
		}
		var actions = sf.Action.subActionsFromDictionary(dict);
		if (!actions) {
			cn.error(dict);
			return false;
		}
		// remove invalid actions
		for (var i = actions.length - 1; i >= 0; --i) {
			if (actions[i] instanceof cc.FiniteTimeAction) {
			} else {
				actions.splice(i, 1);
			}
		}
		
		if (actions.length < 1) {
			cn.error(dict);
			return false;
		}
		
		this._actions = actions;
		return true;
	}
	
	function ccAction() {
		if (!this._actions) {
			cn.error(this._actions);
			return null;
		}
		return cc.Sequence.create(this._actions);
	}
	
	var prop = {
		ctor: Sequence,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_actions: null,
	};
	
	// extends
	sf.Sequence = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//======================================================================= Repeat

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function Repeat() {
		sf.ActionInterval.prototype.ctor.call(this);
		this._action = null;
		this._times = 0;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._action = null;
		this._times = 0;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var action = sf.Action.subActionFromDictionary(dict);
		if (action instanceof cc.FiniteTimeAction) {
			this._action = action;
		}
		this._times = dict['Times'];
		return true;
	}
	
	function ccAction() {
		if (!this._action || !this._times) {
			cn.error(this._action, this._times);
			return null;
		}
		return cc.Repeat.create(this._action, this._times);
	}
	
	var prop = {
		ctor: Repeat,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_action: null,
		_times: 0,
	};
	
	// extends
	sf.Repeat = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//======================================================================== Spawn

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function Spawn() {
		sf.ActionInterval.prototype.ctor.call(this);
		this._actions = null;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._actions = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var actions = sf.Action.subActionsFromDictionary(dict);
		if (!actions) {
			cn.error(dict);
			return false;
		}
		// remove invalid actions
		for (var i = actions.length - 1; i >= 0; --i) {
			if (actions[i] instanceof cc.FiniteTimeAction) {
			} else {
				actions.splice(i, 1);
			}
		}
		
		if (actions.length < 1) {
			cn.error(dict);
			return false;
		}
		
		this._actions = actions;
		return true;
	}
	
	function ccAction() {
		if (!this._actions) {
			cn.error(this._actions);
			return null;
		}
		return cc.Spawn.create(this._actions);
	}
	
	var prop = {
		ctor: Spawn,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_actions: null,
	};
	
	// extends
	sf.Spawn = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//==================================================================== DelayTime

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function ccAction() {
		return cc.DelayTime.create(this._action);
	}
	
	var prop = {
		ctor: sf.ActionInterval.prototype.ctor,
		
		ccAction: ccAction,
		
		// properties
	};
	
	// extends
	sf.DelayTime = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//================================================================== ReverseTime

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function ReverseTime() {
		sf.ActionInterval.prototype.ctor.call(this);
		this._action = null;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._action = null;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		var action = sf.Action.subActionFromDictionary(dict);
		if (action instanceof cc.FiniteTimeAction) {
			this._action = action;
			return true;
		}
		
		cn.error(dict);
		return false;
	}
	
	function ccAction() {
		if (!this._action) {
			cn.error(this._action);
			return null;
		}
		return cc.ReverseTime.create(this._action);
	}
	
	var prop = {
		ctor: ReverseTime,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_action: null,
	};
	
	// extends
	sf.ReverseTime = sf.ActionInterval.extend(prop);
	
}(SpriteForest);

//====================================================================== Animate

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	function Animate() {
		sf.ActionInterval.prototype.ctor.call(this);
		this._frames = null;
		this._delay = 0;
		this._loops = 1;
		this._restoreOriginalFrame = false;
	}
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	function init() {
		if (!sf.ActionInterval.prototype.init.call(this)) {
			return false;
		}
		this._frames = null;
		this._delay = 0;
		this._loops = 1;
		this._restoreOriginalFrame = false;
		return true;
	}
	function initWithDictionary(dict) {
		if (!sf.ActionInterval.prototype.initWithDictionary.call(this, dict)) {
			return false;
		}
		
		var frames = dict['Frames'];
		this._frames = frames ? frames : [];
		
		var delay = dict['Delay'];
		this._delay = delay;
		
		var loops = dict['Loops'];
		this._loops = loops !== undefined ? loops : 1;
		
		var restoreOriginalFrame = dict['RestoreOriginalFrame'];
		this._restoreOriginalFrame = restoreOriginalFrame;
		
		return true;
	}
	
	function createAnimation(frames, delayTime) {
		
		var spriteFrames = [];
		var frame, file;
		for (var i = 0; i < frames.length; ++i) {
			file = frames[i];
			if (!file) {
				continue;
			} else if (typeof file === 'string') {
				// frame name
			} else {
				// file name
				file = file['File'];
			}
			if (!file) {
				continue;
			}
			
			frame = cn.Sprite.getSpriteFrameWithFile(file);
			if (frame) {
				spriteFrames.push(frame);
			} else {
				cn.error(file, frame, frames[i]);
			}
		}
		
		return cc.Animation.create(spriteFrames, delayTime);
	}
	
	function ccAction() {
		var frames = this._frames;
		if (!frames || frames.length < 1) {
			cn.error(this._frames);
			return null;
		}
		var delayTime = this._duration ? this._duration / frames.length : this._delay;
		var animation = createAnimation(frames, delayTime);
		if (!animation) {
			cn.error(frames, delayTime, this._loops);
			return null;
		}
		animation.setLoops(this._loops);
		animation.setRestoreOriginalFrame(this._restoreOriginalFrame);
		return cc.Animate.create(animation);
	}
	
	var prop = {
		ctor: Animate,
		
		init: init,
		initWithDictionary: initWithDictionary,
		
		ccAction: ccAction,
		
		// properties
		_frames: null,
		_delay: null,
		_loops: null,
		_restoreOriginalFrame: null,
	};
	
	// extends
	sf.Animate = sf.ActionInterval.extend(prop);
	
}(SpriteForest);
