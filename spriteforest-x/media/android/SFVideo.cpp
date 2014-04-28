//
//  SFVideo.cpp
//  SuperFans
//
//  Created by Moky on 13-7-30.
//  Copyright (c) 2013年 Slanissue Inc. All rights reserved.
//

#include "coconut2d.h"

void SFVideo_initPlayer(const float x, const float y, const float width, const float height)
{
	CNLog("not implement: {{%.2f, %.2f}, {%.2f, %.2f}}", x, y, width, height);
}

void SFVideo_playMovie(const char * pszFile)
{
	if (!pszFile)
	{
		CNLog("not implement");
	}
	else
	{
		CNLog("not implement: %s", pszFile);
	}
}

void SFVideo_stopMovie(void)
{
	CNLog("not implement");
}
