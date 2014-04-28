//
//  SFVideo.cpp
//  SpriteForest-X
//
//  Created by Moky on 13-7-24.
//  Copyright (c) 2013 Slanissue Inc. All rights reserved.
//

#include "SFVideo.h"

extern void SFVideo_initPlayer(const float x, const float y, const float width, const float height);
extern void SFVideo_playMovie(const char * pszFile);
extern void SFVideo_stopMovie(void);

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

bool SFVideo::perform(CCDictionary * pDict, cocos2d::CCNode * pTarget)
{
	if (!pDict)
	{
		CNLog("error");
		return false;
	}
	
	CCString * pTask = (CCString *)pDict->objectForKey("Task");
	if (!pTask)
	{
		CNLog("invalid video task");
		return false;
	}
	const char * task = pTask->getCString();
	CNLog("SFVideo: ******************************** %s", task);
	
	if (strlen(task) == 0)
	{
		CNLog("invalid task");
	}
	else if (strcasecmp(task, "Init") == 0 || strcasecmp(task, "InitPlayer") == 0)
	{
		CNLog("init video player");
		if (pTarget)
		{
			CCNode * pParent = pTarget->getParent();
			if (pParent)
			{
				CCPoint position = ccpSub(pTarget->getPosition(), pTarget->getAnchorPointInPoints());
				CCPoint p2 = ccpAdd(position, ccpFromSize(pTarget->getContentSize()));
				
				position = pParent->convertToWorldSpace(position);
				p2 = pParent->convertToWorldSpace(p2);
				
				SFVideo_initPlayer(position.x, position.y, p2.x - position.x, p2.y - position.y);
			}
			else
			{
				CNLog("error");
			}
		}
		else
		{
			CNLog("error");
		}
	}
	else if (strcasecmp(task, "play") == 0 || strcasecmp(task, "playMovie") == 0)
	{
		CCString * pFilename = (CCString *)pDict->objectForKey("File");
		const char * filename = pFilename ? pFilename->getCString() : "";
		CNLog("playing video: %s", filename);
		SFVideo_playMovie(filename);
	}
	else if (strcasecmp(task, "stop") == 0 || strcasecmp(task, "stopMovie") == 0)
	{
		CNLog("stop video");
		SFVideo_stopMovie();
	}
	
	return true;
}

void SFVideo::stopAll(void)
{
	CNLog("stop all video");
	SFVideo_stopMovie();
}

NS_SF_END
