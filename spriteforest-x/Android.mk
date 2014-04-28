LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := spriteforestx_static

LOCAL_MODULE_FILENAME := libspriteforestx

LOCAL_SRC_FILES := spriteforest.cpp \
					\
					base/SFNode.cpp \
					base/SFSprite.cpp \
					base/SFLayer.cpp \
					base/SFScene.cpp \
					base/SFForest.cpp \
					base/SFEventHandler.cpp \
					base/SFNodeFileParser.cpp \
					base/SFLord.cpp \
					\
					action/CCActionMagic.cpp \
					action/CCActionMagicSlow.cpp \
					action/SFAction.cpp \
					action/SFActionInstant.cpp \
					action/SFActionInterval.cpp \
					action/SFActionEase.cpp \
					action/SFActionMagic.cpp \
					action/SFAnimation.cpp \
					\
					extension/SFSpriteBatchNode.cpp \
					extension/SFTouchSprite.cpp \
					extension/SFDragSprite.cpp \
					extension/SFFiniteLayer.cpp \
					extension/SFScrollLayer.cpp \
					extension/SFProgressTimer.cpp \
					extension/SFTextSprite.cpp \
					\
					media/android/SFWebBrowser.cpp \
					media/android/SFVideo.cpp \
					media/SFAudio.cpp \
					media/SFVideo.cpp \
					media/SFParticleSystem.cpp \
					\
					transition/SFTransitionScene.cpp 


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_WHOLE_STATIC_LIBRARIES := cocosdenshion_static coconut2dx_static

include $(BUILD_STATIC_LIBRARY)
