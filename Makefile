
PROJECT_PATH=$(shell pwd)
PROJECT_NDK=$(PROJECT_PATH)/../android/ndk-r7/
PROJECT_SDK=$(PROJECT_PATH)/../android/sdk-r15/
PROJECT_MODULE=$(PROJECT_PATH)/../
EWOL_FOLDER=$(PROJECT_MODULE)ewol

all:
	cd $(PROJECT_NDK) ; NDK_PROJECT_PATH=$(PROJECT_PATH) NDK_MODULE_PATH=$(PROJECT_MODULE) ./ndk-build
	cp -rvf $(EWOL_FOLDER)/src .
	PATH=$(PROJECT_SDK)/tools/:$(PROJECT_SDK)/platform-tools/:$(PATH) ant -Dsdk.dir=$(PROJECT_SDK) debug
	rm -rf src
	

install: all
	#$(PROJECT_SDK)/platform-tools/adb kill-server
	# install application
	sudo $(PROJECT_SDK)/platform-tools/adb  install -r ./bin/EwolActivity-debug.apk

clean:
	rm -r bin libs gen obj
