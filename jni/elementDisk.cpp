/**
 *******************************************************************************
 * @file elementDisk.cpp
 * @brief ewol drawer element disk (Sources)
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




drawElement::Disk::Disk(void) : Base(DRAW_ELEMENT_TYPE_DISK)
{
	
}

drawElement::Disk::~Disk(void)
{
	
}

void drawElement::Disk::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(0.0, 1.0, 1.0, 1.0);
	OObjects.Disc(0.7, 0.7, 0.3);
}





