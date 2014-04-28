//
//  CNDataTransformer.h
//  Coconut2D-X
//
//  Created by Moky on 13-1-4.
//  Copyright 2013 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_CNDataTransformer_h
#define Coconut2D_X_CNDataTransformer_h

#include "CNData.h"

NS_CN_BEGIN

class CNDataTransformer : public CNData
{
public:
	virtual bool init(const std::string & sPath);
	virtual bool init(cocos2d::CCDictionary * pDict);
};

NS_CN_END

#endif
