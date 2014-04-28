//
//  SFParticleSystem.h
//  BevaTing-X
//
//  Created by Moky on 12-12-26.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFParticleSystem_h
#define SpriteForest_X_SFParticleSystem_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SFParticleSystem : public cocos2d::CCParticleSystemQuad
{
	std::string m_sPositionString;
	
public:
	SFParticleSystem(void);
	virtual ~SFParticleSystem(void);
	virtual bool init(void);
	
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	static SFParticleSystem * particle(cocos2d::CCDictionary * pDict);
	
	virtual void run(cocos2d::CCNode * pNode);
};

NS_SF_END

#endif
