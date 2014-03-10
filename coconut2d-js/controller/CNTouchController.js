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
//  CNTouchController.js
//  Coconut2D-HTML5
//
//  Created by moKy on Mar. 1, 2014.
//

!function(cn) {
	'use strict';
	var cc = cn.cc;
	
	cn.TouchNodeNormal = 0;
	cn.TouchNodeActivie = 1;
	
	//
	//  construtor
	//
	var TouchController = function() {
		this._node = null;
		this._delegate = null;
		
		this._touchBeganPoint = cc.PointZero();
		this._touchPoint = cc.PointZero();
		this._touchEndedPoint = cc.PointZero();
		
		this._status = cn.TouchNodeNormal;
		
		this._dragEnabled = false;
		this._originalPosition = cc.PointZero();
	};
	
	//
	//  static functions
	//
	
	//
	//  instance functions
	//
	var init = function() {
		this._node = null;
		this._delegate = null;
		
		this._touchBeganPoint = null;
		this._touchPoint = null;
		this._touchEndedPoint = null;
		
		this._status = 0;
		
		this._dragEnabled = false;
		this._originalPosition = null;
		
		return true;
	};
	
	var getNode = function() {
		return this._node;
	};
	var setNode = function(node) {
		if (this._node == node) {
			return;
		}
		
		if (this._node) {
			var scene = cn.Node.ancestorScene(this._node);
			if (scene instanceof cn.Scene) {
				scene.removeTouchNode(this._node);
			}
		}
		
		this._node = node;
		
		if (this._node) {
			var scene = cn.Node.ancestorScene(this._node);
			if (scene instanceof cn.Scene) {
				var maxTouches = this._dragEnabled ? 1 : -1;
				scene.addTouchNode(this._node, this, maxTouches);
			}
		}
	};
	
	var getDelegate = function() {
		return this._delegate;
	};
	var setDelegate = function(delegate) {
		this._delegate = delegate;
	};
	
	// CCTargetedTouchDelegate
	var onTouchBegan = function(touch, event) {
		var delegate = this._delegate;
		var node = this._node;
		
		if (!cn.Node.containsTouchLocation(touch, node)) {
			return false;
		}
		
		// touch points
		var point = node.convertTouchToNodeSpace(touch);
		this._touchBeganPoint = point;
		this._touchPoint = point;
		this._touchEndedPoint = point;
		
		if (this._dragEnabled) {
			point = node.convertToWorldSpace(point);
			this._touchBeganPoint = point;
			this._touchPoint = point;
			this._touchEndedPoint = point;
			
			this._originalPosition = node.getPosition();
			return delegate.onDragStart(node);
		}
		
		// button delegate
		this._status = cn.TouchNodeActivie;
		delegate.onFingerDown(node);
		delegate.onFingerOver(node);
		return true;
	};
	
	var onTouchMoved = function(touch, event) {
		var delegate = this._delegate;
		var node = this._node;
		
		// touch points
		var point = node.convertTouchToNodeSpace(touch);
		this._touchPoint = point;
		
		if (this._dragEnabled) {
			point = node.convertToWorldSpace(point);
			this._touchPoint = point;
			
			var delta = cc.p(point.x - this._touchBeganPoint.x,
							 point.y - this._touchBeganPoint.y);
			var parent = node.getParent();
			
			var position = parent.convertToWorldSpace(this._originalPosition);
			position.x += delta.x;
			position.y += delta.y;
			position = parent.convertToNodeSpace(position);
			// try to move to new position
			var oldPosition = node.getPosition();
			if (!delegate.onDrag(node)) {
				node.setPosition(oldPosition);
			}
			return;
		}
		
		// button delegate
		if (cn.Node.containsTouchLocation(touch, node)) {
			if (this._status === cn.TouchNodeNormal) {
				this._status = cn.TouchNodeActivie;
				delegate.onFingerOver(node);
			} else {
				delegate.onFingerMove(node);
			}
		} else {
			if (this._status === cn.TouchNodeActivie) {
				this._status = cn.TouchNodeNormal;
				delegate.onFingerOut(node);
			}
		}
	};
	
	var onTouchEnded = function(touch, event) {
		var delegate = this._delegate;
		var node = this._node;
		
		// touch points
		var point = node.convertTouchToNodeSpace(touch);
		this._touchPoint = point;
		this._touchEndedPoint = point;
		
		if (this._dragEnabled) {
			point = node.convertToWorldSpace(point);
			this._touchPoint = point;
			this._touchEndedPoint = point;
			
			if (!this._delegate.onDragEnd(node)) {
				var moveTo = cc.MoveTo.create(0.2, this._originalPosition);
				moveTo = cc.EaseInOut.create(moveTo, 2.0);
				node.runAction(moveTo);
			}
			return;
		}
		
		// button delegate
		this._status = cn.TouchNodeNormal;
		if (cn.Node.containsTouchLocation(touch, node)) {
			delegate.onFingerUp(node);
		}
		delegate.onFingerOut(node);
		
		// guesture delegate
		var d = cc.p(this._touchEndedPoint.x - this._touchBeganPoint.x,
					 this._touchEndedPoint.y - this._touchBeganPoint.y);
		var quantum = 100.0;
		if (d.x > - quantum && d.x < quantum) {
			if (d.y > quantum) {
				delegate.onSwipeUp(node);
				return;
			} else if (d.y < - quantum) {
				delegate.onSwipeDown(node);
				return;
			}
		} else if (d.y > - quantum && d.y < quantum) {
			if (d.x > quantum) {
				delegate.onSwipeRight(node);
				return;
			} else if (d.x < - quantum) {
				delegate.onSwipeLeft(node);
				return;
			}
		}
		
		// click delegate
		if (cn.Node.containsTouchLocation(touch, node)) {
			delegate.onClick(node);
		}
	};
	
	var onTouchCancelled = function(touch, event) {
		this.onTouchEnded(touch, event);
	};
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: TouchController,
		
		init: init,
		
		getNode: getNode,
		setNode: setNode,
		
		getDelegate: getDelegate,
		setDelegate: setDelegate,
		
		// CCTargetedTouchDelegate
		onTouchBegan: onTouchBegan,
		onTouchMoved: onTouchMoved,
		onTouchEnded: onTouchEnded,
		onTouchCancelled: onTouchCancelled,
		
		// properties
		_node: null,
		_delegate: null,
		
		_touchBeganPoint: null,
		_touchPoint: null,
		_touchEndedPoint: null,
		
		_originalPosition: null, // save drag start position
		_dragEnabled: false,
		
		_status: 0,
	};
	
	// extends
	cn.TouchController = cc.TargetedTouchDelegate.extend(prop);
	
}(Coconut2D);
