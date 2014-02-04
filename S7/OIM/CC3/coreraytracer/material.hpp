#pragma once

#include "bsdf.hpp"
#include "diff_geom.hpp"

/** @ingroup Raytracer 
 *  Abstract class for material
 */
class Material {
public:
	virtual ~Material(){}
	virtual BSDF evaluate (const Diff_Geom& diff_geom_) const =0;
};
