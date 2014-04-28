//
//  SFNodeFileParser.m
//  SpriteForest2
//
//  Created by Moky on 12-9-28.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "SFNodeFileParser.h"

#import "CJSONDeserializer.h"

#import "SFWebBrowser.h"

@interface SFNodeFileParser (private)

- (void) traverse;

@end

@implementation SFNodeFileParser

@synthesize path = path_;
@synthesize root = root_;

+ (id) parser:(NSString *)path
{
	return [[[self alloc] initWithFile:path] autorelease];
}

- (id) initWithFile:(NSString *)path
{
	if ((self = [self init]))
	{
		[self parse:path];
	}
	return self;
}

- (id) init
{
	if ((self = [super init]))
	{
		self.path = nil;
		self.root = nil;
	}
	return self;
}

- (void) dealloc
{
	[path_ release];
	[root_ release];
	
	[super dealloc];
}

- (id) node
{
	id node = nil;
	if ([root_ isKindOfClass:[NSDictionary class]])
	{
		//CNLog(@"root = %@", root_);
		node = [root_ objectForKey:@"SFNode"];
	}
	return node;
}

#pragma mark -

+ (NSDictionary *) attributesFromString:(NSString *)attributes
{
	NSMutableDictionary * mDict = nil;
	
	NSArray * pairs = [attributes componentsSeparatedByString:@";"];
	if ([pairs isKindOfClass:[NSArray class]] && [pairs count] > 0)
	{
		mDict = [NSMutableDictionary dictionaryWithCapacity:[pairs count]];
		for (NSString * pair in pairs)
		{
			NSRange range = [pair rangeOfString:@":"];
			if (range.location == NSNotFound)
			{
				CNLog(@"invalid pair: %@", pair);
				continue;
			}
			// key
			NSString * key = [pair substringToIndex:range.location];
			key = [key stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
			if ([key length] == 0)
			{
				CNLog(@"invalid key: %@", key);
				continue;
			}
			// value
			NSString * value = [pair substringFromIndex:range.location + 1];
			value = [value stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
			value = [value stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"'"]];
			value = [value stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
			
			[mDict setObject:value forKey:key];
		}
	}
	
	return mDict;
}

- (void) parse:(NSString *)path
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	self.path = [path stringByDeletingLastPathComponent];
	
	// check whether parsed
	NSString * outFile = [path lastPathComponent];
	outFile = [NSString stringWithFormat:@"%@-output.plist", [outFile stringByDeletingPathExtension]];
	outFile = [path_ stringByAppendingPathComponent:outFile];
	if ([[NSFileManager defaultManager] fileExistsAtPath:outFile])
	{
		CNLog(@"loading data from output file: %@", outFile);
		self.root = [NSDictionary dictionaryWithContentsOfFile:outFile];
		[pool release];
		return;
	}
	
	// parse it
	NSString * ext = [[path pathExtension] lowercaseString];
	if ([@"plist" isEqualToString:ext])
	{
		self.root = [NSDictionary dictionaryWithContentsOfFile:path];
	}
	else if ([@"js" isEqualToString:ext] || [@"json" isEqualToString:ext])
	{
		NSError * error = nil;
		NSData * fileData = [[NSData alloc] initWithContentsOfFile:path];
		self.root = [[CJSONDeserializer deserializer] deserializeAsDictionary:fileData error:&error];
		if (error)
		{
			CNLog(@"error = %@, path = %@", error, path);
		}
		[fileData release];
	}
	else
	{
		CNLog(@"unsupported file type: %@", path);
	}
	
	// traverse all nodes
	[self traverse];
	
	// write output
	if ([[NSFileManager defaultManager] isWritableFileAtPath:path_])
	{
		CNLog(@"writting output into file: %@", outFile);
		[root_ writeToFile:outFile atomically:YES];
	}
	
	[pool release];
}

- (id) traverse:(id)node
{
	if ([node isKindOfClass:[NSArray class]])
	{
		// array node
		NSArray * array = (NSArray *)node;
		node = [NSMutableArray arrayWithCapacity:[array count]];
		for (id child in array)
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			child = [self traverse:child];
			if (child)
			{
				[node addObject:child];
			}
			else
			{
				CNLog(@"could not happen!");
			}
			[pool release];
		} // EOF 'for (id child in array)'
	}
	else if ([node isKindOfClass:[NSDictionary class]])
	{
		// dictionary node
		NSDictionary * dict = (NSDictionary *)node;
		NSArray * allKeys = [dict allKeys];
		node = [NSMutableDictionary dictionaryWithCapacity:[allKeys count]];
		for (NSString * key in allKeys)
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			
			id child = [dict objectForKey:key];
			key = [key stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
			if (!child)
			{
				CNLog(@"ERROR!");
			}
			else if ([key isEqualToString:@"File"])
			{
				NSString * filename = (NSString *)child;
				if (![filename isAbsolutePath])
				{
					// check whether it is a URL
					NSRange range = [filename rangeOfString:@"://"];
					if (range.location == NSNotFound)
					{
						// not a URL, prefix current directory to the filename
						filename = [path_ stringByAppendingPathComponent:filename];
					}
					else
					{
						// yes! it is a URL
						filename = [filename dynamicURLString];
					}
				} // EOF if (![filename isAbsolutePath])
				
				[node setObject:filename forKey:key];
			}
			else
			{
				child = [self traverse:child];
				if (child)
				{
					[node setObject:child forKey:key];
				}
				else
				{
					CNLog(@"could not happen!");
				}
			}
			
			[pool release];
		} // EOF 'for (NSString * key in allKeys)'
	}
	else if ([node isKindOfClass:[NSString class]])
	{
		// string node
		NSString * string = (NSString *)node;
		string = [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		NSString * lowercaseString = [string lowercaseString];
		
		// include file
		NSRange range = [lowercaseString rangeOfString:@"include file=\""];
		if (range.location != NSNotFound)
		{
			// get filename
			NSString * filename = [string substringFromIndex:range.location + 14];
			range = [filename rangeOfString:@"\""];
			if (range.location != NSNotFound)
			{
				filename = [filename substringToIndex:range.location];
				filename = [filename stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
				CNLog(@"filename = [%@]", filename);
				if ([filename length] > 0)
				{
					// load 'SFNode' from file
					SFNodeFileParser * parser = [SFNodeFileParser parser:[path_ stringByAppendingPathComponent:filename]];
					node = [parser node];
				}
				else
				{
					CNLog(@"parse error, node = %@", node);
				}
			}
			else
			{
				CNLog(@"parse error, node = %@", node);
			}
			
			// get attributes
			if ([node isKindOfClass:[NSDictionary class]])
			{
				range = [lowercaseString rangeOfString:@"attributes=\""];
				if (range.location != NSNotFound)
				{
					NSString * attributes = [string substringFromIndex:range.location + 12];
					range = [attributes rangeOfString:@"\""];
					if (range.location != NSNotFound)
					{
						attributes = [attributes substringToIndex:range.location];
						attributes = [attributes stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
						CNLog(@"attributes = [%@]", attributes);
						NSDictionary * dict = [[self class] attributesFromString:attributes];
						if ([dict isKindOfClass:[NSDictionary class]])
						{
							// reset attributes
							NSArray * allKeys = [dict allKeys];
							if ([allKeys count] > 0)
							{
								node = [NSMutableDictionary dictionaryWithDictionary:node];
								for (NSString * key in allKeys)
								{
									[node setObject:[dict objectForKey:key] forKey:key];
								}
							}
							else
							{
								CNLog(@"empty dictionary");
							}
						}
						else
						{
							CNLog(@"no attributes found");
						} // EOF 'if ([dict isKindOfClass:[NSDictionary class]])'
					}
					else
					{
						CNLog(@"parse error");
					} // EOF 'if (range.location != NSNotFound)' for '"'
				} // EOF 'if (range.location != NSNotFound)' for 'attributes="'
			}
			else
			{
				CNLog(@"could not happen!");
			} // EOF 'if ([node isKindOfClass:[NSDictionary class]])'
		}
		else
		{
			node = string; // trimed string
		} // EOF 'if (range.location != NSNotFound)' for 'include file="'
	}
	
	return node;
}

- (void) traverse
{
	if (root_)
	{
		self.root = [self traverse:root_];
	}
}

@end
