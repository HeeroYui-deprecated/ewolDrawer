/**
 *******************************************************************************
 * @file elementMesh.cpp
 * @brief ewol drawer element mesh (Sources)
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


drawElement::Mesh::Mesh(void) : Base("Mesh")
{
	
}

drawElement::Mesh::~Mesh(void)
{
	
}

void drawElement::Mesh::Draw(ewol::OObject2DColored &OObjects)
{
	OObjects.SetColor(0.0, 1.0, 0.0, 1.0);
}




