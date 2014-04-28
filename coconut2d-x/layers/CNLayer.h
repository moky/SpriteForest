//
//  CNLayer.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-22.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNLayer_h
#define Coconut2D_X_CNLayer_h

#include "../CNNode.h"
#include "../cocoa/CNSelector.h"

NS_CN_BEGIN


#define CN_LAYER_FACTORY(class_name)         CN_INLINE_FACTORY(class_name, node, init)
#define CN_LAYER_WITH_FILE(class_name)       CN_INLINE_FACTORY_VAR(class_name, layerWithFile, initWithFile, const char *)
#define CN_LAYER_WITH_NODE(class_name)       CN_INLINE_FACTORY_VAR(class_name, layerWithNode, initWithNode, cocos2d::CCNode *)
#define CN_LAYER_WITH_FRAME(class_name)      CN_INLINE_FACTORY_VAR(class_name, layerWithFrame, initWithFrame, const cocos2d::CCRect &)
#define CN_LAYER_WITH_DICTIONARY(class_name) CN_INLINE_FACTORY_VAR(class_name, layerWithDictionary, initWithDictionary, cocos2d::CCDictionary *)

#define CNLAYER_FACTORIES(class_name) /* CNLayer factories begin */ \
				CN_LAYER_FACTORY(class_name); \
				CN_LAYER_WITH_FILE(class_name); \
				CN_LAYER_WITH_NODE(class_name); \
				CN_LAYER_WITH_FRAME(class_name); \
				CN_LAYER_WITH_DICTIONARY(class_name); \
/* CNLayer factories end */

class CN_DLL CNLayer : public cocos2d::CCLayer, public CNSelectorDelegate
{
public:
	virtual ~CNLayer(void);
	virtual bool init(void);
	
	virtual bool initWithFile(const char * pszFilename);
	virtual bool initWithNode(cocos2d::CCNode * pNode);
	virtual bool initWithFrame(const cocos2d::CCRect & tFrame);
	virtual bool initWithDictionary(cocos2d::CCDictionary * pDict);
	
	void focus(const cocos2d::CCPoint & tPoint);
	cocos2d::CCPoint focus(void);
	
	// CNNode Extensions
	CNNODE_EXTENSIONS(CNLayer);
	// CNNode factories
	CNLAYER_FACTORIES(CNLayer);
};

NS_CN_END

#endif
