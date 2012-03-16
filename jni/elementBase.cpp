/**
 *******************************************************************************
 * @file elementBase.h
 * @brief ewol drawer element Base (header)
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
#include <elementBase.h>

drawElement::Base::Base(elementType_te type)
{
	m_name = "NoName";
	m_type = type;
	m_visible = true;
}

drawElement::Base::~Base(void)
{
	
}

const char* drawElement::Base::GetTypeChar(void)
{
	switch(m_type) {
		case DRAW_ELEMENT_TYPE_CIRCLE:
			return "Circle";
		case DRAW_ELEMENT_TYPE_DISK:
			return "Disk";
		case DRAW_ELEMENT_TYPE_MESH:
			return "Mesh";
		case DRAW_ELEMENT_TYPE_POLYGONE:
			return "Polygone";
		case DRAW_ELEMENT_TYPE_RECTANGLE:
			return "Rectangle";
	}
	return "??";
}