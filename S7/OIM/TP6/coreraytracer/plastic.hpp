#pragma once

#include "material.hpp"

/** @ingroup Raytracer 
 *  Plastic material
 */
class Plastic : public Material {
private:

	Color m_kd;
	Color m_ks;
	float m_shininess;
	
public:

        Plastic (const Color& kd_, const Color& ks_, float shininess_) : m_kd (kd_), m_ks (ks_), m_shininess (shininess_) {
	}

	BSDF evaluate (const Diff_Geom& diff_geom_) const {
		return BSDF::init_blinn_phong (diff_geom_.normal(), m_kd, m_ks, m_shininess);
	}
};
