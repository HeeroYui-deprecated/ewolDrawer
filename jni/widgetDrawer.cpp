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

#include <globalMsg.h>
#include <ewol/WidgetManager.h>
#include <ewol/EObject.h>


#undef __class__
#define __class__	"widgetDrawer"


widgetDrawer::widgetDrawer(void)
{
	m_fontNormal = -1;
	m_fontSize = 15;
	m_movingPoint = false;
	m_lastSelected[0] = -1;
	m_lastSelected[1] = -1;
	m_lastSelected[2] = -1;
	m_textColorFg.red   = 0.0;
	m_textColorFg.green = 	0.0;
	m_textColorFg.blue  = 0.0;
	m_textColorFg.alpha = 1.0;
	
	m_textColorBg.red   = 0.0;
	m_textColorBg.green = 0.0;
	m_textColorBg.blue  = 0.0;
	m_textColorBg.alpha = 0.25;
	RegisterMultiCast(drawMsgGuiLinkNew);
	SetCanHaveFocus(true);
}

widgetDrawer::~widgetDrawer(void)
{
	
}

bool widgetDrawer::CalculateMinSize(void)
{
	m_minSize.x = 50;
	m_minSize.y = 50;
	return true;
}

bool widgetDrawer::OnDraw(void)
{
	m_OObjectsColored[      m_currentDrawId].Draw();
	m_OObjectTextNormal[    m_currentDrawId].Draw();
	return true;
}
#define BORDER_SIZE       (2)
void widgetDrawer::OnRegenerateDisplay(void)
{
	if (true == NeedRedraw()) {
		// clean internal elements ...
		m_OObjectTextNormal[    m_currentCreateId].SetFontID(m_fontNormal);
		m_OObjectTextNormal[    m_currentCreateId].Clear();
		m_OObjectsColored[      m_currentCreateId].Clear();
		// we set 3 pixels in the border (blue) and draw 
		color_ts bgColor;
		bgColor.red   = 0.0;
		bgColor.green = 0.0;
		bgColor.blue  = 1.0;
		bgColor.alpha = 1.0;
		m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
		m_OObjectsColored[m_currentCreateId].Rectangle( 0, 0, m_size.x, m_size.y);
		// we set a white background... and we draw a square ...
		bgColor.red   = 1.0;
		bgColor.green = 1.0;
		bgColor.blue  = 1.0;
		bgColor.alpha = 1.0;
		m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
		coord2D_ts drawPosStart;
		coord2D_ts drawPosStop;
		if (m_size.x < m_size.y) {
			drawPosStart.x = BORDER_SIZE;
			drawPosStart.y = BORDER_SIZE;
			drawPosStop.x = m_size.x-2*BORDER_SIZE;
			drawPosStop.y = m_size.x-2*BORDER_SIZE;
		} else {
			drawPosStart.x = BORDER_SIZE;
			drawPosStart.y = BORDER_SIZE;
			drawPosStop.x = m_size.y-2*BORDER_SIZE;
			drawPosStop.y = m_size.y-2*BORDER_SIZE;
		}
		m_OObjectsColored[m_currentCreateId].Rectangle( drawPosStart.x, drawPosStart.y, drawPosStop.x, drawPosStop.y);
		
		for (int32_t iii=0; iii<m_linkList.Size(); iii++) {
			for (int32_t jjj=0; jjj<3; jjj++) {
				// set color
				m_OObjectsColored[m_currentCreateId].SetColor(m_linkList[iii].color[jjj]);
				// Set the specific dot
				int dotId = m_linkList[iii].dot[jjj];
				coord2D_ts position;
				position.x = BORDER_SIZE + m_dotList[dotId].x * (drawPosStop.x-drawPosStart.x);
				position.y = BORDER_SIZE + m_dotList[dotId].y * (drawPosStop.y-drawPosStart.y);
				m_OObjectsColored[m_currentCreateId].SetPoint(position);
			}
		}
		// we set a white background... and we draw a square ...
		bgColor.red   = 0.0;
		bgColor.green = 0.0;
		bgColor.blue  = 0.0;
		bgColor.alpha = 1.0;
		m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
		for (int32_t iii=0; iii<m_dotList.Size(); iii++) {
			coord2D_ts position;
			position.x = BORDER_SIZE + m_dotList[iii].x * (drawPosStop.x-drawPosStart.x);
			position.y = BORDER_SIZE + m_dotList[iii].y * (drawPosStop.y-drawPosStart.y);
			if (m_lastSelected[2] == iii) {
				color_ts tmpColor;
				tmpColor.red   = 1.0;
				tmpColor.green = 0.0;
				tmpColor.blue  = 0.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Rectangle( position.x-1, position.y-1, 3, 3);
				m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
			} else if (m_lastSelected[1] == iii) {
				color_ts tmpColor;
				tmpColor.red   = 0.0;
				tmpColor.green = 1.0;
				tmpColor.blue  = 0.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Rectangle( position.x-1, position.y-1, 3, 3);
				m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
			} else if (m_lastSelected[0] == iii) {
				color_ts tmpColor;
				tmpColor.red   = 0.0;
				tmpColor.green = 0.0;
				tmpColor.blue  = 1.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Rectangle( position.x-1, position.y-1, 3, 3);
				m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
			} else {
				m_OObjectsColored[m_currentCreateId].RectangleBorder( position.x-1, position.y-1, 3, 3, 1);
			}
		}
		
		/*
		coord2D_ts textPos;
		textPos.x = 20;
		textPos.y = 20;
		color_ts myColor;
		myColor.red   = 1.0;
		myColor.green = 0.0;
		myColor.blue  = 0.0;
		myColor.alpha = 1.0;
		m_OObjectTextNormal[m_currentCreateId].SetColor(myColor);
		etk::UString tmpDisplay = "test de text";
		m_OObjectTextNormal[m_currentCreateId].Text(textPos, tmpDisplay);
		*/
		
		
		m_needFlipFlop = true;
	}
}


bool widgetDrawer::OnEventKb(ewol::eventKbType_te typeEvent, uniChar_t unicodeData)
{
	//EDN_DEBUG("KB EVENT : \"" << UTF8_data << "\" size=" << strlen(UTF8_data) << "type=" << (int32_t)typeEvent);
	if (typeEvent == ewol::EVENT_KB_TYPE_DOWN) {
		
		MarkToReedraw();
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


etkFloat_t widgetDrawer::QuadDistance(coord2D_ts aaa, coord2D_ts bbb)
{
	etkFloat_t xxx = aaa.x - bbb.x;
	etkFloat_t yyy = aaa.y - bbb.y;
	
	return xxx*xxx + yyy*yyy;
}

int32_t widgetDrawer::GetNearestPoint(coord2D_ts pos)
{
	int32_t idNearest = -1;
	etkFloat_t smallestQuadDist = 10000000;
	for (int32_t iii=0; iii<m_dotList.Size(); iii++) {
		etkFloat_t dist = QuadDistance(pos, m_dotList[iii]);
		if (dist < smallestQuadDist) {
			smallestQuadDist = dist;
			idNearest = iii;
		}
	}
	return idNearest;
}


bool widgetDrawer::OnEventInput(int32_t IdInput, ewol::eventInputType_te typeEvent, ewol::eventPosition_ts pos)
{
	coord2D_ts drawPosStart;
	coord2D_ts drawPosStop;
	if (m_size.x < m_size.y) {
		drawPosStart.x = BORDER_SIZE;
		drawPosStart.y = BORDER_SIZE;
		drawPosStop.x = m_size.x-2*BORDER_SIZE;
		drawPosStop.y = m_size.x-2*BORDER_SIZE;
	} else {
		drawPosStart.x = BORDER_SIZE;
		drawPosStart.y = BORDER_SIZE;
		drawPosStop.x = m_size.y-2*BORDER_SIZE;
		drawPosStop.y = m_size.y-2*BORDER_SIZE;
	}
	coord2D_ts position;
	position.x = (pos.local.x - BORDER_SIZE) / (drawPosStop.x-drawPosStart.x);
	position.y = (pos.local.y - BORDER_SIZE) / (drawPosStop.y-drawPosStart.y);
	
	if (1 == IdInput) {
		if ( ewol::EVENT_INPUT_TYPE_SINGLE == typeEvent) {
			// try to find the point
			int select = GetNearestPoint(position);
			if (select != m_lastSelected[2]) {
				if (select == m_lastSelected[1] ) {
					m_lastSelected[1] = m_lastSelected[2];
					m_lastSelected[2] = select;
				} else {
					m_lastSelected[0] = m_lastSelected[1];
					m_lastSelected[1] = m_lastSelected[2];
					m_lastSelected[2] = select;
				}
				MarkToReedraw();
			}
		} if ( ewol::EVENT_INPUT_TYPE_DOWN == typeEvent) {
			// try to find the point
			int select = GetNearestPoint(position);
			if (select == m_lastSelected[2]) {
				MarkToReedraw();
				m_movingPoint = true;
			}
		} else if (ewol::EVENT_INPUT_TYPE_UP == typeEvent) {
			m_movingPoint = false;
			MarkToReedraw();
		} else if (ewol::EVENT_INPUT_TYPE_MOVE == typeEvent && true == m_movingPoint) {
			// check if neede moving ...
			if(    pos.local.x < drawPosStart.x
			    || pos.local.y < drawPosStart.y
			    || pos.local.x > drawPosStop.x
			    || pos.local.y > drawPosStop.y) {
				// No data to add ...
				return false;
			}
			m_dotList[m_lastSelected[2]] = position;
			MarkToReedraw();
		}
	} else if (3 == IdInput && ewol::EVENT_INPUT_TYPE_SINGLE == typeEvent) {
		// chack if not outside the cadre
		if(    pos.local.x < drawPosStart.x
		    || pos.local.y < drawPosStart.y
		    || pos.local.x > drawPosStop.x
		    || pos.local.y > drawPosStop.y) {
			// No data to add ...
			return false;
		}
		// convert the current position in a float -1 < x?y < 1
		// TODO : Set a min/max ..
		m_dotList.PushBack(position);
		MarkToReedraw();
	}
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
	if (eventId == drawMsgGuiLinkNew) {
		if(    m_lastSelected[0] != -1
		    && m_lastSelected[1] != -1
		    && m_lastSelected[2] != -1) {
			link_ts tmpLink;
			tmpLink.dot[0] = m_lastSelected[0];
			tmpLink.dot[1] = m_lastSelected[1];
			tmpLink.dot[2] = m_lastSelected[2];
			m_lastSelected[0] = -1;
			m_lastSelected[1] = -1;
			m_lastSelected[2] = -1;
			tmpLink.color[0].red   = 0.0;
			tmpLink.color[0].green = 0.0;
			tmpLink.color[0].blue  = 1.0;
			tmpLink.color[0].alpha = 1.0;
			
			tmpLink.color[1].red   = 0.0;
			tmpLink.color[1].green = 1.0;
			tmpLink.color[1].blue  = 0.0;
			tmpLink.color[1].alpha = 1.0;
			
			tmpLink.color[2].red   = 1.0;
			tmpLink.color[2].green = 0.0;
			tmpLink.color[2].blue  = 0.0;
			tmpLink.color[2].alpha = 1.0;
			m_linkList.PushBack(tmpLink);
			MarkToReedraw();
		}
	}
}

void widgetDrawer::SetFontSize(int32_t size)
{
	m_fontSize = size;
}

void widgetDrawer::SetFontNameNormal(etk::UString fontName)
{
	int32_t fontID = ewol::LoadFont(fontName, m_fontSize);
	if (fontID >= 0) {
		m_fontNormal = fontID;
	}
}