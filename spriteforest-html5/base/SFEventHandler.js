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
//  SFEventHandler.js
//  SpriteForest-HTML5
//
//  Created by moKy on Feb. 28, 2014.
//

!function(sf) {
	'use strict';
	var cc = sf.cc;
	var cn = sf.cn;
	
	//
	//  constructor
	//
	var EventHandler = function() {
		this._eventTree = null;
		this._actionTree = null;
	};
	
	//
	//  static functions
	//
	var create = function(eventTree, actionTree) {
		var handler = new sf.EventHandler();
		handler.init(eventTree, actionTree);
		return handler;
	};
	
	//
	//  instance functions
	//
	var init = function(eventTree, actionTree) {
		this._eventTree = eventTree;
		this._actionTree = actionTree;
		
		this.snapshot(); // for restore 'Target'
		
		return true;
	};
	
	var getTarget = function(dict, node) {
		var target = dict['Target'];
		if (!target) {
			target = dict['ss_Target'];
		}
		if (!target) {
			return node;
		}
		
		if (typeof target === 'string') {
			return sf.Node.getTarget(target, node);
		}
		return target;
	};
	
	var runAction = function(dict, node) {
		dict['Target'] = node;
		// create action
		var action = sf.Action.create(dict);
		if (!action) {
			//cn.error(dict);
			return false;
		}
		var ccAction = action.ccAction();
		if (ccAction instanceof cc.Action) {
			// run action
			node.runAction(ccAction);
			return true;
		}
		cn.error(action);
		return false;
	};
	
	var doEvent = function(eventName, node) {
		if (!this._eventTree || !node) {
			//cn.log(eventName);
			return false;
		}
		if (!this._eventTree) {
			return false;
		}
		
		var tasks = this._eventTree[eventName];
		if (!tasks) {
			return false;
		}
		
		var flag = false;
		
		for (var i = 0; i < tasks.length; ++i) {
			var task = tasks[i];
			var target = getTarget(task, node);
			var worker = this;
			
			if (target instanceof sf.Sprite) {
				worker = target.getEventDelegate();
			}
			
			var name = task['Name'];
			if (!worker) {
				cn.error('could not happen!');
			} else if (worker.doEvent(name, target)) {
				flag = true;
			} else if (worker.doAction(name, target)) {
				// combined action
				flag = true;
			} else {
				// cc action
				flag = runAction(task, target);
			}
		}
		
		return flag;
	};
	
	var doAction = function(actionName, node) {
		if (!this._eventTree || !node) {
			//cn.log(eventName);
			return false;
		}
		if (!this._actionTree) {
			return false;
		}
		
		var dict = this._actionTree[actionName];
		if (!dict) {
			return false;
		}
		
		var target = getTarget(dict, node);
		return runAction(dict, target);
	};
	
	var snapshotArray = function(array) {
		if (array)
		for (var i = array.length - 1; i >= 0; --i) {
			snapshotDictionary(array[i]);
		}
	};
	var restoreArray = function(array) {
		if (array)
		for (var i = array.length - 1; i >= 0; --i) {
			restoreDictionary(array[i]);
		}
	};
	var snapshotDictionary = function(dict) {
		if (dict)
		for (var key in dict) {
			var obj = dict[key];
			if (key === 'Target' && typeof obj === 'string') {
				dict['ss_Target'] = obj; // snapshot
			} else if (obj instanceof Array) {
				snapshotArray(obj);
			} else if (typeof obj === 'object') {
				snapshotDictionary(obj);
			}
		}
	};
	var restoreDictionary = function(dict) {
		if (dict)
		for (var key in dict) {
			var obj = dict[key];
			if (key === 'Target' && typeof obj !== 'string') {
				obj = dict['ss_Target'];
				if (obj) {
					dict['Target']; // restore
					dict['ss_Target'] = null;
				} else {
					dict['Target'] = null;
				}
			} else if (obj instanceof cc.Class) {
				// do nothing
			} else if (obj instanceof Array) {
				restoreArray(obj);
			} else if (typeof obj === 'object') {
				restoreDictionary(obj);
			}
		}
	};
	
	var restore = function() {
		restoreDictionary(this._eventTree);
		restoreDictionary(this._actionTree);
	};
	
	var snapshot = function() {
		snapshotDictionary(this._eventTree);
		snapshotDictionary(this._actionTree);
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: EventHandler,
		
		init: init,
		
		doEvent: doEvent,
		doAction: doAction,
		
		restore: restore,
		snapshot: snapshot,
		
		// properties
		_eventTree: null,
		_actionTree: null,
	};
	
	// extends
	sf.EventHandler = cc.Class.extend(prop);
	
	// static
	sf.EventHandler.create = create;
	
}(SpriteForest);
