/**
 *******************************************************************************
 * @file elementRectangle.cpp
 * @brief ewol drawer element Rectangle (Sources)
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


drawElement::Rectangle::Rectangle(void) : Base("Rectangle")
{
	
}

drawElement::Rectangle::~Rectangle(void)
{
	
}

void drawElement::Rectangle::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(1.0, 0.0, 0.0, 1.0);
	OObjects.Rectangle(0.5, 0.5, 0.3, 0.3);
}




