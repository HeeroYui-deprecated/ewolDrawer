/**
 *******************************************************************************
 * @file widgetDrawer.cpp
 * @brief Ewol Drawer : element generator (Sources)
 * @author Edouard DUPIN
 * @date 03/03/2012
 * @par Project
 * Edn
 *
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
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

#include <widgetDrawer.h>

#include <Debug.h>

#include <ewol/ewol.h>
#include "tinyXML/tinyxml.h"

#include <globalMsg.h>
#include <ewol/WidgetManager.h>
#include <ewol/EObject.h>
#include <elementManager.h>


#undef __class__
#define __class__	"widgetDrawer"


widgetDrawer::widgetDrawer(void)
{
	
}

widgetDrawer::~widgetDrawer(void)
{
	
}

//!< EObject name :
extern const char * const TYPE_EOBJECT_WIDGET_DRAW_DRAWER = "widgetDrawer";

/**
 * @brief Check if the object has the specific type.
 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
 * @param[in] objectType type of the object we want to check
 * @return true if the object is compatible, otherwise false
 */
bool widgetDrawer::CheckObjectType(const char * const objectType)
{
	if (NULL == objectType) {
		EWOL_ERROR("check error : \"" << TYPE_EOBJECT_WIDGET_DRAW_DRAWER << "\" != NULL(pointer) ");
		return false;
	}
	if (objectType == TYPE_EOBJECT_WIDGET_DRAW_DRAWER) {
		return true;
	} else {
		if(true == ewol::Scene::CheckObjectType(objectType)) {
			return true;
		}
		EWOL_ERROR("check error : \"" << TYPE_EOBJECT_WIDGET_DRAW_DRAWER << "\" != \"" << objectType << "\"");
		return false;
	}
}

/**
 * @brief Get the current Object type of the EObject
 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
 * @param[in] objectType type description
 * @return true if the object is compatible, otherwise false
 */
const char * const widgetDrawer::GetObjectType(void)
{
	return TYPE_EOBJECT_WIDGET_DRAW_DRAWER;
}


bool widgetDrawer::OnEventKb(ewol::eventKbType_te typeEvent, uniChar_t unicodeData)
{
	//DRAW_DEBUG("KB EVENT : \"" << unicodeData << "\"" << "type=" << (int32_t)typeEvent);
	if (typeEvent == ewol::EVENT_KB_TYPE_UP) {
		
	}
	return true;
}


bool widgetDrawer::OnEventKbMove(ewol::eventKbType_te typeEvent, ewol::eventKbMoveType_te moveTypeEvent)
{
	if (typeEvent == ewol::EVENT_KB_TYPE_DOWN) {
		MarkToReedraw();
	}
	return true;
}

/*
etkFloat_t widgetDrawer::QuadDistance(coord2D_ts aaa, coord2D_ts bbb)
{
	etkFloat_t xxx = aaa.x - bbb.x;
	etkFloat_t yyy = aaa.y - bbb.y;
	
	return xxx*xxx + yyy*yyy;
}
*/

/**
 * @brief Event on an input of this Widget
 * @param[in] IdInput Id of the current Input (PC : left=1, right=2, middle=3, none=0 / Tactil : first finger=1 , second=2 (only on this widget, no knowledge at ouside finger))
 * @param[in] typeEvent ewol type of event like EVENT_INPUT_TYPE_DOWN/EVENT_INPUT_TYPE_MOVE/EVENT_INPUT_TYPE_UP/EVENT_INPUT_TYPE_SINGLE/EVENT_INPUT_TYPE_DOUBLE/...
 * @param[in] pos Absolute position of the event
 * @return true the event is used
 * @return false the event is not used
 */
bool widgetDrawer::OnEventInput(int32_t IdInput, ewol::eventInputType_te typeEvent, coord2D_ts pos)
{
	coord2D_ts relativePos = RelativePosition(pos);

	return true;
}



/**
 * @brief Receive a message from an other EObject with a specific eventId and data
 * @param[in] CallerObject Pointer on the EObject that information came from
 * @param[in] eventId Message registered by this class
 * @param[in] data Data registered by this class
 * @return ---
 */
void widgetDrawer::OnReceiveMessage(ewol::EObject * CallerObject, const char * eventId, etk::UString data)
{
	DRAW_DEBUG("Extern Event : " << CallerObject << "  type : " << eventId << "  data=\"" << data << "\"");
}


