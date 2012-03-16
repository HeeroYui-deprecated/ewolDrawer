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
	
	void                RemoveAll(void);
	int32_t             Size(void);
	drawElement::Base * Get(int32_t id);
	void                Rm(int32_t id);
	void                Add(elementType_te type);
	void                Up(int32_t id);
	void                Down(int32_t id);
	void                SelectSet(int32_t id);
	int32_t             SelectGet(void);
	
	void Load(etk::UString fileName);
	void Save(void);
	void SetFilename(etk::UString fileName);
	bool HasName(void);
};

#endif

