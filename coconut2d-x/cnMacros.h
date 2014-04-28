//
//  cnMacros.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-20.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#ifndef Coconut2D_X_cnMacros_h
#define Coconut2D_X_cnMacros_h

#include <math.h>

#include "cocos2d.h"


#define CNCreateBuffer(len)   ({ char * __buffer = (char *)malloc(len); memset(__buffer, 0, len); __buffer; })
#define CNFreeBuffer(p)       do { if (p) { free(p); p = NULL; } } while (0)

/**
 *  Print log info
 *
 *  Usage:
 *      CNLog(format, ...)
 *      format: "[LineNumber]+[Class Function] > InfoString"
 */
#if 0
#	define NSLog(...)   do {} while(0)
#	define CNLog(...)   do {} while(0)
#else
//	HH:mm:ss
#	define CNLogTime()           ({ char * __tmp = CNCreateBuffer(16); \
                                    time_t __time = time(NULL); \
                                    tm * __tm = gmtime(&__time); \
                                    snprintf(__tmp, 16, "%02d:%02d:%02d", __tm->tm_hour, __tm->tm_min, __tm->tm_sec); \
                                    __tmp; })
//	filename.ext
#	define CNLogFile()           ({ char * __tmp = CNCreateBuffer(32); \
                                    std::string __file(__FILE__); \
                                    snprintf(__tmp, 32, "%s", __file.substr(__file.rfind("/") + 1).c_str()); \
                                    __tmp; })
//	[HH:mm:ss] filename.ext [0000] function
#	define CNLogHead()           ({ char * __tmp = CNCreateBuffer(128); \
                                    char * __time = CNLogTime(); \
                                    char * __file = CNLogFile(); \
                                    snprintf(__tmp, 128, "[%s] %s [% 4d] %s", __time, __file, __LINE__, __FUNCTION__); \
                                    CNFreeBuffer(__file); \
                                    CNFreeBuffer(__time); \
                                    __tmp; })
//	...
#	define CNLogMsg(format, ...) ({ char * __tmp = CNCreateBuffer(512); \
                                    snprintf(__tmp, 512, format, ##__VA_ARGS__); \
                                    __tmp; })
//	[HH:mm:ss] filename.ext [0000] function > ...
#	define CNLog(format, ...)    do { \
                                     char * __head = CNLogHead(); \
                                     char * __msg = CNLogMsg(format, ##__VA_ARGS__); \
                                     cocos2d::CCLog("%s > %s", __head, __msg); \
                                     CNFreeBuffer(__head); \
                                     CNFreeBuffer(__msg); \
                                 } while (0)
#endif





#define CN_SAFE_RETAIN(p) /* safe retain begin */ \
	do { \
		cocos2d::CCObject * _##p = dynamic_cast<cocos2d::CCObject *>(p); \
		if (_##p) { \
			_##p->retain(); \
		} \
	} while (0) \
/* safe retain end */

#define CN_SAFE_RELEASE(p) /* safe release begin */ \
	do { \
		cocos2d::CCObject * _##p = dynamic_cast<cocos2d::CCObject *>(p); \
		if (_##p) { \
			_##p->release(); \
		} \
	} while (0) \
/* safe release end */

#define CN_SAFE_AUTORELEASE(p) /* safe autorelease begin */ \
	do { \
		cocos2d::CCObject * _##p = dynamic_cast<cocos2d::CCObject *>(p); \
		if (_##p) { \
			_##p->autorelease(); \
		} \
	} while (0) \
/* safe autorelease end */

#define CN_SYNTHESIZE_RETAIN(varType, varName, funName) /* synthesize begin */ \
	protected: varType varName; \
	public: virtual varType get##funName(void) const { return varName; } \
	public: virtual void set##funName(varType var) { \
		if (varName != var) { \
			CN_SAFE_RETAIN(var); \
			CN_SAFE_RELEASE(varName); \
			varName = var; \
		} \
	} \
/* synthesize end */

#define CN_INLINE_FACTORY(class, factory, init) /* inline factory(void) begin */ \
				public: static inline class * factory(void) { \
					class * obj = new class(); \
					if (obj && obj->init()) { \
						CN_SAFE_AUTORELEASE(obj); \
						return obj; \
					} \
					CC_SAFE_DELETE(obj); \
					return NULL; \
				} \
/* inline factory(void) end */

#define CN_INLINE_FACTORY_VAR(class, factory, init, type) /* inline factory(var) begin */ \
				public: static inline class * factory(type var) { \
					class * obj = new class(); \
					if (obj && obj->init(var)) { \
						CN_SAFE_AUTORELEASE(obj); \
						return obj; \
					} \
					CC_SAFE_DELETE(obj); \
					return NULL; \
				} \
/* inline factory(var) end */




#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#	define DIV(A, B)    ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __b == 0 ? INFINITY : __a / __b; })
#else
#	define DIV(A, B)    ((B) == 0 ? INFINITY : (A) / (B))
#endif




#define CN_DLL          CC_DLL

// namespace coconut2d {}
#ifdef __cplusplus
#	define NS_CN_BEGIN  namespace coconut2d {
#	define NS_CN_END    }
#	define USING_NS_CN  using namespace coconut2d
#else
#	define NS_CN_BEGIN
#	define NS_CN_END
#	define USING_NS_CN
#endif



#endif
