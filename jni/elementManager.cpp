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
