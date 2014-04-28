//
//  CNString.h
//  Coconut2D
//
//  Created by Moky on 12-7-15.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (Capitalized)

- (NSString *) capitalizedString;
- (NSString *) uncapitalizedString;

- (NSString *) shiftCapitalizedString;

@end


@interface NSString (URLRequest)

+ (NSString *) parameterValueForKey:(NSString *)name withURL:(NSURL *)url;
- (NSString *) parameterValueForKey:(NSString *)name;

- (NSString *) stringByAppendingClientParameters;

- (BOOL) isDynamicURLString;
- (NSString *) dynamicURLString;

@end
