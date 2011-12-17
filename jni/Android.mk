LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ewoldrawerpackage
LOCAL_STATIC_LIBRARIES := ewol

LOCAL_SRC_FILES := ewolAndroidAbstraction.cpp \
                   Main.cpp
LOCAL_LDLIBS    := -llog -landroid

#LOCAL_STATIC_JAVA_LIBRARIES := ewol
#LOCAL_JAVA_RESOURCE_DIRS := $(LOCAL_PATH)/../ewol

include $(BUILD_SHARED_LIBRARY)

NDK_MODULE_PATH := $(LOCAL_PATH)/../../

$(call import-module,ewol/jni)
