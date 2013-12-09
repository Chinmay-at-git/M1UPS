#pragma once

#include "geometry.hpp"
#include <cmath>

/** @ingroup Raytracer 
 *  Plane geometric object
 */
class Plane : public Geometry {
private:

	Vector3D m_normal;
	float m_offset;
	
public:

    Plane (const Vector3D& pos_, const Vector3D& normal_) {
        m_normal = normal_.normalize();
		m_offset = -m_normal.dot (pos_);
	}

    /**
     * @brief intersect a plan.
     * @param ray_ the ray
     * @param p_diff_geom_ the result of the intersection
     * @return true if the ray intersects the geometry
     * Modifies the ray_.max_t() value, intersect only if the intersection
     * is before ray_.max_t()
     */
    bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
        float d = ray_.dir().dot (m_normal);

        if (std::fabs(d) < ray_.ray_epsilon())
            return false;

        float t = (-m_offset - ray_.ori().dot (m_normal)) / d;

		if (t < Ray::ray_epsilon() || t > ray_.max_t()) {
			return false;
		}

		ray_.set_max_t (t);
        *p_diff_geom_ = Diff_Geom (ray_.at (t), m_normal, t);

		return true;
	}

    /**
     * @brief clip a ray by a plane.
     * @param ray_ the ray to clip
     * @param bounds ray sorted bounds of the resulting clipping segment.
     * @return  true if ray was clipped. bounds parameter is filld by this method
     *
     * For simple convex objects, there is two values in  bounds that represent in and out events.
     * An in event is whe the ray enters the geometry, an out is when the ray leaves the geometry.
     */
    bool clip(Ray& ray_, IntervalSet &bounds) const {
        float d = ray_.dir().dot (m_normal);

        if (std::fabs(d) < ray_.ray_epsilon())
            return false;

        float t = (-m_offset - ray_.ori().dot (m_normal)) / d;
        Vector3D point = ray_.at(t);
        Diff_Geom *in = new Diff_Geom(point, m_normal, t);
        Diff_Geom *out = new Diff_Geom(point, m_normal, t+ray_.ray_epsilon());
        bounds.add(in, out);
        return true;
    }
};
