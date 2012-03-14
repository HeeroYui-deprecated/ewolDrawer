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


drawElement::Circle::Circle(void) : Base("Circle")
{
	
}

drawElement::Circle::~Circle(void)
{
	
}

void drawElement::Circle::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(1.0, 0.0, 1.0, 1.0);
	OObjects.Circle(0.2, 0.2, 0.3, 0.05);
}


