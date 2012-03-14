/**
 *******************************************************************************
 * @file elementPolygone.cpp
 * @brief ewol drawer element polygone (Sources)
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


drawElement::Polygone::Polygone(void) : Base("Polygone")
{
	
}

drawElement::Polygone::~Polygone(void)
{
	
}

void drawElement::Polygone::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(0.0, 0.0, 1.0, 1.0);
}




