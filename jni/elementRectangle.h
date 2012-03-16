/**
 *******************************************************************************
 * @file elementRectangle.h
 * @brief ewol drawer element Rectangle (header)
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

#ifndef __ELEMENT_RECTANGLE_H__
#define __ELEMENT_RECTANGLE_H__

namespace drawElement {
	class Rectangle : public drawElement::Base
	{
		public:
			Rectangle(void);
			virtual ~Rectangle(void);
		private:
			color_ts    m_colorBorder;
			color_ts    m_colorInside;
			coord2D_ts  m_center;
			coord2D_ts  m_size;
			bool        m_fill
			etkFloat_t  m_thickness;
			etkFloat_t  m_shadowOutput;
			etkFloat_t  m_shadowInput;
			//etkFloat_t  m_angle;
			//etkFloat_t  m_angleDisplayed;
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

