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
	
	m_triangleColor.red   = 0.0;
	m_triangleColor.green = 1.0;
	m_triangleColor.blue  = 0.0;
	m_triangleColor.alpha = 1.0;
	
	RegisterMultiCast(drawMsgGuiLinkNew);
	SetCanHaveFocus(true);
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
		if(true == ewol::Widget::CheckObjectType(objectType)) {
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
		color_ts bandColor;
		bandColor.red   = 0.0;
		bandColor.green = 0.0;
		bandColor.blue  = 0.0;
		bandColor.alpha = 0.2;
		color_ts bgColor;
		bgColor.red   = 0.0;
		bgColor.green = 0.0;
		bgColor.blue  = 1.0;
		bgColor.alpha = 1.0;
		m_OObjectsColored[m_currentCreateId].SetColor(bgColor);
		m_OObjectsColored[m_currentCreateId].Rectangle( 0, 0, m_size.x, m_size.y);
		// we set a white background... and we draw a square ...
		bgColor.red   = 0.8;
		bgColor.green = 0.8;
		bgColor.blue  = 0.8;
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
		m_OObjectsColored[m_currentCreateId].Rectangle(drawPosStart.x, drawPosStart.y, drawPosStop.x, drawPosStop.y);
		m_OObjectsColored[m_currentCreateId].SetColor(bandColor);
		clipping_ts clip;
		clip.x = drawPosStart.x;
		clip.y = drawPosStart.y;
		clip.w = drawPosStop.x-drawPosStart.x + 2;
		clip.h = drawPosStop.y-drawPosStart.y + 2;
		m_OObjectsColored[m_currentCreateId].clippingSet(clip);
		int32_t nbElement = (drawPosStop.x-drawPosStart.x)/20 +1;
		for (int32_t iii=0; iii<nbElement; iii++) {
			m_OObjectsColored[m_currentCreateId].Rectangle(drawPosStart.x + iii*20, drawPosStart.y, 10, drawPosStop.y);
		}
		nbElement = (drawPosStop.y-drawPosStart.y)/20 +1;
		for (int32_t iii=0; iii<nbElement; iii++) {
			m_OObjectsColored[m_currentCreateId].Rectangle(drawPosStart.x, drawPosStart.y + iii*20, drawPosStop.x, 10);
		}
		m_OObjectsColored[m_currentCreateId].clippingDisable();
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
		bgColor.red   = 1.0;
		bgColor.green = 1.0;
		bgColor.blue  = 1.0;
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
				m_OObjectsColored[m_currentCreateId].Rectangle( position.x-1, position.y-1, 3, 3);
			}
			if (m_nearestDot == iii) {
				color_ts tmpColor;
				tmpColor.red   = 1.0;
				tmpColor.green = 0.0;
				tmpColor.blue  = 1.0;
				tmpColor.alpha = 1.0;
				m_OObjectsColored[m_currentCreateId].SetColor(tmpColor);
				m_OObjectsColored[m_currentCreateId].Circle( position.x, position.y, 6, 2);
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
			tmpLink.color[0] = m_triangleColor;
			tmpLink.color[1] = m_triangleColor;
			tmpLink.color[2] = m_triangleColor;
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

void widgetDrawer::SetColorOnSelected(color_ts newColor)
{
	m_triangleColor = newColor;
	// Remove all selected points ...
	for(int32_t iii=0; iii<m_dotList.Size() ; iii++) {
		if (true == DotIsSelected(iii)) {
			// Remove all link who have a selected point : 
			for(int32_t jjj=0 ; jjj<m_linkList.Size() ; jjj++) {
				if(m_linkList[jjj].dot[0] == iii) {
					m_linkList[jjj].color[0] = newColor;
				}
				if(m_linkList[jjj].dot[1] == iii) {
					m_linkList[jjj].color[1] = newColor;
				}
				if(m_linkList[jjj].dot[2] == iii) {
					m_linkList[jjj].color[2] = newColor;
				}
			}
		}
	}
	MarkToReedraw();
}


/*
<e2d ratio="1.000">
	<element name="hjhj">
		<dot id=1 x="0.2352" y="0.435634" />
		<dot id=2 x="0.6746" y="0.323467" />
		<dot id=3 x="0.4657" y="0.234131" />
		<dot id=3 x="0.00000" y="1.000000" />
		<link id1="1" color1="#45F645FF"
		      id2="2" color2="#345635FF"
		      id3="4" color3="#867757FF"/>
	</element>
</e2d>
*/
void widgetDrawer::Load(etk::UString newFileName)
{
	
	// Remove all local elements :
	m_dotList.Clear();
	m_linkList.Clear();
	m_selectedList.Clear();
	m_nearestDot = -1;
	m_movingPoint = false;
	m_fileName = newFileName;
	
	DRAW_DEBUG("open file (DRAWER) \"" << m_fileName << "\"");

	// allocate the document in the stack
	TiXmlDocument XmlDocument;
	// open the curent File
	etk::File fileName(m_fileName, etk::FILE_TYPE_DIRECT);
	if (false == fileName.Exist()) {
		DRAW_ERROR("File Does not exist : " << fileName);
		return;
	}
	int32_t fileSize = fileName.Size();
	if (0==fileSize) {
		DRAW_ERROR("This file is empty : " << fileName);
		return;
	}
	if (false == fileName.fOpenRead()) {
		DRAW_ERROR("Can not open the file : " << fileName);
		return;
	}
	// allocate data
	char * fileBuffer = new char[fileSize+5];
	if (NULL == fileBuffer) {
		DRAW_ERROR("Error Memory allocation size=" << fileSize);
		return;
	}
	memset(fileBuffer, 0, (fileSize+5)*sizeof(char));
	// load data from the file :
	fileName.fRead(fileBuffer, 1, fileSize);
	// close the file:
	fileName.fClose();
	// load the XML from the memory
	XmlDocument.Parse((const char*)fileBuffer, 0, TIXML_ENCODING_UTF8);
	
	TiXmlElement* root = XmlDocument.FirstChildElement( "e2d" );
	if (NULL == root ) {
		DRAW_ERROR("(l ?) main node not find: \"e2d\" in \"" << fileName << "\"");
		return;
	} else {
		
		for(TiXmlNode * pNode = root->FirstChild();
		    NULL != pNode;
		    pNode = pNode->NextSibling() ) {
			if (pNode->Type()==TiXmlNode::TINYXML_COMMENT) {
				// nothing to do, just proceed to next step
			} else if (!strcmp(pNode->Value(), "element")) {
				for(TiXmlNode * pGuiNode = pNode->FirstChild();
				    NULL != pGuiNode;
				    pGuiNode = pGuiNode->NextSibling()) {
					if (pGuiNode->Type()==TiXmlNode::TINYXML_COMMENT) {
						// nothing to do, just proceed to next step
					} else if (!strcmp(pGuiNode->Value(), "dot")) {
						const char *xxx = pGuiNode->ToElement()->Attribute("x");
						const char *yyy = pGuiNode->ToElement()->Attribute("y");
						
						if(    NULL != xxx
						    && NULL != yyy) {
							coord2D_ts pos;
							double posX, posY;
							sscanf(xxx, "%lf", &posX);
							sscanf(yyy, "%lf", &posY);
							pos.x = posX;
							pos.y = posY;
							DRAW_DEBUG("load dot : " << xxx << "," << yyy << " ==>" << pos);
							m_dotList.PushBack(pos);
						}
					} else if (!strcmp(pGuiNode->Value(), "link")) {
						const char *id[3];
						const char *color[3];
						id[0] = pGuiNode->ToElement()->Attribute("id1");
						id[1] = pGuiNode->ToElement()->Attribute("id2");
						id[2] = pGuiNode->ToElement()->Attribute("id3");
						color[0] = pGuiNode->ToElement()->Attribute("color1");
						color[1] = pGuiNode->ToElement()->Attribute("color2");
						color[2] = pGuiNode->ToElement()->Attribute("color3");
						
						if(    NULL != id[0]
						    && NULL != id[1]
						    && NULL != id[2]
						    && NULL != color[0]
						    && NULL != color[1]
						    && NULL != color[2]) {
							link_ts localLink;
							int r=0;
							int v=0;
							int b=0;
							int a=-1;
							for(int32_t kkk=0; kkk<3; kkk++) {
								sscanf(id[kkk], "%d", &localLink.dot[kkk]);
								sscanf(color[kkk], "#%02x%02x%02x%02x", &r, &v, &b, &a);
								localLink.color[kkk].red = (float)r/255.0;
								localLink.color[kkk].green = (float)v/255.0;
								localLink.color[kkk].blue = (float)b/255.0;
								if (-1 == a) {
									localLink.color[kkk].alpha = 1;
								} else {
									localLink.color[kkk].alpha = (float)a/255.0;
								}
							}
							DRAW_DEBUG("load link : [" << localLink.dot[0] << "," << localLink.dot[1] << "," << localLink.dot[2] << "] ");
							DRAW_DEBUG("       col: [" << localLink.color[0] << "," << localLink.color[1] << "," << localLink.color[2] << "] ");
							m_linkList.PushBack(localLink);
						}
					} else {
						DRAW_ERROR("(l "<<pGuiNode->Row()<<") node not suported : \""<<pGuiNode->Value()<<"\" must be [dot,link]");
					}
				}
			} else {
				DRAW_ERROR("(l "<<pNode->Row()<<") node not suported : \""<<pNode->Value()<<"\" must be [element]");
			}
		}
	}
	if (NULL != fileBuffer) {
		delete[] fileBuffer;
	}
	MarkToReedraw();
}
/*
<e2d ratio="1.000">
	<element name="hjhj">
		<dot id=1 x="0.2352" y="0.435634" />
		<dot id=2 x="0.6746" y="0.323467" />
		<dot id=3 x="0.4657" y="0.234131" />
		<dot id=3 x="0.00000" y="1.000000" />
		<link id1="1" color1="#45F645FF"
		      id2="2" color2="#345635FF"
		      id3="4" color3="#867757FF"/>
	</element>
</e2d>
*/
void widgetDrawer::Save(void)
{
	if (m_fileName == "") {
		DRAW_ERROR("No filename set ...");
		return;
	}
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	doc.LinkEndChild( decl );
	TiXmlElement * mastertElement = new TiXmlElement( "e2d" );
	mastertElement->SetAttribute( "version", "0.1" );
	doc.LinkEndChild( mastertElement ); 
	
	TiXmlElement * element = new TiXmlElement( "element" );
	element->SetAttribute( "name", "???" );
	element->SetAttribute( "type", "mesh" );
	mastertElement->LinkEndChild( element );
	
	for(int32_t iii=0; iii<m_dotList.Size() ; iii++) {
		char tmpChar[256];
		TiXmlElement * elementDot = new TiXmlElement( "dot" );
		elementDot->SetAttribute( "id", iii );
		sprintf(tmpChar, "%f", m_dotList[iii].x);
		elementDot->SetAttribute( "x", tmpChar );
		sprintf(tmpChar, "%f", m_dotList[iii].y);
		elementDot->SetAttribute( "y", tmpChar );
		element->LinkEndChild( elementDot );
	}
	for(int32_t iii=0; iii<m_linkList.Size() ; iii++) {
		TiXmlElement * elementDot = new TiXmlElement( "link" );
		elementDot->SetAttribute( "id1", m_linkList[iii].dot[0] );
		char colorText[256];
		sprintf(colorText, "#%02X%02X%02X%02X",
		        (uint8_t)(m_linkList[iii].color[0].red   * 0xFF),
		        (uint8_t)(m_linkList[iii].color[0].green * 0xFF),
		        (uint8_t)(m_linkList[iii].color[0].blue  * 0xFF),
		        (uint8_t)(m_linkList[iii].color[0].alpha * 0xFF));
		elementDot->SetAttribute( "color1", colorText );
		elementDot->SetAttribute( "id2", m_linkList[iii].dot[1] );
		sprintf(colorText, "#%02X%02X%02X%02X",
		        (uint8_t)(m_linkList[iii].color[1].red   * 0xFF),
		        (uint8_t)(m_linkList[iii].color[1].green * 0xFF),
		        (uint8_t)(m_linkList[iii].color[1].blue  * 0xFF),
		        (uint8_t)(m_linkList[iii].color[1].alpha * 0xFF));
		elementDot->SetAttribute( "color2", colorText );
		elementDot->SetAttribute( "id3", m_linkList[iii].dot[2] );
		sprintf(colorText, "#%02X%02X%02X%02X",
		        (uint8_t)(m_linkList[iii].color[2].red   * 0xFF),
		        (uint8_t)(m_linkList[iii].color[2].green * 0xFF),
		        (uint8_t)(m_linkList[iii].color[2].blue  * 0xFF),
		        (uint8_t)(m_linkList[iii].color[2].alpha * 0xFF));
		elementDot->SetAttribute( "color3", colorText );
		element->LinkEndChild( elementDot );
	}
	//Save Document
	doc.SaveFile( m_fileName.Utf8Data() );
}

