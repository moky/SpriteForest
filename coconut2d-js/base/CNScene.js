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
//  CNScene.js
//  Coconut2D-HTML5
//
//  Created by moKy on Feb. 26, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	//
	//  construtor
	//
	function Scene() {
		cc.Scene.prototype.ctor.call(this);
		this._touchNodes = null;
		this._allClaimedKeys = null;
	}
	
	//
	//  static functions
	//
	function create() {
		var node = new cn.Scene();
		node.init();
		return node;
	}
	
	//
	//  instance functions
	//
	function init() {
		if (!cc.Scene.prototype.init.call(this)) {
			cn.error(this);
			return false;
		}
		
		// clean up caches
		cc.SpriteFrameCache.getInstance().removeSpriteFrames(); // removeUnusedSpriteFrames
		//cc.TextureCache.getInstance().removeAllTextures(); // removeUnusedTextures
		
		this.setAnchorPoint(cc.PointZero());
		this._touchNodes = {};
		this._allClaimedKeys = [];
		
		return true;
	}
	
	function onEnter() {
		cc.Scene.prototype.onEnter.call(this);
		cc.registerStandardDelegate(this, -1);
	}
	
	function onExit() {
		cc.unregisterTouchDelegate(this);
		cc.Scene.prototype.onExit.call(this);
	}
	
	function perform(scene) {
		scene = scene || this;
		var director = cc.Director.getInstance();
		var old = director.getRunningScene();
		if (old) {
			// Clean the current scene before next created,
			// to avoid crash caused by sprite frame cache,
			// because CNScene will clean up all textures caches while creating
			old.cleanup();
			// Now create new scene for replacement.
			// NOTICE: here will call 'runningScene onExit' second time
			director.replaceScene(scene);
		} else {
			director.runWithScene(scene);
		}
	}
	
	// protected:
	function _object_key(node) {
		if (!node._unique_id_for_object) {
			node._unique_id_for_object = 'node-' + Math.random();
		}
		return node._unique_id_for_object;
	}
	
	function addClaimedKey(key) {
		this._allClaimedKeys.push(key);
	}
	function removeClaimedKey(key) {
		for (var i = this._allClaimedKeys.length - 1; i >= 0; --i) {
			if (this._allClaimedKeys[i] == key) {
				this._allClaimedKeys.splice(i, 1);
			}
		}
	}
	function isKeyClaimed(key) {
		for (var i = this._allClaimedKeys.length - 1; i >= 0; --i) {
			if (this._allClaimedKeys[i] == key) {
				return false; // ???
			}
		}
		return false;
	}
	
	// public: for touch dispatching
	function addTouchNode(node, delegate, maxTouches) {
		if (maxTouches === undefined || maxTouches === null) {
			maxTouches = -1;
		}
		for (var p = node; p; p = p.getParent()) {
			var key = _object_key(p);
			var obj = this._touchNodes[key];
			if (!obj) {
				obj = new cn.TouchObject();
				obj.init();
				this._touchNodes[key] = obj;
			}
			
			obj.count += 1;
			if (p === node && delegate) {
				obj.delegate = delegate;
				obj.maxTouches = maxTouches;
			}
		}
	}
	function removeTouchNode(node) {
		for (var p = node; p; p = p.getParent()) {
			var key = _object_key(node);
			var obj = this._touchNodes[key];
			if (obj) {
				obj.count -= 1;
				if (obj.count <= 0) {
					this._touchNodes[key] = null;
				}
			}
		}
	}
	
	// protected:
	function objectByNode(node) {
		var key = _object_key(node);
		return this._touchNodes[key];
	}
	
	function cnTouchObject(touch, event, touchType, touchObject) {
		var touchKey = _object_key(touch);
		var claimedTouches = touchObject.claimedTouches;
		
		if (touchType === cc.TOUCH_BEGAN) {
			for (var i = 0; i < claimedTouches.length; ++i) {
				touchKey = _object_key(claimedTouches[i]);
				this.removeClaimedKey(touchKey);
			}
			touchObject.removeAllClaimedTouches();
		}
		
		var claimed = false;
		// dispatch
		var delegate = touchObject.delegate;
		if (!delegate) {
			cn.error('could not happen');
		} else if (touchObject.isClaimedTouch(touch)) {
			claimed = true;
			if (touchType === cc.TOUCH_MOVED) {
				delegate.onTouchMoved(touch, event);
			} else if (touchType === cc.TOUCH_ENDED) {
				this.removeClaimedKey(touchKey);
				touchObject.removeClaimedTouch(touch);
				delegate.onTouchEnded(touch, event);
			} else if (touchType === cc.TOUCH_CANCELLED) {
				this.removeClaimedKey(touchKey);
				touchObject.removeClaimedTouch(touch);
				delegate.onTouchCancelled(touch, event);
			} else {
				cn.error('could not happen!');
			}
		} else if (this.isKeyClaimed(touchKey)) {
			// already claimed by other obj
		} else if (touchObject.maxTouches > 0 && claimedTouches.length >= touchObject.maxTouches) {
			cn.log('the touch node has already claimed ' + claimedTouches.length + ' touch(es).');
		} else if (touchType === cc.TOUCH_BEGAN || touchType === cc.TOUCH_MOVED) {
			claimed = delegate.onTouchBegan(touch, event);
			if (claimed) {
				claimedTouches.push(touch);
				this.addClaimedKey(touchKey);
			}
		}
		
		return claimed;
	}
	function cnTouchNode(touch, event, touchType, node) {
		var touchableCount = 0;
		var obj = this.objectByNode(node);
		if (obj) {
			touchableCount = obj.count;
		}
		if (touchableCount <= 0) {
			cn.error(touchableCount);
			return false;
		}
		var delegate = obj.delegate;
		
		var children = node.getChildren();
		if (!children) {
			children = [];
		}
		var pos = children.length - 1;
		
		var child, childObj;
		// check children which zOrder >= 0
		for (; pos >= 0 && (touchableCount > 1 || !delegate); --pos) {
			child = children[pos];
			if (child.getZOrder() < 0) {
				break;
			}
			
			childObj = this.objectByNode(child);
			if (!childObj) {
				// not a touchable node
				continue;
			}
			touchableCount -= childObj.count;
			
			if (this.cnTouchNode(touch, event, touchType, child)) {
				return true;
			}
		}
		
		if (touchableCount == 0) {
			return false;
		} else if (touchableCount < 0) {
			cn.error(touchableCount);
			return false;
		}
		
		// check self
		if (delegate) {
			touchableCount -= 1;
			if (this.cnTouchObject(touch, event, touchType, obj)) {
				return true;
			}
		}
		
		if (touchableCount == 0) {
			return false;
		} else if (touchableCount < 0) {
			cn.error(touchableCount);
			return false;
		}
		
		// check children which zOrder < 0
		for (; pos >= 0 && (touchableCount > 1 || !delegate); --pos) {
			child = children[pos];
			if (child.getZOrder() >= 0) {
				cn.error(child);
				break;
			}
			
			childObj = this.objectByNode(child);
			if (!childObj) {
				// not a touchable node
				continue;
			}
			touchableCount -= childObj.count;
			
			if (this.cnTouchNode(touch, event, touchType, child)) {
				return true;
			}
		}
		
		if (touchableCount != 0) {
			cn.error(touchableCount);
		}
		
		return false;
	}
	function cnTouches(touches, event, touchType) {
		var touch;
		for (var i = 0; i < touches.length; ++i) {
			touch = touches[i];
			if (!this.cnTouchNode(touch, event, touchType, this)) {
				cn.log('nothing hit.');
			}
		}
	}
	
	// public:
	function onTouchesBegan(touches, event) {
		this.cnTouches(touches, event, cc.TOUCH_BEGAN);
	}
	function onTouchesMoved(touches, event) {
		this.cnTouches(touches, event, cc.TOUCH_MOVED);
	}
	function onTouchesEnded(touches, event) {
		this.cnTouches(touches, event, cc.TOUCH_ENDED);
	}
	function onTouchesCancelled(touches, event) {
		this.cnTouches(touches, event, cc.TOUCH_CANCELLED);
	}
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Scene,
		
		init: init,
		
		onEnter: onEnter,
		onExit: onExit,
		
		perform: perform,
		
		addClaimedKey: addClaimedKey,
		removeClaimedKey: removeClaimedKey,
		isKeyClaimed: isKeyClaimed,
		
		addTouchNode: addTouchNode,
		removeTouchNode: removeTouchNode,
		
		objectByNode: objectByNode,
		cnTouchObject: cnTouchObject,
		cnTouchNode: cnTouchNode,
		cnTouches: cnTouches,
		
		onTouchesBegan: onTouchesBegan,
		onTouchesMoved: onTouchesMoved,
		onTouchesEnded: onTouchesEnded,
		onTouchesCancelled: onTouchesCancelled,
		
		// properties
		_touchNodes: {},
		_allClaimedKeys: [],
	};
	
	// extends
	cn.Scene = cc.Scene.extend(prop);
	
	// static
	cn.Scene.create = create;
	
	cn.Scene.perform = perform;
	
	// CNNode Extensions
	cn.Node.extensions(cn.Scene);
	
}(Coconut2D);
