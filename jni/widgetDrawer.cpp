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

#include <globalMsg.h>
#include <ewol/WidgetManager.h>
#include <ewol/EObject.h>


#undef __class__
#define __class__	"widgetDrawer"


widgetDrawer::widgetDrawer(void)
{
	m_fontNormal = -1;
	m_fontSize = 15;
	m_nearestDot = -1;
	m_movingPoint = false;
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

void widgetDrawer::OnDraw(void)
{
	m_OObjectsColored[      m_currentDrawId].Draw();
	m_OObjectTextNormal[    m_currentDrawId].Draw();
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
			if (true == DotIsSelected(iii)) {
				color_ts tmpColor;
				tmpColor.red   = 1.0;
				tmpColor.green = 0.0;
				tmpColor.blue  = 0.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Rectangle( position.x-1, position.y-1, 3, 3);
				m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
			} else {
				m_OObjectsColored[m_currentCreateId].RectangleBorder( position.x-1, position.y-1, 3, 3, 1);
			}
			if (m_nearestDot == iii) {
				color_ts tmpColor;
				tmpColor.red   = 1.0;
				tmpColor.green = 0.0;
				tmpColor.blue  = 1.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Circle( position.x, position.y, 6, 1);
				m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
			}
		}
		m_needFlipFlop = true;
	}
}


bool widgetDrawer::OnEventKb(ewol::eventKbType_te typeEvent, uniChar_t unicodeData)
{
	//DRAW_DEBUG("KB EVENT : \"" << unicodeData << "\"" << "type=" << (int32_t)typeEvent);
	if (typeEvent == ewol::EVENT_KB_TYPE_UP) {
		if (unicodeData == 0x7F) {
			// Remove all selected points ...
			for(int32_t iii=m_dotList.Size()-1 ; iii>=0 ; iii--) {
				if (true == DotIsSelected(iii)) {
					// Remove all link who have a selected point : 
					for(int32_t jjj=m_linkList.Size()-1; jjj>=0; jjj--) {
						if(     m_linkList[jjj].dot[0] == iii
						     || m_linkList[jjj].dot[1] == iii
						     || m_linkList[jjj].dot[2] == iii ) {
							m_linkList.Erase(jjj);
						}
					}
					m_dotList.Erase(iii);
					for(int32_t jjj=m_linkList.Size()-1; jjj>=0; jjj--) {
						if(m_linkList[jjj].dot[0] > iii) {
							m_linkList[jjj].dot[0]--;
						}
						if(m_linkList[jjj].dot[1] > iii) {
							m_linkList[jjj].dot[1]--;
						}
						if(m_linkList[jjj].dot[2] > iii) {
							m_linkList[jjj].dot[2]--;
						}
					}
				}
			}
			// rmemove all the selected list
			m_selectedList.Clear();
			
			MarkToReedraw();
		}
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

bool widgetDrawer::DotIsSelected(int32_t dotId)
{
	for( int32_t iii=0; iii< m_selectedList.Size(); iii++) {
		if (m_selectedList[iii] == dotId) {
			return true;
		}
	}
	return false;
}

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
	position.x = (relativePos.x - BORDER_SIZE) / (drawPosStop.x-drawPosStart.x);
	position.y = (relativePos.y - BORDER_SIZE) / (drawPosStop.y-drawPosStart.y);
	
	position.x = etk_avg(0, position.x, 1);
	position.y = etk_avg(0, position.y, 1);
	//DRAW_DEBUG(" event " << IdInput);
	if (0 == IdInput) {
		m_nearestDot = GetNearestPoint(position);
		MarkToReedraw();
	} else  if (1 == IdInput) {
		KeepFocus();
		if ( ewol::EVENT_INPUT_TYPE_SINGLE == typeEvent) {
			// try to find the point
			int select = GetNearestPoint(position);
			if (false == ewol::IsSetShift() ) {
				m_selectedList.Clear();
				m_selectedList.PushBack(select);
				MarkToReedraw();
			} else {
				if (false == DotIsSelected(select)) {
					// add element in the list
					m_selectedList.PushBack(select);
					MarkToReedraw();
				} else {
					// remove it ...
					for (int32_t iii=m_selectedList.Size()-1 ; iii>=0 ; iii--) {
						if (m_selectedList[iii] == select) {
							m_selectedList.Erase(iii);
						}
					}
				}
			}
		} if ( ewol::EVENT_INPUT_TYPE_DOWN == typeEvent) {
			// try to find the point
			int select = GetNearestPoint(position);
			if (m_selectedList.Size() == 1) {
				if (select == m_selectedList[0]) {
					MarkToReedraw();
					m_movingPoint = true;
				}
			}
		} else if (ewol::EVENT_INPUT_TYPE_UP == typeEvent) {
			m_movingPoint = false;
			MarkToReedraw();
		} else if (ewol::EVENT_INPUT_TYPE_MOVE == typeEvent && true == m_movingPoint) {
			if (m_selectedList.Size() != 1) {
				m_movingPoint = false;
				return false;
			}
			// set it in the drawing area
			relativePos.x = etk_avg(drawPosStart.x, relativePos.x, drawPosStop.x);
			relativePos.y = etk_avg(drawPosStart.y, relativePos.y, drawPosStop.y);
			// instanciate the value ...
			m_dotList[m_selectedList[0]] = position;
			MarkToReedraw();
		}
	} else if (3 == IdInput && ewol::EVENT_INPUT_TYPE_SINGLE == typeEvent) {
		
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
		if (m_selectedList.Size() == 3) {
			link_ts tmpLink;
			tmpLink.dot[0] = m_selectedList[0];
			tmpLink.dot[1] = m_selectedList[1];
			tmpLink.dot[2] = m_selectedList[2];
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