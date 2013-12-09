#pragma once

#include "vector3d.hpp"
#include <memory>

/** @ingroup Raytracer 
 *  Geometrical information at a ray/object intersection point
 */
struct Diff_Geom {
private:
    /// The 3D position
	Vector3D m_pos;
    /// The normal
	Vector3D m_normal;
    /// The coordinate on the ray
    float m_t;

public:

    Diff_Geom (): m_pos (0.f), m_normal (0.f), m_t(0.f) {
	} 

    Diff_Geom (const Vector3D& pos_, const Vector3D& normal_, float t) : m_pos (pos_), m_normal (normal_), m_t(t) {
	}
	
    Diff_Geom (const Diff_Geom& other) : m_pos (other.m_pos), m_normal (other.m_normal), m_t(other.m_t) {
	}

    Diff_Geom& operator=(const Diff_Geom& other) {
                    m_pos = other.m_pos;
                    m_normal = other.m_normal;
                    m_t = other.m_t;
                    return (*this);
    }
	const Vector3D& pos () const {
		return m_pos;
	}

	const Vector3D& normal () const {
		return m_normal;
	}

    float t() const {
        return m_t;
    }

    void set_pos(const Vector3D & pos_) {
        m_pos = pos_;
    }

    void set_normal(const Vector3D & normal_) {
        m_normal = normal_;
    }

    void set_t(float t) {
        m_t = t;
    }

};

	
