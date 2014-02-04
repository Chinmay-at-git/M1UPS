#pragma once

#include "vector3d.hpp"

/** @ingroup Raytracer 
 *  Geometrical information
 */
struct Diff_Geom {
private:
	Vector3D m_pos;
	Vector3D m_normal;

public:

	Diff_Geom () {
	}

	Diff_Geom (const Vector3D& pos_, const Vector3D& normal_) : m_pos (pos_), m_normal (normal_) {
	}

	const Vector3D& pos () const {
		return m_pos;
	}

	const Vector3D& normal () const {
		return m_normal;
	}
};

	
