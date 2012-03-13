/**
 *******************************************************************************
 * @file widgetDrawer.h
 * @brief Ewol Drawer : element generator (Header)
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

#ifndef __WIDGET_DRAWER_H__
#define __WIDGET_DRAWER_H__

#include <widgetDrawer.h>
#include <globalMsg.h>
#include <ewol/Widget.h>

#include <etk/Types.h>
typedef struct {
	int32_t  dot[3];
	color_ts color[3];
} link_ts;


extern const char * const TYPE_EOBJECT_WIDGET_DRAW_DRAWER;

class widgetDrawer :public ewol::Widget
{
	public:
		         widgetDrawer(void);
		virtual ~widgetDrawer(void);
		/**
		 * @brief Check if the object has the specific type.
		 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
		 * @param[in] objectType type of the object we want to check
		 * @return true if the object is compatible, otherwise false
		 */
		virtual bool CheckObjectType(const char * const objectType);
		
		/**
		 * @brief Get the current Object type of the EObject
		 * @note In Embended platforme, it is many time no -rtti flag, then it is not possible to use dynamic cast ==> this will replace it
		 * @param[in] objectType type description
		 * @return true if the object is compatible, otherwise false
		 */
		virtual const char * const GetObjectType(void);
		virtual bool   CalculateMinSize(void);
	private:
		color_ts                     m_triangleColor;  //!< color for the next element of the triangle
		color_ts                     m_textColorFg;    //!< Text color
		color_ts                     m_textColorBg;    //!< Background color
		// drawing elements :
		ewol::OObject2DTextColored   m_OObjectTextNormal[NB_BOUBLE_BUFFER];
		ewol::OObject2DColored       m_OObjectsColored[NB_BOUBLE_BUFFER];
		
	public:
		virtual void   OnRegenerateDisplay(void);
		/**
		 * @brief Receive a message from an other EObject with a specific eventId and data
		 * @param[in] CallerObject Pointer on the EObject that information came from
		 * @param[in] eventId Message registered by this class
		 * @param[in] data Data registered by this class
		 * @return ---
		 */
		virtual void OnReceiveMessage(ewol::EObject * CallerObject, const char * eventId, etk::UString data);
	public:
		/**
		 * @brief Event on an input of this Widget
		 * @param[in] IdInput Id of the current Input (PC : left=1, right=2, middle=3, none=0 / Tactil : first finger=1 , second=2 (only on this widget, no knowledge at ouside finger))
		 * @param[in] typeEvent ewol type of event like EVENT_INPUT_TYPE_DOWN/EVENT_INPUT_TYPE_MOVE/EVENT_INPUT_TYPE_UP/EVENT_INPUT_TYPE_SINGLE/EVENT_INPUT_TYPE_DOUBLE/...
		 * @param[in] pos Absolute position of the event
		 * @return true the event is used
		 * @return false the event is not used
		 */
		virtual bool OnEventInput(int32_t IdInput, ewol::eventInputType_te typeEvent, coord2D_ts pos);
		/**
		 * @brief Event on the keybord (if no shortcut has been detected before).
		 * @param[in] type of the event (ewol::EVENT_KB_TYPE_DOWN or ewol::EVENT_KB_TYPE_UP)
		 * @param[in] unicodeValue key pressed by the user
		 * @return true if the event has been used
		 * @return false if the event has not been used
		 */
		virtual bool OnEventKb(ewol::eventKbType_te typeEvent, uniChar_t unicodeData);
		virtual bool OnEventKbMove(ewol::eventKbType_te typeEvent, ewol::eventKbMoveType_te moveTypeEvent);
	private:
		int32_t m_fontSize;
		int32_t m_fontNormal;
	public:
		void SetFontSize(int32_t size);
		void SetFontNameNormal(etk::UString fontName);
		void SetColorOnSelected(color_ts newColor);
	protected:
		virtual void OnDraw(void);
	private:
		etk::VectorType<coord2D_ts>   m_dotList;       //!< list of all point in the buffer
		etk::VectorType<link_ts>      m_linkList;      //!< List of all triangle in the mesh
		etk::VectorType<int32_t>      m_selectedList;  //!< current selected points
		int32_t                       m_nearestDot;    //!< nearest dot from the current cursor
		bool                          m_movingPoint;
		etk::UString                  m_fileName;
		void removeDotId(int32_t id);
		int32_t GetNearestPoint(coord2D_ts pos);
		etkFloat_t QuadDistance(coord2D_ts aaa, coord2D_ts bbb);
		bool DotIsSelected(int32_t dotId);
	public:
		void Load(etk::UString fileName);
		void Save(void);
		void SetFilename(etk::UString fileName) {m_fileName = fileName; };
		bool HasName(void) { if(m_fileName=="") { return false;} return true; };
};

#define DRAW_CAST_WIDGET_DRAWER(curentPointer) EWOL_CAST(TYPE_EOBJECT_WIDGET_DRAW_DRAWER,ewol::widgetDrawer,curentPointer)

#endif

