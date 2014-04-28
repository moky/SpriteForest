//
//  cnMacros.h
//  Coconut2D
//
//  Created by Moky on 12-7-8.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef _COCOSNUT_MACROS_H_
#define _COCOSNUT_MACROS_H_

#include <math.h>
#import <Foundation/Foundation.h>



/**
 *  Print log info
 *
 *  Usage:
 *      CNLog(format, ...)
 *      format: "[LineNumber]+[Class Function] > InfoString"
 */
#ifdef NDEBUG
#	define NSLog(...)   do {} while(0)
#	define CNLog(...)   do {} while(0)
#else
#	define CNLog(...)   NSLog(@"[% 4d]%s > %@", __LINE__, __FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
#endif




#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#	define DIV(A, B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __b == 0 ? INFINITY : __a / __b; })
#else
#	define DIV(A, B)    ((B) == 0 ? INFINITY : (A) / (B))
#endif






#endif	// end of _COCOSNUT_MACROS_H_
