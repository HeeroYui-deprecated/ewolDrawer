
PROJECT_PATH=$(shell pwd)
PROJECT_NDK=$(PROJECT_PATH)/../android/ndk-r7/
PROJECT_SDK=$(PROJECT_PATH)/../android/sdk-r15/
PROJECT_MODULE=$(PROJECT_PATH)/../
EWOL_FOLDER=$(PROJECT_MODULE)ewol


PROJECT_VENDOR=heeroyui
PROJECT_NAME=ewoldrawer
PROJECT_PACKAGE=ewoldrawerpackage
JAVA_FOLDER=src/com/$(PROJECT_VENDOR)/$(PROJECT_NAME)


all:
	# Clear previous sources
	rm -rf src
	# Create folder
	mkdir -p $(JAVA_FOLDER)/
	# copy the java File : 
	cp $(EWOL_FOLDER)/SourcesJava/PROJECT_NAME.java $(JAVA_FOLDER)/$(PROJECT_NAME).java
	
	sed -i "s|__PROJECT_VENDOR__|$(PROJECT_VENDOR)|" $(JAVA_FOLDER)/$(PROJECT_NAME).java
	sed -i "s|__PROJECT_NAME__|$(PROJECT_NAME)|" $(JAVA_FOLDER)/$(PROJECT_NAME).java
	sed -i "s|__PROJECT_PACKAGE__|$(PROJECT_PACKAGE)|" $(JAVA_FOLDER)/$(PROJECT_NAME).java
	
	cp $(EWOL_FOLDER)/SourcesJava/ewolAndroidAbstraction.cpp jni/
	sed -i "s|__PROJECT_VENDOR__|$(PROJECT_VENDOR)|" jni/ewolAndroidAbstraction.cpp
	sed -i "s|__PROJECT_NAME__|$(PROJECT_NAME)|" jni/ewolAndroidAbstraction.cpp
	sed -i "s|__PROJECT_PACKAGE__|$(PROJECT_PACKAGE)|" jni/ewolAndroidAbstraction.cpp
	
	#build native code
	cd $(PROJECT_NDK) ; NDK_PROJECT_PATH=$(PROJECT_PATH) NDK_MODULE_PATH=$(PROJECT_MODULE) ./ndk-build
	#build java CODE : 
	PATH=$(PROJECT_SDK)/tools/:$(PROJECT_SDK)/platform-tools/:$(PATH) ant -Dsdk.dir=$(PROJECT_SDK) debug
	rm -rf src
	rm -f  jni/ewolAndroidAbstraction.cpp

install: all
	#$(PROJECT_SDK)/platform-tools/adb kill-server
	# install application
	sudo $(PROJECT_SDK)/platform-tools/adb  install -r ./bin/EwolActivity-debug.apk

clean:
	rm -rf bin libs gen obj
