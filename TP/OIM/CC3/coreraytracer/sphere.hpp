#pragma once

#include "geometry.hpp"

/** @ingroup Raytracer 
 *  Sphere geometric object
 */
class Sphere : public Geometry {
private:

	Vector3D m_center;
	float m_radius;
	
public:

	Sphere () : m_radius (0.f) {
	}

	Sphere (const Vector3D& center_, float radius_) : m_center (center_), m_radius (radius_) {
	}

    /**
     * @brief intersect a sphere.
     * @param ray_ the ray
     * @param p_diff_geom_ the result of the intersection
     * @return true if the ray intersects the geometry
     * Modifies the ray_.max_t() value, intersect only if the intersection
     * is before ray_.max_t()
     */
    bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
		Vector3D ori_local = ray_.ori() - m_center;

		float dir_dot_ori = ray_.dir().dot (ori_local);
		float delta = dir_dot_ori * dir_dot_ori - (ori_local.dot (ori_local) - m_radius * m_radius);

		if (delta < 0.f) {
			return false;
		}

		float sqrt_delta = sqrtf (delta);

		float t;

		float t2 = -dir_dot_ori + sqrt_delta;

		//to avoid auto intersection
		if (t2 < Ray::ray_epsilon()) {
			//t1 < t2 => no solution after the origin of the ray
			return false;
		}

		float t1 = -dir_dot_ori - sqrt_delta;
        if (t1 > Ray::ray_epsilon()) {
			//t1 < t2
			t = t1;
		} else {
            t = t2;
		}

		if (t > ray_.max_t()) {
			return false;
		}

		ray_.set_max_t (t);

        Vector3D isect_p = ray_.at(t);

		Vector3D normal = (isect_p - m_center).normalize();

        *p_diff_geom_ = Diff_Geom (isect_p, normal, t);

		return true;
	}

    /**
     * @brief clip a ray by a sphere.
     * @param ray_ the ray to clip
     * @param bounds ray sorted bounds of the resulting clipping segment.
     * @return  true if ray was clipped. bounds parameter is filld by this method
     *
     * For simple convex objects, there is two values in  bounds that represent in and out events.
     * An in event is whe the ray enters the geometry, an out is when the ray leaves the geometry.
     */
   bool clip(Ray& ray_, IntervalSet &bounds) const {
        //std::cerr << "Clip Sphere" << std::endl;
        Vector3D ori_local = ray_.ori() - m_center;

        float dir_dot_ori = ray_.dir().dot (ori_local);
        float delta = dir_dot_ori * dir_dot_ori - (ori_local.dot (ori_local) - m_radius * m_radius);

        // do not consider double root
        if (delta <= 0.f) {
            return false;
        }

        float sqrt_delta = sqrtf (delta);
        // t is the entry point
        float t = -dir_dot_ori - sqrt_delta;
        Vector3D isect_p = ray_.at(t);
        Vector3D normal = (isect_p - m_center).normalize();
        Diff_Geom *in = new Diff_Geom(isect_p, normal, t);

        t = -dir_dot_ori + sqrt_delta;
        // t is the leaving point
        isect_p = ray_.at(t);
        normal = (isect_p - m_center).normalize();
        Diff_Geom *out = new Diff_Geom(isect_p, normal, t);
        bounds.add(in, out);

        return true;
    }

};
