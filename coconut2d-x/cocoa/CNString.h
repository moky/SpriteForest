//
//  CNString.h
//  Coconut2D-X
//
//  Created by Moky on 12-11-24.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#ifndef Coconut2D_X_CNString_h
#define Coconut2D_X_CNString_h

#include "../cnMacros.h"

NS_CN_BEGIN

//
// Convienient String Reader
//
class CNString
{
public:
	
#pragma mark Numeric
	/**
	 *    0123456789 || -0123456789 || .0123456789 || -.0123456789
	 */
	static bool isNumeric(const std::string & string);
	/**
	 *    0123456789 || -0123456789
	 */
	static bool isInteger(const std::string & string);
	/**
	 *    .0123456789 || -.0123456789
	 */
	static inline bool isFloat(const std::string & string) {
		return isNumeric(string) && (!isInteger(string));
	}
	
#pragma mark Trim
	static inline std::string & ltrim(std::string & string, const std::string & pattern) {
		std::size_t pos = string.find_first_not_of(pattern);
		string = (pos == std::string::npos) ? "" : string.substr(pos);
		return string;
	}
	static inline std::string & rtrim(std::string & string, const std::string & pattern) {
		std::size_t pos = string.find_last_not_of(pattern);
		string = (pos == std::string::npos) ? "" : string.substr(0, pos + 1);
		return string;
	}
	static inline std::string & trim(std::string & string, const std::string & pattern) {
		return rtrim(ltrim(string, pattern), pattern);
	}
	
	static inline std::string & ltrim(std::string & string) {
		return ltrim(string, " \n\r\t");
	}
	static inline std::string & rtrim(std::string & string) {
		return rtrim(string, " \n\r\t");
	}
	static inline std::string & trim(std::string & string) {
		return trim(string, " \n\r\t");
	}
	
#pragma mark Case
	static inline std::string & lowercaseString(std::string & string) {
		for (int i = string.length() - 1; i >= 0; i--) {
			string[i] = tolower(string[i]);
		}
		return string;
	}
	static inline std::string & uppercaseString(std::string & string) {
		for (int i = string.length() - 1; i >= 0; i--) {
			string[i] = toupper(string[i]);
		}
		return string;
	}
	
#pragma mark URL
	static std::string & stringByAddingPercentEscapes(std::string & string);
	static std::string & stringByReplacingPercentEscapes(std::string & string);
	
	static std::string & stringByAddingUrlParameter(std::string & url, const std::string & key, const std::string & value);
	static std::string & stringByAddingClientParameters(std::string & url);
	static bool isDynamicURLString(const std::string & url);
	
#pragma mark Array
	static cocos2d::CCArray * split(const std::string & string, const std::string & pattern);
	static bool containsInArray(const std::string & string, const cocos2d::CCArray * pArray);
	
#pragma mark Prefix & Suffix
	static inline bool hasPrefix(const std::string & string, const std::string & prefix) {
		int len1 = string.length(), len2 = prefix.length();
		return len1 < len2 ? false : strcmp(string.substr(0, len2).c_str(), prefix.c_str()) == 0;
	}
	static inline bool hasSuffix(const std::string & string, const std::string & suffix) {
		int len1 = string.length(), len2 = suffix.length();
		return len1 < len2 ? false : strcmp(string.substr(len1 - len2).c_str(), suffix.c_str()) == 0;
	}
	
#pragma mark Path
	static inline bool isAbsolutePath(const std::string & string) {
		return hasPrefix(string, "/") || hasPrefix(string, "file://");
	}
	/**
	 *  Cut down substring '../' and the prefix directory name at the same time.
	 */
	static std::string & simplifyPath(std::string & string);
	
	static inline std::string & lastPathComponent(std::string & string) {
		int pos = string.rfind('/');
		if (pos != std::string::npos) string = string.substr(pos + 1);
		return string;
	}
	static inline std::string & pathExtension(std::string & string) {
		int pos = string.rfind('.');
		string = (pos == std::string::npos) ? "" : string.substr(pos + 1);
		return string;
	}
	static inline std::string & stringByAppendingPathExtension(std::string & string, const std::string & ext) {
		int len1 = string.length(), len2 = ext.length();
		string += (len1 > 0 && string[len1 - 1] != '.' && len2 > 0 && ext[0] != '.') ? "." + ext : ext;
		return string;
	}
	static inline std::string & stringByDeletingPathExtension(std::string & string) {
		int pos = string.rfind('.');
		if (pos != std::string::npos) string = string.substr(0, pos);
		return string;
	}
	static inline std::string & stringByAppendingPathComponent(std::string & string, const std::string & path) {
		int len1 = string.length(), len2 = path.length();
		string += (len1 > 0 && string[len1 - 1] != '/' && len2 > 0 && path[0] != '/') ? "/" + path : path;
		return string;
	}
	static inline std::string & stringByDeletingLastPathComponent(std::string & string) {
		int pos = string.rfind('/');
		string = (pos == std::string::npos) ? "" : string.substr(0, pos);
		return string;
	}
	
#pragma mark Others
	static std::string & stringWithFormat(std::string & string, const char * format, ...); 
};

NS_CN_END

#endif
