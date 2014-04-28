//
//  SFAudio.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-12-5.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFAudio.h"

#include "SimpleAudioEngine.h"

NS_SF_BEGIN

USING_NS_CC;
using namespace CocosDenshion;
USING_NS_CN;

bool SFAudio::perform(CCDictionary * pDict)
{
	if (!pDict)
	{
		CNLog("error");
		return false;
	}
	
	CCString * pFilename = (CCString *)pDict->objectForKey("File");
	CCString * pTask = (CCString *)pDict->objectForKey("Task");
	if (!pTask)
	{
		CNLog("invalid audio task");
		return false;
	}
	CNLog("SFAudio: ******************************** %s", pTask->getCString());
	
	SimpleAudioEngine * pEngine = SimpleAudioEngine::sharedEngine();
	if (!pEngine)
	{
		CNLog("could not happen");
		return false;
	}
	
	const char * task = pTask->getCString();
	const char * filename = pFilename ? pFilename->getCString() : "";
	
	if (strlen(task) == 0)
	{
		CNLog("invalid task");
	}
	//----------------------- background music
	else if (strcasecmp(task, "preloadBackgroundMusic") == 0)
	{
		if (!CNFileManager::isExists(filename))
		{
			CNLog("no such audio file: %s", filename);
			return false;
		}
		pEngine->preloadBackgroundMusic(filename);
	}
	else if (strcasecmp(task, "playBackgroundMusic") == 0)
	{
		if (!CNFileManager::isExists(filename))
		{
			CNLog("no such audio file: %s", filename);
			return false;
		}
		CCString * pLoop = (CCString *)pDict->objectForKey("Loop");
		bool bLoop = pLoop ? pLoop->boolValue() : false;
		pEngine->playBackgroundMusic(filename, bLoop);
	}
	else if (strcasecmp(task, "stopBackgroundMusic") == 0)
	{
		pEngine->stopBackgroundMusic();
	}
	else if (strcasecmp(task, "pauseBackgroundMusic") == 0)
	{
		pEngine->pauseBackgroundMusic();
	}
	else if (strcasecmp(task, "resumeBackgroundMusic") == 0)
	{
		pEngine->resumeBackgroundMusic();
	}
	else if (strcasecmp(task, "rewindBackgroundMusic") == 0)
	{
		pEngine->rewindBackgroundMusic();
	}
	//----------------------- sound effect
	else if (strcasecmp(task, "preloadEffect") == 0)
	{
		if (!CNFileManager::isExists(filename))
		{
			CNLog("no such audio file: %s", filename);
			return false;
		}
		pEngine->preloadEffect(filename);
	}
	else if (strcasecmp(task, "playEffect") == 0)
	{
		if (!CNFileManager::isExists(filename))
		{
			CNLog("no such audio file: %s", filename);
			return false;
		}
		CCString * pLoop = (CCString *)pDict->objectForKey("Loop");
		bool bLoop = pLoop ? pLoop->boolValue() : false;
		pEngine->playEffect(filename, bLoop);
	}
	
	return true;
}

void SFAudio::stopAll(void)
{
	SimpleAudioEngine * pEngine = SimpleAudioEngine::sharedEngine();
	if (!pEngine)
	{
		CNLog("could not happen");
		return;
	}
	if (pEngine->isBackgroundMusicPlaying())
	{
		pEngine->stopBackgroundMusic();
	}
	pEngine->stopAllEffects();
}

NS_SF_END
