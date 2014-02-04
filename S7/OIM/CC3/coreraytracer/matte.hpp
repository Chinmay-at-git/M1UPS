#pragma once

#include "material.hpp"

/** @ingroup Raytracer 
 *  Matte material
 */
class Matte : public Material {
private:

	Color m_kd;
	
public:

	Matte (const Color& kd_) : m_kd (kd_) {
	}

	BSDF evaluate (const Diff_Geom& diff_geom_) const {
		return BSDF::init_diffuse (diff_geom_.normal(), m_kd);
	}
};
