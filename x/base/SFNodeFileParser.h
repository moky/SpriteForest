//
//  SFNodeFileParser.h
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef SpriteForest_X_SFNodeFileParser_h
#define SpriteForest_X_SFNodeFileParser_h

#include "../sfMacros.h"

NS_SF_BEGIN

class SF_DLL SFNodeFileParser : public cocos2d::CCObject
{
	CC_SYNTHESIZE(std::string, m_sPath, Path);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary *, m_pRoot, Root);
public:
	SFNodeFileParser(void);
	virtual ~SFNodeFileParser(void);
	virtual bool init(void);
	
	static SFNodeFileParser * parser(const char * pszPath);
	virtual bool initWithFile(const char * pszPath);
	
	void parse(const char * pszPath);
	cocos2d::CCObject * node(void) const;
private:
	cocos2d::CCObject * traverse(cocos2d::CCObject * pObject) const;
};

NS_SF_END

#endif
