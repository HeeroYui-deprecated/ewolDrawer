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
			color_ts    m_color;
			coord2D_ts  m_center;
			int32_t     m_nbRay;
			etkFloat_t  m_ratio;
			etkFloat_t  m_thickness;
			etkFloat_t  m_shadowOutput;
			etkFloat_t  m_shadowInput;
		public:
			void        ColorSet(color_ts color) { m_color = color; };
			color_ts    ColorGet(void) { return m_color; };
			void        CenterSet(coord2D_ts center) { m_center = center; };
			coord2D_ts  CenterGet(void) { return m_center; };
			
			void        RatioSet(etkFloat_t ratio) { m_ratio = ratio; };
			etkFloat_t  RatioGet(void)             { return m_ratio; };
			void        ThicknessSet(etkFloat_t thickness) { m_thickness = thickness; };
			etkFloat_t  ThicknessGet(void)                 { return m_thickness; };
			void        ShadowOutputSet(etkFloat_t shadowOutput) { m_shadowOutput = shadowOutput; };
			etkFloat_t  ShadowOutputGet(void)                    { return m_shadowOutput; };
			void        ShadowInputSet(etkFloat_t shadowInput) { m_shadowInput = shadowInput; };
			etkFloat_t  ShadowInputGet(void)                   { return m_shadowInput; };
			void        NbRaySet(int32_t nbRay) { m_nbRay = nbRay; };
			int32_t     nbRayGet(void)          { return m_nbRay; };
		public:
			virtual void Draw(ewol::OObject2DColored &OObjects);
	};
};

#endif

