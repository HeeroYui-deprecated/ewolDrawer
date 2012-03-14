/**
 *******************************************************************************
 * @file elementManager.h
 * @brief ewol drawer element manager (header)
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

#ifndef __ELEMENT_MANAGER_H__
#define __ELEMENT_MANAGER_H__

#include <elementBase.h>

namespace drawElement {
	typedef enum {
		DRAW_ELEMENT_TYPE_CIRCLE,
		DRAW_ELEMENT_TYPE_DISK,
		DRAW_ELEMENT_TYPE_MESH,
		DRAW_ELEMENT_TYPE_POLYGONE,
		DRAW_ELEMENT_TYPE_RECTANGLE,
	}elementType_te;
	
	void                RemoveAll(void);
	int32_t             Size(void);
	drawElement::Base * Get(int32_t id);
	void                Rm(int32_t id);
	void                Add(elementType_te type);
	void                Up(int32_t id);
	void                Down(int32_t id);
	
};

#endif

