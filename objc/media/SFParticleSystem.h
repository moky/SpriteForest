//
//  SFParticleSystem.h
//  SpriteForest
//
//  Created by Moky on 11-12-26.
//  Copyright 2011 Slanissue.com. All rights reserved.
//

#import "coconut2d.h"


#ifndef ARCH_OPTIMAL_PARTICLE_SYSTEM
// build each architecture with the optimal particle system

// ARMv7, Mac or Simulator use "Quad" particle
#if defined(__ARM_NEON__) || defined(__MAC_OS_X_VERSION_MAX_ALLOWED) || TARGET_IPHONE_SIMULATOR
#define ARCH_OPTIMAL_PARTICLE_SYSTEM CCParticleSystemQuad

// ARMv6 use "Point" particle
#elif __arm__
#define ARCH_OPTIMAL_PARTICLE_SYSTEM CCParticleSystemPoint
#else
#error(unknown architecture)
#endif

#endif


@interface SFParticleSystem : ARCH_OPTIMAL_PARTICLE_SYSTEM

+ (id) particle:(NSDictionary *)dict;
- (id) init:(NSDictionary *)dict;

- (void) runWithNode:(CCNode *)node;

@end
