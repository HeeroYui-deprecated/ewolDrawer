/**
 *******************************************************************************
 * @file elementDisk.h
 * @brief ewol drawer element disk (header)
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

#ifndef __ELEMENT_DISK_H__
#define __ELEMENT_DISK_H__

namespace drawElement {
	class Disk : public drawElement::Base
	{
		public:
			Disk(void);
			virtual ~Disk(void);
		private:
			color_ts    m_color;
			coord2D_ts  m_center;
			int32_t     m_nbRay;
			etkFloat_t  m_ratio;
			etkFloat_t  m_shadowOutput;
			//etkFloat_t  m_angle;
			//etkFloat_t  m_angleDisplayed;
		public:
			
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

