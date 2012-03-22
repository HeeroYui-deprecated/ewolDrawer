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
#include <ewol/widget/ButtonColor.h>
#include <ewol/widget/CheckBox.h>
#include <ewol/widget/SizerHori.h>
#include <ewol/widget/SizerVert.h>
#include <ewol/widget/Label.h>
#include <ewol/widget/Entry.h>
#include <ewol/widget/List.h>
#include <ewol/widget/PopUp.h>
#include <ewol/widget/Spacer.h>
#include <ewol/widget/ColorBar.h>
#include <ewol/widget/Menu.h>
#include <ewol/widget/widgetE2D.h>
#include <ewol/widgetMeta/FileChooser.h>
#include <ewol/WidgetManager.h>
#include <parserSVG/parserSVG.h>
#include <globalMsg.h>
#include <widgetDrawer.h>
#include <elementManager.h>

#include <Debug.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// need to run xcompmgr to have transparency


class MaListExemple : public ewol::List
{
	private:
		
	public:
		MaListExemple(void) {
			RegisterMultiCast(drawMsgListElementChange);
		};
		~MaListExemple(void) { };
		
		uint32_t GetNuberOfColomn(void) {
			return 1;
		};
		bool GetTitle(int32_t colomn, etk::UString &myTitle, color_ts &fg, color_ts &bg) {
			myTitle = "title";
			return true;
		};
		uint32_t GetNuberOfRaw(void) {
			return drawElement::Size();
		};
		bool GetElement(int32_t colomn, int32_t raw, etk::UString &myTextToWrite, color_ts &fg, color_ts &bg) {
			int32_t idSelected = drawElement::SelectGet();
			drawElement::Base* elementLocal = drawElement::Get(raw);
			myTextToWrite  = "[";
			myTextToWrite += raw;
			myTextToWrite += "] ";
			if (NULL == elementLocal) {
				myTextToWrite += "????";
			} else {
				myTextToWrite += elementLocal->GetTypeChar();
				myTextToWrite += "-";
				myTextToWrite += elementLocal->GetName();
			}
			fg.red = 0.0;
			fg.green = 0.0;
			fg.blue = 0.0;
			fg.alpha = 1.0;
			if (raw == idSelected) {
				bg.red = 0.5;
				bg.green = 0.5;
				bg.blue = 1.0;
				bg.alpha = 1.0;
			} else if (raw % 2) {
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
			if (IdInput==1 && typeEvent == ewol::EVENT_INPUT_TYPE_SINGLE) {
				DRAW_INFO("Event on List : IdInput=" << IdInput << " colomn=" << colomn << " raw=" << raw );
				drawElement::SelectSet(raw);
			}
			return false;
		}
		/**
		 * @brief Receive a message from an other EObject with a specific eventId and data
		 * @param[in] CallerObject Pointer on the EObject that information came from
		 * @param[in] eventId Message registered by this class
		 * @param[in] data Data registered by this class
		 * @return ---
		 */
		virtual void OnReceiveMessage(ewol::EObject * CallerObject, const char * eventId, etk::UString data)
		{
			if (eventId == drawMsgListElementChange) {
				MarkToReedraw();
			}
		}
};






const char * const drawerEventRequestOpenFileClosed   = "Drawer Close Open File";
const char * const drawerEventRequestOpenFileSelected = "Drawer Open Selected File";
const char * const drawerEventRequestSaveFileSelected = "Drawer Save Selected File";

const char * const drawerEventColorHasChange = "Drawer-select-color-change";
const char * const TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN = "MainWindows";
class MainWindows :public ewol::Windows
{
	private:
		widgetDrawer* m_drawer;
	public:
		MainWindows(void)
		{
			ewol::SizerVert * mySizerVert = new ewol::SizerVert();
			SetSubWidget(mySizerVert);
				ewol::Menu * myMenu = new ewol::Menu();
				mySizerVert->SubWidgetAdd(myMenu);
				int32_t idMenuFile = myMenu->AddTitle("File");
					(void)myMenu->Add(idMenuFile, "New", "", drawMsgGuiNew);
					(void)myMenu->AddSpacer();
					(void)myMenu->Add(idMenuFile, "Open", "", drawMsgGuiOpen);
					(void)myMenu->Add(idMenuFile, "Close", "", drawMsgGuiClose);
					(void)myMenu->Add(idMenuFile, "Save", "", drawMsgGuiSave);
					(void)myMenu->Add(idMenuFile, "Save As ...", "", drawMsgGuiSaveAs);
					(void)myMenu->AddSpacer();
				/*
				int32_t idMenuEdit = myMenu->AddTitle("Edit");
					(void)myMenu->Add(idMenuEdit, "Undo", "", drawMsgGuiUndo);
					(void)myMenu->Add(idMenuEdit, "Redo", "", drawMsgGuiRedo);
				*/
				int32_t idMenuElement = myMenu->AddTitle("Element");
					(void)myMenu->Add(idMenuElement, "new mesh",          "", drawMsgGuiElementNewMesh);
					(void)myMenu->Add(idMenuElement, "new circle",        "", drawMsgGuiElementNewCircle);
					(void)myMenu->Add(idMenuElement, "new disk",          "", drawMsgGuiElementNewDisk);
					(void)myMenu->Add(idMenuElement, "new rectangle",     "", drawMsgGuiElementNewRectangle);
					(void)myMenu->Add(idMenuElement, "new polygone",      "", drawMsgGuiElementNewPolygone);
					(void)myMenu->Add(idMenuElement, "Remove",            "", drawMsgGuiElementRemove);
					(void)myMenu->Add(idMenuElement, "hide/show",         "", drawMsgGuiElementHideShow);
				
			// generate the display : 
			ewol::SizerHori * mySizer = new ewol::SizerHori();
			mySizerVert->SubWidgetAdd(mySizer);
			
			ewol::SizerVert * mySizerVert2 = new ewol::SizerVert();
			mySizer->SubWidgetAdd(mySizerVert2);
			
			MaListExemple * myList = new MaListExemple();
			//myList->SetExpendX(true);
			myList->SetExpendY(true);
			myList->SetFillY(true);
			mySizerVert2->SubWidgetAdd(myList);
			
			
			ewol::ButtonColor * mybtColor = new ewol::ButtonColor();
			mybtColor->SetFillX(true);
			color_ts tmpColor;
			tmpColor.red   = 1.0;
			tmpColor.green = 0.0;
			tmpColor.blue  = 0.0;
			tmpColor.alpha = 1.0;
			mybtColor->SetCurrentColor(tmpColor);
			mybtColor->RegisterOnEvent(this, ewolEventButtonColorChange, drawerEventColorHasChange);
			mySizerVert2->SubWidgetAdd(mybtColor);
			
			
			etk::File fileE2D("/home/edupin/progperso/ewolDrawer/Exemple.xml");
			ewol::widgetE2D * myE2Dwidget = new ewol::widgetE2D();
			myE2Dwidget->SetElement(fileE2D);
			myE2Dwidget->SetMinSize(120,120);
			myE2Dwidget->SetFillX(true);
			mySizerVert2->SubWidgetAdd(myE2Dwidget);
			
			
			mybtColor = new ewol::ButtonColor();
			mybtColor->SetFillX(true);
			tmpColor.red   = 0.0;
			tmpColor.green = 1.0;
			tmpColor.blue  = 0.0;
			tmpColor.alpha = 1.0;
			mybtColor->SetCurrentColor(tmpColor);
			mySizerVert2->SubWidgetAdd(mybtColor);
			
			mybtColor = new ewol::ButtonColor();
			mybtColor->SetFillX(true);
			tmpColor.red   = 0.0;
			tmpColor.green = 0.0;
			tmpColor.blue  = 1.0;
			tmpColor.alpha = 1.0;
			mybtColor->SetCurrentColor(tmpColor);
			mySizerVert2->SubWidgetAdd(mybtColor);
			
			m_drawer = new widgetDrawer();
			m_drawer->SetFontSize(11);
			m_drawer->SetFontNameNormal("freefont/FreeSerif.ttf");
			m_drawer->SetExpendX(true);
			m_drawer->SetExpendY(true);
			m_drawer->SetFillX(true);
			m_drawer->SetFillY(true);
			mySizer->SubWidgetAdd(m_drawer);
			
			RegisterMultiCast(drawMsgGuiOpen);
			RegisterMultiCast(drawMsgGuiSave);
			RegisterMultiCast(drawMsgGuiElementNewMesh);
			RegisterMultiCast(drawMsgGuiElementNewCircle);
			RegisterMultiCast(drawMsgGuiElementNewDisk);
			RegisterMultiCast(drawMsgGuiElementNewRectangle);
			RegisterMultiCast(drawMsgGuiElementNewPolygone);
			RegisterMultiCast(drawMsgGuiElementRemove);
			RegisterMultiCast(drawMsgGuiElementHideShow);
		};
		
		~MainWindows(void)
		{
			
		};
		
		
		/**
		 * @brief Receive a message from an other EObject with a specific eventId and data
		 * @param[in] CallerObject Pointer on the EObject that information came from
		 * @param[in] eventId Message registered by this class
		 * @param[in] data Data registered by this class
		 * @return ---
		 */
		virtual void OnReceiveMessage(ewol::EObject * CallerObject, const char * eventId, etk::UString data)
		{
			ewol::Windows::OnReceiveMessage(CallerObject, eventId, data);
			
			DRAW_INFO("Receive Event from the main windows ... : widgetid=" << CallerObject << " ==> " << eventId << " ==> data=\"" << data << "\"" );
			if (eventId == drawMsgGuiOpen) {
				ewol::FileChooser* tmpWidget = new ewol::FileChooser();
				tmpWidget->SetTitle("Open Files ...");
				tmpWidget->SetValidateLabel("Open");
				PopUpWidgetPush(tmpWidget);
				tmpWidget->RegisterOnEvent(this, ewolEventFileChooserValidate, drawerEventRequestOpenFileSelected);
			} else if (eventId == drawerEventRequestOpenFileSelected) {
				// get widget:
				ewol::FileChooser * tmpWidget = EWOL_CAST_WIDGET_FILE_CHOOSER(CallerObject);
				if (NULL == tmpWidget) {
					DRAW_ERROR("impossible to get pop_upWidget " << CallerObject);
					return;
				}
				// get the filename : 
				etk::UString tmpData = tmpWidget->GetCompleateFileName();
				DRAW_DEBUG("Request opening the file : " << tmpData);
				if (NULL != m_drawer) {
					//m_drawer->Load(tmpData);
				}
			} else if (eventId == drawMsgGuiSave) {
				if (NULL != m_drawer) {
					/*
					if (m_drawer->HasName()) {
						m_drawer->Save();
					} else {
						ewol::FileChooser* tmpWidget = new ewol::FileChooser();
						tmpWidget->SetTitle("Save Files ...");
						tmpWidget->SetValidateLabel("Save");
						PopUpWidgetPush(tmpWidget);
						tmpWidget->RegisterOnEvent(this, ewolEventFileChooserValidate, drawerEventRequestSaveFileSelected);
					}
					*/
				}
			} else if (eventId == drawerEventRequestSaveFileSelected) {
				// get widget:
				ewol::FileChooser * tmpWidget = EWOL_CAST_WIDGET_FILE_CHOOSER(CallerObject);
				if (NULL == tmpWidget) {
					DRAW_ERROR("impossible to get pop_upWidget " << CallerObject);
					return;
				}
				// get the filename : 
				etk::UString tmpData = tmpWidget->GetCompleateFileName();
				DRAW_DEBUG("Request opening the file : " << tmpData);
				if (NULL != m_drawer) {
					/*
					m_drawer->SetFilename(tmpData);
					m_drawer->Save();
					*/
				}
			} else if (eventId == drawerEventColorHasChange) {
				// the button color has change ==> we really change the current color ...
				if (NULL != CallerObject) {
					ewol::ButtonColor * tmpColorButton = EWOL_CAST_WIDGET_BUTTON_COLOR(CallerObject);
					if (NULL != tmpColorButton) {
						color_ts tmpColor = tmpColorButton->GetCurrentColor();
						if (NULL != m_drawer) {
							m_drawer->SetColorOnSelected(tmpColor);
						}
					}
				}
			} else if (eventId == drawMsgGuiElementNewMesh) {
				drawElement::Add(drawElement::DRAW_ELEMENT_TYPE_MESH);
			} else if (eventId == drawMsgGuiElementNewCircle) {
				drawElement::Add(drawElement::DRAW_ELEMENT_TYPE_CIRCLE);
			} else if (eventId == drawMsgGuiElementNewDisk) {
				drawElement::Add(drawElement::DRAW_ELEMENT_TYPE_DISK);
			} else if (eventId == drawMsgGuiElementNewRectangle) {
				drawElement::Add(drawElement::DRAW_ELEMENT_TYPE_RECTANGLE);
			} else if (eventId == drawMsgGuiElementNewPolygone) {
				drawElement::Add(drawElement::DRAW_ELEMENT_TYPE_POLYGONE);
			}
			return;
		};
		/**
		 * @brief Inform object that an other object is removed ...
		 * @param[in] removeObject Pointer on the EObject remeved ==> the user must remove all reference on this EObject
		 * @note : Sub classes must call this class
		 * @return ---
		 */
		virtual void OnObjectRemove(ewol::EObject * removeObject)
		{
			ewol::Windows::OnObjectRemove(removeObject);
			
			if (removeObject == m_drawer) {
				m_drawer = NULL;
				m_needFlipFlop = true;
			}
		}
	public:
		/**
		 * @brief Check if the object has the specific type.
		 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
		 * @param[in] objectType type of the object we want to check
		 * @return true if the object is compatible, otherwise false
		 */
		bool CheckObjectType(const char * const objectType)
		{
			if (NULL == objectType) {
				EWOL_ERROR("check error : \"" << TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN << "\" != NULL(pointer) ");
				return false;
			}
			if (objectType == TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN) {
				return true;
			} else {
				if(true == ewol::Windows::CheckObjectType(objectType)) {
					return true;
				}
				EWOL_ERROR("check error : \"" << TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN << "\" != \"" << objectType << "\"");
				return false;
			}
		}
		
		/**
		 * @brief Get the current Object type of the EObject
		 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
		 * @param[in] objectType type description
		 * @return true if the object is compatible, otherwise false
		 */
		const char * const GetObjectType(void)
		{
			return TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN;
		}
};

#define DRAW_CAST_WINDOWS_MAIN(curentPointer) EWOL_CAST(TYPE_EOBJECT_WIDGET_DRAW_WINDOWS_MAIN,widgetDrawer,curentPointer)


static MainWindows * basicWindows = NULL;

/**
 * @brief main application function Initialisation
 */
void APP_Init(void)
{
	DRAW_INFO("==> Init Ewol Drawer (START)");
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
	
	#ifdef __PLATFORM__Android
		ewol::SetDefaultFont("freefont/FreeSerif.ttf", 16);
	#else
		ewol::SetDefaultFont("freefont/FreeSerif.ttf", 12);
	#endif
	
	basicWindows = new MainWindows();
	
	
	ewol::shortCut::Add("ctrl+t",       drawMsgGuiLinkNew,   "");
	
	// create the specific windows
	ewol::DisplayWindows(basicWindows);
	DRAW_INFO("==> Init Ewol Drawer (END)");
	etk::File svgFile("lion.svg", etk::FILE_TYPE_DATA);
	svg::Parser *mySVGElement = new svg::Parser(svgFile);
	//mySVGElement->DisplayDebug();
	mySVGElement->GenerateTestFile();
	etk::UString tmpString;
	/*
	tmpString = "H2g2.svg";
	svgFile.SetCompleateName(tmpString, etk::FILE_TYPE_DATA);
	mySVGElement = new svg::Parser(svgFile);
	mySVGElement->GenerateTestFile();
	*/
	tmpString = "01_rectangle.svg";
	svgFile.SetCompleateName(tmpString, etk::FILE_TYPE_DATA);
	mySVGElement = new svg::Parser(svgFile);
	mySVGElement->DisplayDebug();
	mySVGElement->GenerateTestFile();

	tmpString = "02_rectangle.svg";
	svgFile.SetCompleateName(tmpString, etk::FILE_TYPE_DATA);
	mySVGElement = new svg::Parser(svgFile);
	mySVGElement->DisplayDebug();
	mySVGElement->GenerateTestFile();

	tmpString = "03_rectangle.svg";
	svgFile.SetCompleateName(tmpString, etk::FILE_TYPE_DATA);
	mySVGElement = new svg::Parser(svgFile);
	mySVGElement->DisplayDebug();
	mySVGElement->GenerateTestFile();

	tmpString = "04_rectangle.svg";
	svgFile.SetCompleateName(tmpString, etk::FILE_TYPE_DATA);
	mySVGElement = new svg::Parser(svgFile);
	mySVGElement->DisplayDebug();
	mySVGElement->GenerateTestFile();

	exit(-1);
	
}

/**
 * @brief main application function Un-Initialisation
 */
void APP_UnInit(void)
{
	DRAW_INFO("==> Un-Init Ewol Drawer (START)");
	// Remove windows :
	ewol::DisplayWindows(NULL);
	
	if (NULL != basicWindows) {
		basicWindows->MarkToRemove();
		basicWindows = NULL;
	}
	DRAW_INFO("==> Un-Init Ewol Drawer (END)");
}
