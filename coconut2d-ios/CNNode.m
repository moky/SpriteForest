//
//  CNNode.m
//  Coconut2D
//
//  Created by Moky on 12-7-6.
//  Copyright 2012 Slanissue.com. All rights reserved.
//

#import "CNNode.h"

#import "cnMacros.h"
#import "cnProtocol.h"
#import "CNDictionary.h"


#pragma mark Touch Location Extensions

@implementation CCNode (TouchLocationExtend)

- (BOOL) containsNodeSpacePoint:(CGPoint)point
{
	CGRect rect = CGRectZero;
	rect.size = contentSize_;
	return CGRectContainsPoint(rect, point);
}

- (BOOL) containsVisiblePixelAtNodeSpacePoint:(CGPoint)point
{
	ccColor4B c = [self resetAndReadPixel:point];
	return c.a;
}

- (CGPoint) convertsTouchToNodeSpace:(UITouch *)touch
{
	if (touch.view)
	{
		return [self convertTouchToNodeSpace:touch];
	}
	CGPoint point = [touch locationInView:[[CCDirector sharedDirector] openGLView]];
	point = [[CCDirector sharedDirector] convertToGL: point];
	return [self convertToNodeSpace:point];
}

- (BOOL) containsTouchLocation:(UITouch *)touch
{
	return [self containsTouchLocation:touch checkPixel:NO];
}

- (BOOL) containsTouchLocation:(UITouch *)touch checkPixel:(BOOL)check
{
	CGPoint point = [self convertsTouchToNodeSpace:touch];
	if (![self containsNodeSpacePoint:point])
	{
		return NO;
	}
	if (!check)
	{
		return YES;
	}
	return [self containsVisiblePixelAtNodeSpacePoint:point];
}

@end


#pragma mark Attributes Extensions

@implementation CCNode (AttributesExtend)

- (void) setAttributes:(NSDictionary *)dict
{
	// size
	if (CGSizeEqualToSize(contentSize_, CGSizeZero))
	{
		NSString * size = (NSString *)[dict objectForKeyCaseInsensitive:SPRITE_SIZE_TAG];
		if (size != nil)
		{
			self.contentSize = CCSizeFromString(size);
		}
		else
		{
			NSString * width = [dict objectForKeyCaseInsensitive:SPRITE_WIDTH_TAG];
			NSString * height = [dict objectForKeyCaseInsensitive:SPRITE_HEIGHT_TAG];
			if (width != nil && height != nil)
			{
				self.contentSize = CGSizeMake([width floatValue], [height floatValue]);
			}
		}
	}
	
	// position
	NSString * position = [dict objectForKeyCaseInsensitive:SPRITE_POSITION_TAG];
	if (position != nil)
	{
		self.position = CCPointFromString(position);
	}
	else
	{
		NSString * x = [dict objectForKeyCaseInsensitive:SPRITE_POSITION_X_TAG];
		NSString * y = [dict objectForKeyCaseInsensitive:SPRITE_POSITION_Y_TAG];
		if (x != nil && y != nil)
		{
			self.position = ccp([x floatValue], [y floatValue]);
		}
	}
	
	// anchor point
	NSString * anchorPoint = [dict objectForKeyCaseInsensitive:SPRITE_ANCHOR_TAG];
	if (anchorPoint != nil)
	{
		self.anchorPoint = CCPointFromString(anchorPoint);
	}
	else
	{
		NSString * anchorX = [dict objectForKeyCaseInsensitive:SPRITE_ANCHOR_X_TAG];
		NSString * anchorY = [dict objectForKeyCaseInsensitive:SPRITE_ANCHOR_Y_TAG];
		if (anchorX != nil && anchorY != nil)
		{
			self.anchorPoint = ccp([anchorX floatValue], [anchorY floatValue]);
		}
	}
	
	// rotation
	NSString * rotation = [dict objectForKeyCaseInsensitive:SPRITE_ROTATION_TAG];
	if (rotation != nil)
	{
		self.rotation = [rotation floatValue];
	}
	
	// scale
	NSString * scale = [dict objectForKeyCaseInsensitive:SPRITE_SCALE_TAG];
	if (scale != nil)
	{
		self.scale = [scale floatValue];
	}
	else
	{
		NSString * scaleX = [dict objectForKeyCaseInsensitive:SPRITE_SCALE_X_TAG];
		NSString * scaleY = [dict objectForKeyCaseInsensitive:SPRITE_SCALE_Y_TAG];
		if (scaleX != nil && scaleY != nil)
		{
			self.scaleX = [scaleX floatValue];
			self.scaleY = [scaleY floatValue];
		}
	}
	
	// skew
	NSString * skewX = [dict objectForKeyCaseInsensitive:SPRITE_SKEW_X_TAG];
	NSString * skewY = [dict objectForKeyCaseInsensitive:SPRITE_SKEW_Y_TAG];
	if (skewX != nil && skewY != nil)
	{
		self.skewX = [skewX floatValue];
		self.skewY = [skewY floatValue];
	}
	
	// tag
	NSString * tag = [dict objectForKeyCaseInsensitive:SPRITE_TAG_TAG];
	if (tag != nil)
	{
		self.tag = [tag integerValue];
	}
	
	// visible
	NSString * hidden = [dict objectForKeyCaseInsensitive:SPRITE_HIDDEN_TAG];
	if (hidden != nil)
	{
		self.visible = ![hidden boolValue];
	}
}

- (CCScene *) scene
{
	for (CCNode * node = self; [node isKindOfClass:[CCNode class]]; node = node.parent)
	{
		if ([node isKindOfClass:[CCScene class]])
		{
			return (CCScene *)node;
		}
	}
	CNLog(@"the node is not perform currently");
	return nil;
}

@end


#pragma mark Pixels and Image Extensions

@implementation CCNode (TextureExtend)

- (void) readPixels:(CGRect)rect buffer:(ccColor4B *)buffer
{
	// quick return if not visible
	if (!visible_)
	{
		return;
	}
	if ([[CCDirector sharedDirector] isPaused])
	{
		CNLog(@"sgx error: background gpu access not permitted");
		return;
	}
	
	self.position = ccpSub(position_, rect.origin);
	@try
	{
		CCRenderTexture * rt = [CCRenderTexture renderTextureWithWidth:rect.size.width height:rect.size.height];
		[rt beginWithClear:0 g:0 b:0 a:0];
		{
			[self visit];
			glReadPixels(0, 0, rect.size.width, rect.size.height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		}
		[rt end];
	}
	@catch (NSException * exception)
	{
		CNLog(@"ERROR: exception = %@", [exception debugDescription]);
	}
	@finally
	{
		self.position = ccpAdd(position_, rect.origin);
	}
}

- (void) resetAndReadPixels:(CGRect)rect buffer:(ccColor4B *)buffer
{
	// save orign values
	CGPoint orignPosition = positionInPixels_;
	CGFloat orignRotation = rotation_;
	CGFloat orignScaleX = scaleX_;
	CGFloat orignScaleY = scaleY_;
	CGFloat orignSkewX = skewX_;
	CGFloat orignSkewY = skewY_;
	
	// reset values
	self.positionInPixels = anchorPointInPixels_;
	self.rotation = 0.0f;
	self.scaleX   = 1.0f;
	self.scaleY   = 1.0f;
	self.skewX    = 0.0f;
	self.skewY    = 0.0f;
	
	[self readPixels:rect buffer:buffer];
	
	// restore orign values
	self.skewY = orignSkewY;
	self.skewX = orignSkewX;
	self.scaleY = orignScaleY;
	self.scaleX = orignScaleX;
	self.rotation = orignRotation;
	self.positionInPixels = orignPosition;
}



- (ccColor4B) readPixel:(CGPoint)point
{
	CGRect rect = CGRectMake(point.x, point.y, 1.0f, 1.0f);
	ccColor4B buffer = ccc4(0, 0, 0, 0);
	[self readPixels:rect buffer:&buffer];
	return buffer;
}

- (ccColor4B) resetAndReadPixel:(CGPoint)point
{
	CGRect rect = CGRectMake(point.x, point.y, 1.0f, 1.0f);
	ccColor4B buffer = ccc4(0, 0, 0, 0);
	[self resetAndReadPixels:rect buffer:&buffer];
	return buffer;
}

#pragma mark UIImage

- (UIImage *) getUIImage
{
	if (contentSizeInPixels_.width <= 0 || contentSizeInPixels_.height <= 0)
	{
		return nil;
	}
	
	CGRect rect = CGRectMake(0, 0, contentSizeInPixels_.width, contentSizeInPixels_.height);
	return [self getUIImageInRect:rect];
}

- (UIImage *) getUIImageInRect:(CGRect)rect
{
	int tx = rect.size.width;
	int ty = rect.size.height;
	
	int bitsPerComponent = 8 * sizeof(GLubyte);
	int bytesPerPixel    = sizeof(ccColor4B);
	int bitsPerPixel     = bitsPerComponent * bytesPerPixel;
	int bytesPerRow      = bytesPerPixel * tx;
	NSInteger bufferLen  = bytesPerRow * ty;
	
	ccColor4B * buffer   = malloc(bufferLen);
	ccColor4B * pixels   = malloc(bufferLen);	// mirror
	
	if (!buffer || !pixels)
	{
		CNLog(@"not enough memory!");
		free(buffer);
		free(pixels);
		return nil;
	}
	bzero(buffer, bufferLen);
	bzero(pixels, bufferLen);
	
	// read origin pixels in rect
	[self resetAndReadPixels:rect buffer:buffer];
	
	// make data provider with data.
	CGBitmapInfo bitmapInfo	= kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault;
	CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLen, NULL);
	CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
	CGImageRef iref	= CGImageCreate(tx, ty,
									bitsPerComponent, bitsPerPixel, bytesPerRow,
									colorSpaceRef, bitmapInfo, provider,
									NULL, false,
									kCGRenderingIntentDefault);
	
	CGContextRef context = CGBitmapContextCreate(pixels, tx, ty,
												 CGImageGetBitsPerComponent(iref),
												 CGImageGetBytesPerRow(iref),
												 CGImageGetColorSpace(iref),
												 bitmapInfo);
	CGContextTranslateCTM(context, 0.0f, ty);
	CGContextScaleCTM(context, 1.0f, -1.0f);
	CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, tx, ty), iref);
	CGImageRef outputRef = CGBitmapContextCreateImage(context);
	UIImage * image	= [[UIImage alloc] initWithCGImage:outputRef];
	
	CGImageRelease(iref);
	CGContextRelease(context);
	CGColorSpaceRelease(colorSpaceRef);
	CGDataProviderRelease(provider);
	CGImageRelease(outputRef);
	
	free(pixels);
	free(buffer);
	
	return [image autorelease];
}

@end

