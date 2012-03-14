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
			
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

