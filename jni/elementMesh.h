/**
 *******************************************************************************
 * @file elementMesh.h
 * @brief ewol drawer element mesh (header)
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

#ifndef __ELEMENT_MESH_H__
#define __ELEMENT_MESH_H__

namespace drawElement {
	class Mesh : public drawElement::Base
	{
		public:
			Mesh(void);
			virtual ~Mesh(void);
		private:
			
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

