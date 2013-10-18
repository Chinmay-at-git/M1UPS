#pragma once

#include "material.hpp"

/** @ingroup Raytracer 
 *  Glass material
 */
class Glass : public Material {
private:

	Color m_kr, m_kt;
	float m_ior;
	
public:

	Glass (const Color& kr_, const Color& kt_, float ior_) : m_kr (kr_), m_kt (kt_), m_ior (ior_) {
	}

	BSDF evaluate (const Diff_Geom& diff_geom_) const {
		return BSDF::init_fresnel (diff_geom_.normal(), m_kr, m_kt, m_ior);
	}
};
