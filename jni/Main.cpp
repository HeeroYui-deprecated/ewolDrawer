/**
 *******************************************************************************
 * @file Main.cpp
 * @brief main fonction
 * @author Edouard DUPIN
 * @date 13/10/2011
 * @par Project
 * ewol 
 *
 * @par Copyright
 * Copyright 2011 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */


#include <ewol/ewol.h>
#include <ewol/Font.h>
#include <ewol/themeManager.h>
#include <ewol/widget/Button.h>
#include <ewol/widget/CheckBox.h>
#include <ewol/widget/SizerHori.h>
#include <ewol/widget/SizerVert.h>
#include <ewol/widget/Test.h>
#include <ewol/widget/Label.h>
#include <ewol/widget/Entry.h>
#include <ewol/widget/List.h>

#include <Debug.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// need to run xcompmgr to have transparency


class MaListExemple : public ewol::List
{
	public:
		MaListExemple(void) { };
		~MaListExemple(void) { };
		virtual color_ts GetBasicBG(void) {
			color_ts bg;
			bg.red = 1.0;
			bg.green = 0.0;
			bg.blue = 0.0;
			bg.alpha = 1.0;
			return bg;
		}
		
		uint32_t GetNuberOfColomn(void) {
			return 1;
		};
		bool GetTitle(int32_t colomn, etk::String &myTitle, color_ts &fg, color_ts &bg) {
			myTitle = "title";
			return true;
		};
		uint32_t GetNuberOfRaw(void) {
			return 3;
		};
		bool GetElement(int32_t colomn, int32_t raw, etk::String &myTextToWrite, color_ts &fg, color_ts &bg) {
			switch (raw) {
				case 0:
					myTextToWrite = "Ligne 1";
					break;
				case 1:
					myTextToWrite = "ma ligne 2";
					break;
				case 2:
					myTextToWrite = "ma ligne 3";
					break;
				default:
					myTextToWrite = "ERROR";
					break;
			}
			fg.red = 0.0;
			fg.green = 0.0;
			fg.blue = 0.0;
			fg.alpha = 1.0;
			if (raw % 2) {
				bg.red = 1.0;
				bg.green = 1.0;
				bg.blue = 1.0;
				bg.alpha = 1.0;
			} else {
				bg.red = 0.5;
				bg.green = 0.5;
				bg.blue = 0.5;
				bg.alpha = 1.0;
			}
			return true;
		};
		
		bool OnItemEvent(int32_t IdInput, ewol::eventInputType_te typeEvent, int32_t colomn, int32_t raw, etkFloat_t x, etkFloat_t y) {
			if (typeEvent == ewol::EVENT_INPUT_TYPE_SINGLE) {
				DRAW_INFO("Event on List : IdInput=" << IdInput << " colomn=" << colomn << " raw=" << raw );
			}
			return false;
		}
	
};




class Plop :public ewol::Windows
{
	public:
		Plop(void)
		{
			// generate the display : 
			ewol::SizerHori * mySizer = new ewol::SizerHori();
			SetSubWidget(mySizer);
			
			
			MaListExemple * myList = new MaListExemple();
			//myList->SetExpendX(true);
			myList->SetExpendY(true);
			myList->SetFillY(true);
			mySizer->SubWidgetAdd(myList);
			
			ewol::SizerVert * mySizerVert = new ewol::SizerVert();
			mySizer->SubWidgetAdd(mySizerVert);
			
			ewol::Button * myButton = new ewol::Button("LB");
			mySizerVert->SubWidgetAdd(myButton);
			
			ewol::Entry * myEntry = new ewol::Entry("basic Text");
			myEntry->SetWidth(120);
			mySizerVert->SubWidgetAdd(myEntry);
			
			ewol::Label * myLabel = new ewol::Label("Mon label");
			myLabel->SetExpendY(true);
			myLabel->SetFillY(true);
			mySizerVert->SubWidgetAdd(myLabel);
			
			mySizerVert = new ewol::SizerVert();
			mySizer->SubWidgetAdd(mySizerVert);
			
			myEntry = new ewol::Entry("Mega super plop");
			//myEntry->SetExpendY(true);
			//myEntry->SetFillY(true);
			//myEntry->SetExpendX(true);
			myEntry->SetFillX(true);
			myEntry->SetWidth(120);
			mySizerVert->SubWidgetAdd(myEntry);
			
			
			myButton = new ewol::Button("BT 3");
			myButton->SetExpendX(true);
			//myButton->SetExpendY(true);
			myButton->SetFillX(true);
			mySizerVert->SubWidgetAdd(myButton);
			
			ewol::Test * myTest = new ewol::Test();
			mySizerVert->SubWidgetAdd(myTest);
			
			ewol::CheckBox * myCheckBox = new ewol::CheckBox("mon label d'eK");
			mySizerVert->SubWidgetAdd(myCheckBox);
			myCheckBox = new ewol::CheckBox("Exemple 2");
			mySizerVert->SubWidgetAdd(myCheckBox);
			myCheckBox = new ewol::CheckBox("Exemple 3 et ��$");
			mySizerVert->SubWidgetAdd(myCheckBox);
			
			myButton = new ewol::Button("4 4 BT");
			myButton->SetFillX(true);
			myButton->SetFillY(true);
			myButton->SetExpendY(true);
			mySizerVert->SubWidgetAdd(myButton);
			
		};
		
		~Plop(void)
		{
			
		};
};

static Plop * myWindowsExample = NULL;

/**
 * @brief main application function Initialisation
 */
void APP_Init(int argc, char *argv[])
{
	ewol::ChangeSize(800, 600);
	/*
	if (true == ewol::AddFont("dataTest/TextMonospace.ebt", true, true, true) ) {
		//fontID = GetFontIdWithFileName("dataTest/TextMonospace.ebt");
	}
	*/
	
	// set the default Path of the application : 
	#ifdef PLATFORM_Linux
		etk::String homedir;
		#ifdef NDEBUG
			homedir = "/usr/share/"PROJECT_NAME"/";
		#else
			char cCurrentPath[FILENAME_MAX];
			if (!getcwd(cCurrentPath, FILENAME_MAX)) {
				homedir = "./assets/";
			} else {
				cCurrentPath[FILENAME_MAX - 1] = '\0';
				homedir = cCurrentPath;
				homedir += "/assets/";
			}
		#endif
		SetBaseFolderData(homedir.c_str());
		SetBaseFolderDataUser("~/."PROJECT_NAME"/");
		SetBaseFolderCache("/tmp/"PROJECT_NAME"/");
	#endif
	
	ewol::SetFontFolder("Font");
	#ifdef EWOL_USE_FREE_TYPE
		ewol::SetDefaultFont("freefont/FreeMono", 14);
	#else
		//ewol::SetDefaultFont("ebtfont/Monospace", 14);
		ewol::SetDefaultFont("ebtfont/Monospace", 22);
	#endif
	//ewol::theme::LoadDefault("dataTest/exemple.eol");
	/*
	etk::File fileTmp("exemple.eol", etk::FILE_TYPE_DATA);
	ewol::theme::LoadDefault(fileTmp);
	*/
	/*
	etk::File tmpFile("/data/data/com.example.EwolActivity.app/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile = ("/data/data/com.example.EwolActivity/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/com.example.EwolActivity.app/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/com.example.EwolActivity/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/data/com.example.ewolactivity.app/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/data/com.example.ewolactivity/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/com.example.ewolactivity.app/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	tmpFile=("/data/com.example.ewolactivity/assets/theme/exemple.eol");
	if (tmpFile.Exist() ) {
		EWOL_WARNING("file existed : " << tmpFile);
	}
	*/
	
	
	myWindowsExample = new Plop();
	
	
	// create the specific windows
	ewol::DisplayWindows(myWindowsExample);
}

/**
 * @brief main application function Un-Initialisation
 */
void APP_UnInit(void)
{
	delete(myWindowsExample);
}
