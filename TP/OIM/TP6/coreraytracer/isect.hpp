#pragma once

#include "diff_geom.hpp"
#include "bsdf.hpp"


/** @ingroup Raytracer 
 *  Intersection point definition 
 */
struct Isect {
private:
	Diff_Geom m_dg;
	BSDF m_bsdf;


public:

	Isect () {
	}

	Isect (const Diff_Geom& dg_, const BSDF& bsdf_) : m_dg (dg_), m_bsdf (bsdf_) {
	}

	const Diff_Geom& dg() const {
		return m_dg;
	}

	const BSDF& bsdf() const {
		return m_bsdf;
	}
};

	
