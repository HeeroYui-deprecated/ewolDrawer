
PROJECT_PATH=$(shell pwd)
PROJECT_NDK=$(PROJECT_PATH)/../android/ndk-r7/
PROJECT_SDK=$(PROJECT_PATH)/../android/sdk-r15/
PROJECT_MODULE=$(PROJECT_PATH)/../
EWOL_FOLDER=$(PROJECT_MODULE)ewol


#PROJECT_VENDOR=heeroyui
#PROJECT_NAME=ewoldrawer
PROJECT_VENDOR=example
PROJECT_NAME=EwolActivity
JAVA_FOLDER=src/com/$(PROJECT_VENDOR)/$(PROJECT_NAME)


all:
	cd $(PROJECT_NDK) ; NDK_PROJECT_PATH=$(PROJECT_PATH) NDK_MODULE_PATH=$(PROJECT_MODULE) ./ndk-build
	# Clear previous sources
	rm -rf src
	# Create folder
	mkdir -p $(JAVA_FOLDER)/
	# copy the java File : 
	cp $(EWOL_FOLDER)/SourcesJava/PROJECT_NAME.java $(JAVA_FOLDER)/$(PROJECT_NAME).java
	
	sed -i "s|__PROJECT_VENDOR__|$(PROJECT_VENDOR)|" $(JAVA_FOLDER)/$(PROJECT_NAME).java
	sed -i "s|__PROJECT_NAME__|$(PROJECT_NAME)|" $(JAVA_FOLDER)/$(PROJECT_NAME).java
	
	PATH=$(PROJECT_SDK)/tools/:$(PROJECT_SDK)/platform-tools/:$(PATH) ant -Dsdk.dir=$(PROJECT_SDK) debug
	rm -rf src
	

install: all
	#$(PROJECT_SDK)/platform-tools/adb kill-server
	# install application
	sudo $(PROJECT_SDK)/platform-tools/adb  install -r ./bin/EwolActivity-debug.apk

clean:
	rm -rf bin libs gen obj
