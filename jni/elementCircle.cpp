/**
 *******************************************************************************
 * @file elementCircle.cpp
 * @brief ewol drawer element Circle (Sources)
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


drawElement::Circle::Circle(void) : Base(DRAW_ELEMENT_TYPE_CIRCLE)
{
	m_colorBorder.red   = 1.0;
	m_colorBorder.green = 1.0;
	m_colorBorder.blue  = 1.0;
	m_colorBorder.alpha = 1.0;
	m_center.x = 0;
	m_center.y = 0;
	m_ratio = 0.3;
	m_thickness = 0.03;
}

drawElement::Circle::~Circle(void)
{
	
}

void drawElement::Circle::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(m_colorBorder);
	OObjects.Circle(m_center.x, m_center.y, m_ratio, m_thickness);
}


