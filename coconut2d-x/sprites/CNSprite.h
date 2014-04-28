//
//  CNSprite.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-21.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNSprite_h
#define Coconut2D_X_CNSprite_h

#include "../CNNode.h"
#include "../cocoa/CNSelector.h"

NS_CN_BEGIN

#define CN_SPRITE_FACTORY(class_name)         CN_INLINE_FACTORY(class_name, node, init)
#define CN_SPRITE_WITH_FILE(class_name)       CN_INLINE_FACTORY_VAR(class_name, spriteWithFile, initWithFile, const char *)
#define CN_SPRITE_WITH_DICTIONARY(class_name) CN_INLINE_FACTORY_VAR(class_name, spriteWithDictionary, initWithDictionary, cocos2d::CCDictionary *)

#define CNSPRITE_FACTORIES(class_name) /* CNSprite factories begin */ \
				CN_SPRITE_FACTORY(class_name); \
				CN_SPRITE_WITH_FILE(class_name); \
				CN_SPRITE_WITH_DICTIONARY(class_name); \
/* CNSprite factories end */


class CN_DLL CNSprite : public cocos2d::CCSprite, public CNSelectorDelegate
{
public:
	virtual bool initWithFile(const char * pszFilename);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	static cocos2d::CCArray * createSprites(cocos2d::CCArray * pFilenames);
	
	/**
	 *  change the sprite's image
	 */
	virtual void replaceImageWithFile(const char * pszFilename);
	static cocos2d::CCImage * getImageWithFile(const char * pszFilename);
	
	// CNNode Extensions
	CNNODE_EXTENSIONS(CNSprite);
	// CNSprite factories
	CNSPRITE_FACTORIES(CNSprite);
};

NS_CN_END

#endif
