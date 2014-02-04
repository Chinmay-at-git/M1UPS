#pragma once

#include "vector3d.hpp"
#include "color.hpp"

#include <limits>


/** @ingroup Raytracer 
 *  Ray definition
 */
class Ray {
private:

	Vector3D m_ori;
	Vector3D m_dir;

	int m_depth;
	Color m_importance;

	float m_max_t;

public:

    Ray () : m_depth (0), m_max_t (std::numeric_limits<float>::max()) {
	}

	/**
	   for a camera ray
	*/
	Ray (const Vector3D& ori_, const Vector3D& dir_) : m_ori (ori_), m_dir (dir_),
													   m_depth (0), m_importance (1.f),
													   m_max_t (std::numeric_limits<float>::max()) {		
	}

	/**
	   for a ray obtained from another ray after scattering at a surface
	   @param previous_ray_
	   @param bsdf_value_ the bsdf value at the surface the couple of rays
       @param ori_
       @param dir_
	*/
	Ray (const Ray& previous_ray_,
		 const Color& bsdf_value_,
		 const Vector3D& ori_,
		 const Vector3D& dir_) : m_ori (ori_), m_dir (dir_),
								 m_depth (previous_ray_.depth() + 1),
								 m_importance (previous_ray_.importance() * bsdf_value_),
								 m_max_t (std::numeric_limits<float>::max()) {		
	}

	const Vector3D& ori () const {
		return m_ori;
	}

	const Vector3D& dir () const {
		return m_dir;
	}

	int depth () const {
		return m_depth;
	}

	const Color& importance () const {
		return m_importance;
	}

	float max_t () const {
		return m_max_t;
	}

	void set_max_t (float max_t_) {
		m_max_t = max_t_;
	}

	Vector3D at (float t_) const {
		return m_ori + m_dir * t_;
	}

	/** to avoid auto intersection */
	static float ray_epsilon() {
		return 0.001f;
	}
	
	
};
