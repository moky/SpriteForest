LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := coconut2dx_static

LOCAL_MODULE_FILENAME := libcoconut2dx

LOCAL_SRC_FILES := coconut2d.cpp \
					CNDirector.cpp \
					CNNode.cpp \
					CNScene.cpp \
					\
					cocoa/CNString.cpp \
					cocoa/CNDictionary.cpp \
					cocoa/CNArray.cpp \
					cocoa/CNRuntimeClass.cpp \
					cocoa/CNClient.cpp \
					cocoa/android/CNFileManager.cpp \
					cocoa/android/CNClient.cpp \
					\
					actions/CCMask.cpp \
					\
					controllers/CNTouchController.cpp \
					controllers/CNScrollLayerController.cpp \
					\
					sprites/CNSprite.cpp \
					sprites/CNSpriteBatchNode.cpp \
					sprites/CNLabel.cpp \
					\
					layers/CNLayer.cpp \
					layers/CNFiniteLayer.cpp \
					layers/CNScrollLayer.cpp \
					\
					sfc/CNSpriteFrameData.cpp \
					sfc/CNSpriteFrameDataReader.cpp \
					sfc/CNSpriteFrameDataTransformer.cpp \
					sfc/CNSpriteFrameCache.cpp \
					\
					data/CNData.cpp \
					data/CNDataReader.cpp \
					data/CNDataTransformer.cpp 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)
