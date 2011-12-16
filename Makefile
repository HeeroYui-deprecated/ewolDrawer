
###############################################################################
### Some Preject properties :                                               ###
###############################################################################

PROJECT_PATH=$(shell pwd)
PROJECT_NDK?=$(PROJECT_PATH)/../android/ndk-r7/
PROJECT_SDK?=$(PROJECT_PATH)/../android/sdk-r15/

PROJECT_MODULE?=$(PROJECT_PATH)/../

EWOL_FOLDER=$(PROJECT_MODULE)ewol

# group name or constructor ... (no dot, no MAJ no Numerical char)
PROJECT_VENDOR=heeroyui
# Binary name ... (no dot, no MAJ no Numerical char)
PROJECT_NAME=ewoldrawer

#dependence of the librairies : 
#PROJECT_LIB_DEPENDENCY= ewol

PROJECT_FILE_DIRECTORY=jni

# get the tag of the current project : 
PROJECT_VERSION_TAG=$(shell git describe --tags)
#$(info Project version TAG : $(PROJECT_VERSION_TAG))

PROJECT_VERSION_TAG_SHORT=$(shell git describe --tags --abbrev=0)
#$(info Project version TAG Short: $(PROJECT_VERSION_TAG_SHORT))

# enable or disable debug :
DEBUG:=1

###############################################################################
### Compilation Define                                                      ###
###############################################################################
ifeq ("$(DEBUG)", "0")
    PROJECT_CXXFLAGS = -DPROJECT_DEBUG_LEVEL=1
    PROJECT_CXXFLAGS+= -DPROJECT_NDEBUG
    PROJECT_CXXFLAGS+= -DPROJECT_VERSION_TAG_NAME="\"$(VERSION_TAG)-release\""
else
    PROJECT_CXXFLAGS = -DPROJECT_DEBUG_LEVEL=3
    PROJECT_CXXFLAGS+= -DPROJECT_VERSION_TAG_NAME="\"$(VERSION_TAG)-debug\""
endif
PROJECT_CXXFLAGS+= -DPROJECT_VERSION_BUILD_TIME="\"$(VERSION_BUILD_TIME)\""

PROJECT_CXXFLAGS+= -I$(EWOL_FOLDER)/Sources/

PROJECT_LDFLAGS= -L$(EWOL_FOLDER)

PROJECT_SOURCES= jni/ewolAndroidAbstraction.cpp \
                 jni/Main.cpp

PROJECT_SOURCES= Main.cpp

#include the specific platefom makefile
include $(EWOL_FOLDER)/Build/Makefile.$(PLATFORM).mk


