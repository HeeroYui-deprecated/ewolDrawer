/**
 *******************************************************************************
 * @file elementManager.cpp
 * @brief ewol drawer element manager (Sources)
 * @author Edouard DUPIN
 * @date 14/03/2012
 * @par Project
 * EwolDrawer
 *
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
 *
 *******************************************************************************
 */

#include <Debug.h>
#include <elementManager.h>
#include <etk/VectorType.h>
#include <ewol/EObject.h>
#include <globalMsg.h>

static etk::VectorType<drawElement::Base*>  l_listElements;
static int32_t                              l_selected = -1;
//!< Basic filename
etk::UString                                l_fileName;

void drawElement::RemoveAll(void)
{
	for (int32_t iii=l_listElements.Size()-1; iii>=0; iii--) {
		if (l_listElements[iii]!=NULL) {
			delete(l_listElements[iii]);
			l_listElements[iii] = NULL;
		}
	}
	l_listElements.Clear();
	etk::UString tmpString("");
	l_selected = -1;
	ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
}

int32_t drawElement::Size(void)
{
	return l_listElements.Size();
}

drawElement::Base* drawElement::Get(int32_t id)
{
	if (id < l_listElements.Size() && id >=0) {
		return l_listElements[id];
	}
	return NULL;
}

void drawElement::Rm(int32_t id)
{
	if (id < l_listElements.Size() && id >=0) {
		if (l_listElements[id]!=NULL) {
			delete(l_listElements[id]);
			l_listElements[id] = NULL;
		}
		l_listElements.Erase(id);
		if (l_selected == id) {
			l_selected = -1;
		}
	}
	etk::UString tmpString("");
	ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
}

void drawElement::Add(elementType_te type)
{
	drawElement::Base* newElement = NULL;
	switch(type) {
		case drawElement::DRAW_ELEMENT_TYPE_CIRCLE:
			newElement = new drawElement::Circle();
			break;
		case drawElement::DRAW_ELEMENT_TYPE_DISK:
			newElement = new drawElement::Disk();
			break;
		case drawElement::DRAW_ELEMENT_TYPE_MESH:
			newElement = new drawElement::Mesh();
			break;
		case drawElement::DRAW_ELEMENT_TYPE_POLYGONE:
			newElement = new drawElement::Polygone();
			break;
		case drawElement::DRAW_ELEMENT_TYPE_RECTANGLE:
			newElement = new drawElement::Rectangle();
			break;
		default:
			DRAW_ERROR("Unknow element type : " << type);
			return;
	}
	if (NULL == newElement) {
		DRAW_ERROR("Ellocation ERROR in the new element ... ");
		return;
	}
	l_listElements.PushBack(newElement);
	l_selected = l_listElements.Size()-1;
	etk::UString tmpString("");
	ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
}

void drawElement::Up(int32_t id)
{
	
	etk::UString tmpString("");
	ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
}

void drawElement::Down(int32_t id)
{
	
	etk::UString tmpString("");
	ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
}

void drawElement::SelectSet(int32_t id)
{
	if (id < l_listElements.Size() && id >=0) {
		l_selected = id;
		etk::UString tmpString("");
		ewol::EObjectMessageMultiCast::AnonymousSend(drawMsgListElementChange, tmpString);
	}
}

int32_t drawElement::SelectGet(void)
{
	return l_selected;
}



void drawElement::SetFilename(etk::UString fileName)
{
	l_fileName = fileName;
}


bool drawElement::HasName(void)
{
	if(l_fileName=="") {
		return false;
	}
	return true;
}


/*
<e2d ratio="1.000">
	<element type="Mesh" name="hjhj">
		<dot id=1 x="0.2352" y="0.435634" />
		<dot id=2 x="0.6746" y="0.323467" />
		<dot id=3 x="0.4657" y="0.234131" />
		<dot id=3 x="0.00000" y="1.000000" />
		<link id1="1" color1="#45F645FF"
		      id2="2" color2="#345635FF"
		      id3="4" color3="#867757FF"/>
	</element>
	<element type="Circle" name="plop">
		<color>#45F645FF</color>
		<center x="0.2352" y="0.435634" />
		<ratio>0.752</ratio>
		<nbRay>12</nbRay>
		<thickness>0.03</thickness>
		<shadowOutput>0.1</shadowOutput>
		<shadowInput>0.1</shadowInput>
	</element>
</e2d>
*/

void drawElement::Load(etk::UString fileName)
{
	drawElement::RemoveAll();
	SetFilename(newFileName);
	
	DRAW_DEBUG("open file (DRAWER) \"" << l_fileName << "\"");

	// allocate the document in the stack
	TiXmlDocument XmlDocument;
	// open the curent File
	etk::File fileName(l_fileName, etk::FILE_TYPE_DIRECT);
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
			/*
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
			*/
			} else {
				DRAW_ERROR("(l "<<pNode->Row()<<") node not suported : \""<<pNode->Value()<<"\" must be [element]");
			}
		}
	}
	if (NULL != fileBuffer) {
		delete[] fileBuffer;
	}
}

void drawElement::Save(void)
{
	if (l_fileName == "") {
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
	doc.SaveFile( l_fileName.Utf8Data() );
}

