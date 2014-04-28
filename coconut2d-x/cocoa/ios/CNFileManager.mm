//
//  CNFileManager.mm
//  Coconut2D-X
//
//  Created by Moky on 12-12-4.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#import "../CNFileManager.h"

NS_CN_BEGIN

USING_NS_CC;

CNFileManager::CNFileManager(void)
: CCObject()
, m_sResourceDirectory("")
, m_sDocumentDirectory("")
, m_sCachesDirectory("")
, m_sTemporaryDirectory("")
{
	
}

CNFileManager::~CNFileManager(void)
{
	
}

const char * CNFileManager::fullFilePath(std::string & sResourceFilename)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * filename = [NSString stringWithUTF8String:sResourceFilename.c_str()];
	NSRange range = [filename rangeOfString:@"://"];
	if ([filename length] == 0)
	{
		CNLog("error");
	}
	else if ([filename isAbsolutePath] || range.location != NSNotFound)
	{
		// do nothing
	}
	else
	{
		filename = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:filename];
		sResourceFilename = [filename cStringUsingEncoding:NSUTF8StringEncoding];
	}
	[pool release];
	return sResourceFilename.c_str();
}

bool CNFileManager::init(void)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	{
		m_sResourceDirectory = [[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSUTF8StringEncoding];
	}
	{
		NSArray * paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString * dir = [paths objectAtIndex:0];
		m_sDocumentDirectory = [dir cStringUsingEncoding:NSUTF8StringEncoding];
	}
	{
		NSArray * paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
		NSString * dir = [paths objectAtIndex:0];
		m_sCachesDirectory = [dir cStringUsingEncoding:NSUTF8StringEncoding];
	}
	{
		NSString * dir = NSTemporaryDirectory();
		m_sTemporaryDirectory = [dir cStringUsingEncoding:NSUTF8StringEncoding];
	}
	[pool release];
	return true;
}

bool CNFileManager::init(const char * pszAppName)
{
	return init();
}

static CNFileManager * s_pSharedManager = NULL;

CNFileManager * CNFileManager::sharedManager(void)
{
	if (!s_pSharedManager)
	{
		s_pSharedManager = new CNFileManager();
		s_pSharedManager->init();
	}
	return s_pSharedManager;
}

bool CNFileManager::isExists(const char * pszFilePath)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * path = [NSString stringWithUTF8String:pszFilePath];
	if (![path isAbsolutePath])
	{
		path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:path];
	}
	bool flag = [[NSFileManager defaultManager] fileExistsAtPath:path];
	[pool release];
	return flag;
}

bool CNFileManager::isWritable(const char * pszFilePath)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * path = [NSString stringWithUTF8String:pszFilePath];
	bool flag = [[NSFileManager defaultManager] isWritableFileAtPath:path];
	[pool release];
	return flag;
}

CCDictionary * CNFileManager::getAttributes(const char * pszFilePath)
{
	CCDictionary * pDict = CCDictionary::dictionary();
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSString * path = [NSString stringWithUTF8String:pszFilePath];
	NSError * error = nil;
	NSDictionary * dict = [[NSFileManager defaultManager] attributesOfItemAtPath:path error:&error];
	if (error)
	{
		CNLog("error: %s", [[error debugDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
	}
	else
	{
		NSArray * allKeys = [dict allKeys];
		for (NSString * key in allKeys)
		{
			NSString * str = [[dict objectForKey:key] description];
			const char * k = [key cStringUsingEncoding:NSUTF8StringEncoding];
			const char * v = [str cStringUsingEncoding:NSUTF8StringEncoding];
			pDict->setObject(CCString::stringWithCString(v), k);
		}
	}
	
	[pool release];
	return pDict;
}

bool CNFileManager::copy(const char *pszSourcePath, const char *pszTargetPath)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * sourcePath = [NSString stringWithUTF8String:pszSourcePath];
	NSString * targetPath = [NSString stringWithUTF8String:pszTargetPath];
	BOOL flag = [[NSFileManager defaultManager] copyItemAtPath:sourcePath toPath:targetPath error:NULL];
	[pool release];
	return flag;
}

bool CNFileManager::move(const char * pszSourcePath, const char * pszTargetPath)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * sourcePath = [NSString stringWithUTF8String:pszSourcePath];
	NSString * targetPath = [NSString stringWithUTF8String:pszTargetPath];
	BOOL flag = [[NSFileManager defaultManager] moveItemAtPath:sourcePath toPath:targetPath error:NULL];
	[pool release];
	return flag;
}

bool CNFileManager::remove(const char * pszFilePath)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * path = [NSString stringWithUTF8String:pszFilePath];
	BOOL flag = [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
	[pool release];
	return flag;
}

bool CNFileManager::mkdir(const char * pszDir)
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSString * path = [NSString stringWithUTF8String:pszDir];
	BOOL flag = [[NSFileManager defaultManager] createDirectoryAtPath:path
										  withIntermediateDirectories:true
														   attributes:nil
																error:nil];
	[pool release];
	return flag;
}

NS_CN_END
