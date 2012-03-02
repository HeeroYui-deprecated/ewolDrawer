LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ewolDrawer
LOCAL_STATIC_LIBRARIES := ewol etk tinyxml libzip libpng libfreetype


# load the common sources file of the platform
include $(LOCAL_PATH)/file.mk

LOCAL_SRC_FILES := $(FILE_LIST)
LOCAL_LDLIBS    := 

LOCAL_CFLAGS    :=	-D__PLATFORM__Linux \
                    -DEWOL_USE_FREE_TYPE \
                    -DDRAW_DEBUG_LEVEL=3

include $(BUILD_EXECUTABLE)

NDK_MODULE_PATH := $(LOCAL_PATH)/../../


$(call import-module,ewol/Sources)
