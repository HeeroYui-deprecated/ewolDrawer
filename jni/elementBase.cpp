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

drawElement::Base::Base(const char* type)
{
	m_name = "NoName";
	m_type = type;
	m_visible = true;
}

drawElement::Base::~Base(void)
{
	
}
