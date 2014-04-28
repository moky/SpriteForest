//
//  SFNodeFileParser.cpp
//  SpriteForest-X
//
//  Created by Moky on 12-11-29.
//  Copyright 2012 Slanissue Inc. All rights reserved.
//

#include "SFNodeFileParser.h"

NS_SF_BEGIN

USING_NS_CC;
USING_NS_CN;

SFNodeFileParser::SFNodeFileParser(void)
: CCObject()
, m_sPath("")
, m_pRoot(NULL)
{
	
}

SFNodeFileParser::~SFNodeFileParser(void)
{
	setRoot(NULL);
}

bool SFNodeFileParser::init(void)
{
	setPath("");
	setRoot(NULL);
	return true;
}

SFNodeFileParser * SFNodeFileParser::parser(const char * pszPath)
{
	SFNodeFileParser * parser = new SFNodeFileParser();
	if (parser && parser->initWithFile(pszPath))
	{
		parser->autorelease();
		return parser;
	}
	CC_SAFE_DELETE(parser);
	return NULL;
}

bool SFNodeFileParser::initWithFile(const char * pszPath)
{
	if (!init() || !pszPath || strlen(pszPath) == 0)
	{
		CNLog("error");
		return false;
	}
	CNLog("parsing %s", pszPath);
	parse(pszPath);
	return true;
}

CCObject * SFNodeFileParser::node() const
{
	CCDictionary * pDict = (CCDictionary *)m_pRoot;
	if (pDict)
	{
		return pDict->objectForKey("SFNode");
	}
	return NULL;
}

CCDictionary * SFNodeFileParser_attributesFromString(const char * psz)
{
	if (!psz || strlen(psz) == 0)
	{
		return NULL;
	}
	std::string string(psz);
	CCDictionary * out = CCDictionary::dictionary();
	
	// drop wrap
	std::string lowercase(psz);
	lowercase = CNString::lowercaseString(lowercase);
	std::size_t pos = lowercase.find("attributes=\"");
	if (pos != std::string::npos)
	{
		string = string.substr(pos + 12);
		pos = string.find('"');
		if (pos != std::string::npos)
		{
			string = string.substr(0, pos);
			string = CNString::trim(string);
			CNLog("attributes = [%s]", string.c_str());
		}
	}
	
	CCArray * array = CNString::split(string, ";");
	CCObject * obj = NULL;
	CCARRAY_FOREACH(array, obj)
	{
		std::string pair = ((CCString *)obj)->getCString();
		pos = pair.find(':');
		if (pos == std::string::npos)
		{
			continue;
		}
		// key
		std::string key = pair.substr(0, pos);
		key = CNString::trim(key);
		if (key.empty())
		{
			CNLog("invalid key");
			continue;
		}
		// value
		std::string value = pair.substr(pos + 1);
		value = CNString::trim(value);
		value = CNString::trim(value, "'");
		value = CNString::stringByReplacingPercentEscapes(value);
		out->setObject(CCString::stringWithCString(value.c_str()), key);
	}
	return out;
}

CCObject * SFNodeFileParser::traverse(CCObject * pObject) const
{
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	if (CCArray * pArray = dynamic_cast<CCArray *>(pObject))
	{
		// array node
		CCArray * out = CCArray::arrayWithCapacity(pArray->count());
		CCObject * obj = NULL;
		CCARRAY_FOREACH(pArray, obj)
		{
			pm->push();
			obj = traverse(obj);
			if (obj)
			{
				out->addObject(obj);
			}
			else
			{
				CNLog("could not happen!");
			}
			pm->pop();
		}
		return out;
	}
	else if (CCDictionary * pDict = dynamic_cast<CCDictionary *>(pObject))
	{
		// dictionary node
		CCDictionary * out = CCDictionary::dictionary();
		CCDictElement * pElement = NULL;
		CCDICT_FOREACH(pDict, pElement)
		{
			pm->push();
			std::string key = pElement->getStrKey();
			CCObject * child = pElement->getObject();
			if (key.empty() || !child)
			{
				CNLog("could not happen!");
				pm->pop();
				continue;
			}
			
			if (strcmp(key.c_str(), "File") == 0)
			{
				std::string filename = ((CCString *)child)->getCString();
				if (filename.empty())
				{
					CNLog("could not happen!");
				}
				else if (CNString::isAbsolutePath(filename))
				{
					CNLog("WARNING: should not set absolute path!");
					out->setObject(child, key);
				}
				else
				{
					// check whether it is a URL
					std::size_t pos = filename.find("://");
					if (pos == std::string::npos)
					{
						// not a URL, prefix current directory to the filename
						if (m_sPath.length() > 0)
						{
							std::string path(m_sPath);
							filename = CNString::stringByAppendingPathComponent(path, filename);
						}
						filename = CNString::simplifyPath(filename);
					}
					else
					{
						// yes! it's a URL
						CNLog("url: %s", filename.c_str());
					}
					out->setObject(CCString::stringWithCString(filename.c_str()), key);
				}
			}
			else
			{
				child = traverse(child);
				if (child)
				{
					out->setObject(child, key);
				}
				else
				{
					CNLog("could not happen");
				}
			}
			pm->pop();
		} // EOF 'CCARRAY_FOREACH(allKeys, obj)'
		
		return out;
	}
	else if (CCString * pString = dynamic_cast<CCString *>(pObject))
	{
		// string node
		std::string string(pString->getCString());
		string = CNString::trim(string);
		std::string lowercase(string);
		lowercase = CNString::lowercaseString(lowercase);
		
		// include file
		std::size_t pos = lowercase.find("include file=\"");
		if (pos != std::string::npos)
		{
			// get filename
			std::string filename = string.substr(pos + 14);
			pos = filename.find('"');
			if (pos != std::string::npos)
			{
				filename = filename.substr(0, pos);
				filename = CNString::trim(filename);
				CNLog("filename = [%s]", filename.c_str());
				if (filename.length() > 0)
				{
					std::string path(m_sPath);
					path = CNString::stringByAppendingPathComponent(path, filename);
					path = CNString::simplifyPath(path);
					// load 'SFNode' from file
					SFNodeFileParser * parser = SFNodeFileParser::parser(path.c_str());
					pObject = parser ? parser->node() : NULL;
					
					if (CCDictionary * dict = dynamic_cast<CCDictionary *>(pObject))
					{
						// reset attributes
						CCDictionary * attributes = SFNodeFileParser_attributesFromString(string.c_str());
						return CNDictionary::mergeDictionaries(dict, attributes);
					}
					else
					{
						return pObject;
					}
				}
			}
			else
			{
				CNLog("parse error: %s", pString->getCString());
			} // EOF 'if (filename->find('"') > 0)'
		}
		
		return CCString::stringWithCString(string.c_str()); // trimed string
	}
	
	return pObject; // other type object
}

std::string & SFNodeFileParser_transform(std::string & sPath)
{
	// check ext
	std::size_t pos = sPath.rfind(".");
	if (pos == std::string::npos)
	{
		CNLog("invalid path: %s", sPath.c_str());
		sPath = "";
		return sPath;
	}
	std::string ext = sPath.substr(pos + 1);
	if (ext.empty())
	{
		CNLog("invalid path: %s", sPath.c_str());
		sPath = "";
		return sPath;
	}
	sPath = CCFileUtils::fullPathFromRelativePath(sPath.c_str()); // try '-hd', '-ipad', '-ipadhd'...
	
	if (strcasecmp(ext.c_str(), "plist") == 0)
	{
		// relative dir
		std::string dir = (sPath.rfind("/") == std::string::npos) ? "" : sPath.substr(0, sPath.rfind("/"));
		
		std::string binaryFile = sPath.substr(0, pos) + ".pbf";
		binaryFile = CCFileUtils::fullPathFromRelativePath(binaryFile.c_str());
		if (CNFileManager::isExists(binaryFile.c_str())) // try '-hd', '-ipad', '-ipadhd'...
		{
			sPath = binaryFile;
			return sPath;
		}
		else if (SF_AUTO_TRANSFORM_PBF && !dir.empty() && CNFileManager::isWritable(dir.c_str()))
		{
			CNDataTransformer * pTransformer = new CNDataTransformer();
			if (pTransformer && pTransformer->init(sPath) && pTransformer->saveToFile(binaryFile))
			{
				CC_SAFE_DELETE(pTransformer);
				CNLog("removing original file: %s", sPath.c_str());
				CNFileManager::remove(sPath.c_str());
				sPath = binaryFile;
				return sPath;
			}
			CC_SAFE_DELETE(pTransformer);
		}
	}
	
	if (!CNFileManager::isExists(sPath.c_str()))
	{
		sPath = "";
	}
	return sPath;
}

CCDictionary * SFNodeFileParser_loadBinary(const char * pszPath)
{
	if (!CNFileManager::isExists(pszPath))
	{
		CNLog("file not found: %s", pszPath);
		return NULL;
	}
	CNLog("loading file: %s", pszPath);
	CCDictionary * pDict = NULL;
	
	CNDataReader * pReader = new CNDataReader();
	if (pReader && pReader->init(pszPath))
	{
		pDict = dynamic_cast<CCDictionary *>(pReader->getData());
		if (pDict)
		{
			pDict->retain();
			pDict->autorelease();
		}
	}
	CC_SAFE_DELETE(pReader);
	
	if (!pDict)
	{
		CNLog("Failed, path: %s", pszPath);
	}
	else
	{
		CNLog("OK, path: %s", pszPath);
	}
	return pDict;
}

CCDictionary * SFNodeFileParser_loadPlist(const char * pszPath)
{
	if (!CNFileManager::isExists(pszPath))
	{
		CNLog("file not found: %s", pszPath);
		return NULL;
	}
	CNLog("loading file: %s", pszPath);
	
	CCDictionary * pDict = CCDictionary::dictionaryWithContentsOfFile(pszPath);
	
	if (!pDict)
	{
		CNLog("Failed, path: %s", pszPath);
	}
	else
	{
		CNLog("OK, path: %s", pszPath);
	}
	return pDict;
}

bool SFNodeFileParser_safeOutput(const char * pszPath, CCDictionary * pDict)
{
	if (!pszPath || strlen(pszPath) == 0)
	{
		CNLog("error");
		return false;
	}
	
	// check format
	std::string path(pszPath);
	std::size_t pos = path.rfind(".");
	if (pos == std::string::npos)
	{
		CNLog("error, path: %s", pszPath);
		return false;
	}
	path = path.substr(0, pos); // cut the '.o' suffix
	pos = path.rfind(".");
	if (pos == std::string::npos)
	{
		CNLog("error, path: %s", pszPath);
		return false;
	}
	std::string ext = path.substr(pos + 1);
	if (ext.empty() || strcasecmp(ext.c_str(), "pbf") != 0)
	{
		CNLog("only support '.pbf' format, path: %s", pszPath);
		return false;
	}
	
	CNLog("writting parsed data into output file: %s", pszPath);
	CNDataTransformer * pTransformer = new CNDataTransformer();
	if (pTransformer && pTransformer->init(pDict) && pTransformer->saveToFile(pszPath))
	{
		CC_SAFE_DELETE(pTransformer);
		CNLog("OK, path: %s", pszPath);
		return true;
	}
	CC_SAFE_DELETE(pTransformer);
	CNLog("Error, path: %s", pszPath);
	return false;
}

void SFNodeFileParser::parse(const char * pszPath)
{
	if (!pszPath || strlen(pszPath) == 0)
	{
		CNLog("error");
		return;
	}
	
	std::string path(pszPath);
	path = SFNodeFileParser_transform(path);
	if (path.empty())
	{
		CNLog("error");
		return;
	}
	
	// relative dir
	std::size_t pos = path.rfind("/");
	std::string dir = (pos == std::string::npos) ? "" : path.substr(0, pos);
	setPath(dir);
	
	// check ext
	pos = path.rfind(".");
	std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
	if (ext.empty())
	{
		CNLog("invalid path: %s", path.c_str());
		return;
	}
	
	CCPoolManager * pm = CCPoolManager::sharedPoolManager();
	pm->push();
	CNLog("start parsing %s", path.c_str());
	
	CCDictionary * pDict = NULL;
	
	std::string outPath = path + ".o";
	if (SF_USE_OUTPUT_FILE)
	{
		// check whether parsed
		if (strcasecmp(ext.c_str(), "plist") == 0)
		{
			pDict = SFNodeFileParser_loadPlist(outPath.c_str());
		}
		else if (strcasecmp(ext.c_str(), "pbf") == 0)
		{
			pDict = SFNodeFileParser_loadBinary(outPath.c_str());
		}
		if (pDict)
		{
			CNLog("data loaded from outfile: %s", outPath.c_str());
			setRoot(pDict);
			pm->pop();
			return;
		}
	}
	
	// load file
	if (strcasecmp(ext.c_str(), "plist") == 0)
	{
		pDict = SFNodeFileParser_loadPlist(path.c_str());
	}
	else if (strcasecmp(ext.c_str(), "pbf") == 0)
	{
		pDict = SFNodeFileParser_loadBinary(path.c_str());
	}
	if (!pDict)
	{
		CNLog("failed to load data from file: %s", path.c_str());
		pm->pop();
		return;
	}
	
	// traverse all nodes
	CCObject * pObject = traverse(pDict);
	
	pDict = dynamic_cast<CCDictionary *>(pObject);
	if (!pDict)
	{
		CNLog("error");
	}
	else
	{
		setRoot(pDict);
		
		if (SF_USE_OUTPUT_FILE && CNFileManager::isWritable(dir.c_str()))
		{
			SFNodeFileParser_safeOutput(outPath.c_str(), pDict);
		}
	}
	
	CNLog("finish parsing %s", path.c_str());
	pm->pop();
}

NS_SF_END
