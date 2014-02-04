#pragma once

#include "material.hpp"

/** @ingroup Raytracer 
 *  Metallic material
 */
class Metal : public Material {
private:

	Color m_kd, m_kr;
	
public:

	Metal (const Color& kd_, const Color& kr_) : m_kd (kd_), m_kr (kr_) {
	}

	BSDF evaluate (const Diff_Geom& diff_geom_) const {
		return BSDF::init_pure_refl (diff_geom_.normal(), m_kd, m_kr);
	}
};
