/**
 *******************************************************************************
 * @file elementPolygone.h
 * @brief ewol drawer element polygone (header)
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

#ifndef __ELEMENT_POLYGONE_H__
#define __ELEMENT_POLYGONE_H__

namespace drawElement {
	class Polygone : public drawElement::Base
	{
		public:
			Polygone(void);
			virtual ~Polygone(void);
		private:
			
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

