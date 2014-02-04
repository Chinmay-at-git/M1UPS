#pragma once

#include "geometry.hpp"

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
	   modifies the ray_.max_t() value, intersect only if the intersection
	   is before ray_.max_t()
	*/
	bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
		float t = (-m_offset - ray_.ori().dot (m_normal)) / ray_.dir().dot (m_normal);

		if (t < Ray::ray_epsilon() || t > ray_.max_t()) {
			return false;
		}

		ray_.set_max_t (t);

		*p_diff_geom_ = Diff_Geom (ray_.at (t), m_normal);

		return true;
	}
};
