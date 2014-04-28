//
//  CNSpriteFrameDataReader.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-3.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNSpriteFrameDataReader_h
#define Coconut2D_X_CNSpriteFrameDataReader_h

#include "CNSpriteFrameData.h"

NS_CN_BEGIN

class CNSpriteFrameDataReader : public CNSpriteFrameData
{
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTexture2D *, m_pTexture, Texture);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pStringArray, StringArray); // string array
	
public:
	CNSpriteFrameDataReader(void);
	virtual ~CNSpriteFrameDataReader(void);
	virtual bool init(void);
	
	virtual bool init(const std::string & sPath);
	
protected:
	bool loadTexture(const std::string & sRelativeFile);
	bool loadSpriteFrames(void) const;
};

NS_CN_END

#endif
