//
//  CNDictionary.h
//  Coconut2D
//
//  Created by Moky on 12-7-15.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSDictionary (CaseInsensitive)

- (id) objectForKeyCaseInsensitive:(NSString *)key;

@end
