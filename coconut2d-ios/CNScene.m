//
//  CNScene.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNScene.h"

#import "cnMacros.h"


@implementation CNScene

- (id) init
{
	if ((self = [super init]))
	{
		[touchNodes_ release];
		touchNodes_ = [[NSMutableDictionary alloc] initWithCapacity:29];
		
		[allClaimedKeys_ release];
		allClaimedKeys_ = [[NSMutableSet alloc] initWithCapacity:5];
		
		// clean up caches
		[[CCTextureCache sharedTextureCache] removeAllTextures];
		[[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFrames];
	}
	return self;
}

- (void) dealloc
{
	[touchNodes_ release];
	[allClaimedKeys_ release];
	
	CNLog(@"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ %@ dealloc", [self class]);
	[super dealloc];
}


#pragma mark -


- (void) addChild:(CCNode *)child
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z
{
	if (child == nil)
	{
		return ;
	}
	[super addChild:child z:z];
}

- (void) addChild:(CCNode *)child z:(NSInteger)z tag:(NSInteger)tag
{
	if (child == nil || child.parent != nil)
	{
		return ;
	}
	[super addChild:child z:z tag:tag];
}

#pragma mark -

- (void) perform
{
	[[self class] perform:self];
}

+ (void) perform:(CCScene *)scene
{
	CCDirector * director = [CCDirector sharedDirector];
	if (director.runningScene)
	{
		// Clean the current scene before next created,
		// to avoid crash caused by sprite frame cache,
		// because CNScene will clean up all textures caches while creating
		[director.runningScene cleanup];
		// Now create new scene for replacement.
		// NOTICE: here will call 'runningScene onExit' second time
		[director replaceScene:scene];
	}
	else
	{
		[director runWithScene:scene];
	}
}


+ (UIImage *) snapshot
{
	CCDirector * director = [CCDirector sharedDirector];
	if ([director isPaused])
	{
		CNLog(@"sgx error: background gpu access not permitted");
		return nil;
	}
	
	CGSize displaySize = director.displaySizeInPixels;
	CGSize winSize = director.winSize;
	
	//Create buffer for pixels
	GLuint bufferLength = displaySize.width * displaySize.height * sizeof(ccColor4B);
	ccColor4B * buffer = (ccColor4B *)malloc(bufferLength);
	
	//Read Pixels from OpenGL
	glReadPixels(0, 0, displaySize.width, displaySize.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	
	//Make data provider with data.
	CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLength, NULL);
	
	//Configure image
	int bitsPerComponent = 8;
	int bitsPerPixel = 32;
	int bytesPerRow = 4 * displaySize.width;
	CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
	CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
	CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
	CGImageRef iref = CGImageCreate(displaySize.width, displaySize.height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
	CGColorSpaceRelease(colorSpaceRef);
	
	uint32_t* pixels = (uint32_t*)malloc(bufferLength);
	CGContextRef context = CGBitmapContextCreate(pixels, winSize.width, winSize.height, 8, winSize.width * 4, CGImageGetColorSpace(iref), kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
	
	CGContextTranslateCTM(context, 0, displaySize.height);
	CGContextScaleCTM(context, 1.0f, -1.0f);
	
	switch (director.deviceOrientation)
	{
		case CCDeviceOrientationPortrait:
			break;
		case CCDeviceOrientationPortraitUpsideDown:
			CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(180));
			CGContextTranslateCTM(context, -displaySize.width, -displaySize.height);
			break;
		case CCDeviceOrientationLandscapeLeft:
			CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(-90));
			CGContextTranslateCTM(context, -displaySize.height, 0);
			break;
		case CCDeviceOrientationLandscapeRight:
			CGContextRotateCTM(context, CC_DEGREES_TO_RADIANS(90));
			CGContextTranslateCTM(context, displaySize.width * 0.5f, -displaySize.height);
			break;
	}
	
	CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, displaySize.width, displaySize.height), iref);
	CGImageRef imageRef = CGBitmapContextCreateImage(context);
	UIImage *outputImage = [UIImage imageWithCGImage:imageRef];
	CGImageRelease(imageRef);
	
	//Dealloc
	CGDataProviderRelease(provider);
	CGImageRelease(iref);
	CGContextRelease(context);
	free(buffer);
	free(pixels);
	
	return outputImage;
}

- (void) snapshot
{
	UIImage * image = [CNScene snapshot];
	UIImageWriteToSavedPhotosAlbum(image, self, @selector(imageSavedToPhotosAlbum:didFinishSavingWithError:contextInfo:), nil);
}

- (void) imageSavedToPhotosAlbum:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
	CNLog(@"override me!");
}

@end
