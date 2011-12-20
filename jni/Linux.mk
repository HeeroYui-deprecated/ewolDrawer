LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ewoldrawerpackage
LOCAL_STATIC_LIBRARIES := ewol


# load the common sources file of the platform
include $(LOCAL_PATH)/file.mk

LOCAL_SRC_FILES := $(FILE_LIST)
LOCAL_LDLIBS    := 

$(info ====> MAIN FILE : include Executable ...)
include $(BUILD_EXECUTABLE)

NDK_MODULE_PATH := $(LOCAL_PATH)/../../

$(info ====> Module Path:$(NDK_MODULE_PATH) ... ==> import sub modules ...)



$(call import-module,ewol/Sources)
