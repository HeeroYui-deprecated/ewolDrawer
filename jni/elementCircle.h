/**
 *******************************************************************************
 * @file elementCircle.h
 * @brief ewol drawer element Circle (header)
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

#ifndef __ELEMENT_CIRCLE_H__
#define __ELEMENT_CIRCLE_H__

namespace drawElement {
	class Circle : public drawElement::Base
	{
		public:
			Circle(void);
			virtual ~Circle(void);
		private:
			
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

