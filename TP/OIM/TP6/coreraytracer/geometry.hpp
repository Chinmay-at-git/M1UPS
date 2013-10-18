#pragma once

#include "ray.hpp"
#include "diff_geom.hpp"

/** @ingroup Raytracer 
 *  Abstract class for geometric object
 */
class Geometry {
public:

	/**
	   modifies the ray_.max_t() value, intersect only if the intersection
	   is before ray_.max_t()
	*/
	virtual bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const =0;
};
