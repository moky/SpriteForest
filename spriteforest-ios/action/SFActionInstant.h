//
//  SFActionInstant.h
//  SpriteForest2
//
//  Created by Moky on 12-10-1.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFAction.h"


@interface SFActionInstant : SFFiniteTimeAction

@end


@interface SFShow : SFActionInstant

@end


@interface SFHide : SFActionInstant

@end


@interface SFToggleVisibility : SFActionInstant

@end


@interface SFFlipX : SFActionInstant

@end


@interface SFFlipY : SFActionInstant

@end


@interface SFPlace : SFActionInstant
{
	CGPoint position_;
}

@end


#pragma mark - Action Call Function


@interface SFCallFunc : SFActionInstant
{
	id targetCallback_;
	SEL selector_;
}
@property(nonatomic, readwrite, retain) id targetCallback;

@end


//@interface SFCallFuncN : SFCallFunc
//
//@end
//
//
//@interface SFCallFuncND : SFCallFuncN
//
//@end


@interface SFCallFuncO : SFCallFunc
{
	id object_;
}
@property(nonatomic, readwrite, retain) id object;

@end


//@interface SFCallBlock : SFActionInstant
//
//@end
//
//
//@interface SFCallBlockN : SFActionInstant
//
//@end
