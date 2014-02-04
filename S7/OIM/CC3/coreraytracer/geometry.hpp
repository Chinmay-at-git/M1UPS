#pragma once

#include "ray.hpp"
#include "diff_geom.hpp"
#include "intervalset.hpp"

/** @ingroup Raytracer 
 *  Abstract class for geometric object
 */
class Geometry {
protected :
    /**
     * @brief garbage for easy memory management
     */
	static std::vector<Diff_Geom*> garbage;

public:
	virtual ~Geometry(){}

    /**
     * @brief intersect a geometric object.
     * @param ray_ the ray
     * @param p_diff_geom_ the result of the intersection
     * @return true if the ray intersects the geometry
     * Modifies the ray_.max_t() value, intersect only if the intersection
     * is before ray_.max_t()
     */
    virtual bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const =0;


    /**
     * @brief clip a ray by a geometry.
     * @param ray_ the ray to clip
     * @param bounds ray sorted bounds of the resulting clipping segment.
     * @return  true if ray was clipped. bounds parameter is filld by this method
     *
     * For simple convex objects, there is two values in  bounds that represent in and out events.
     * An in event is whe the ray enters the geometry, an out is when the ray leaves the geometry.
     */
    virtual bool clip(Ray& ray_, IntervalSet &bounds) const =0;
};
