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
//  SFAudio.js
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
	var Audio = function() {
	};
	
	//
	//  static functions
	//
	
	var perform = function(dict) {
		var filename = dict['File'];
		var task = dict['Task'];
		if (!task) {
			cn.error(dict);
			return false;
		}
		cn.log('audio task: ' + task + ', file: ' + filename);
		
		var engine = cc.AudioEngine.getInstance();
		
		//----------------------- background music
		if (task === 'preloadBackgroundMusic' || task === 'preloadMusic') {
			engine.preloadMusic(filename);
		} else if (task === 'playBackgroundMusic' || task === 'playMusic') {
			var loop = dict['Loop'];
			engine.playMusic(filename, loop);
		} else if (task === 'stopBackgroundMusic' || task === 'stopMusic') {
			engine.stopMusic();
		} else if (task === 'pauseBackgroundMusic' || task === 'pauseMusic') {
			engine.pauseMusic();
		} else if (task === 'resumeBackgroundMusic' || task === 'resumeMusic') {
			engine.resumeMusic();
		} else if (task === 'rewindBackgroundMusic' || task === 'rewindMusic') {
			engine.rewindMusic();
		}
		//----------------------- sound effect
		else if (task === 'preloadEffect') {
			engine.preloadEffect(filename);
		} else if (task === 'playEffect') {
			var loop = dict['Loop'];
			engine.playEffect(filename, loop);
		}
		
		return true;
	};
	
	var stopAll = function() {
		var engine = cc.AudioEngine.getInstance();
		if (engine.isBackgroundMusicPlaying()) {
			engine.stopBackgroundMusic();
		}
		engine.stopAllEffects();
	};
	
	//
	//  instance functions
	//
	
	//--------------------------------------------------------------------------
	
	var prop = {
		ctor: Audio,
		
		// properties
	};
	
	// extends
	sf.Audio = cc.Class.extend(prop);
	
	// static
	sf.Audio.perform = perform;
	sf.Audio.stopAll = stopAll;
	
}(SpriteForest);
