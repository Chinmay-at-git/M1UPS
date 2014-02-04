#pragma once
/** @defgroup Raytracer Simple Raytracer
 *  Raytracing library with simple functionalities
 */


#include "light.hpp"
#include "camera.hpp"
#include "primitive.hpp"

#include "ray.hpp"
#include "isect.hpp"

#include <vector>

using namespace std;


/** @ingroup Raytracer 
 *  Scene definition
 */
class Scene {
private:

	vector<Light *> m_p_lights;

	Camera * m_p_camera;

	vector<Primitive *> m_p_prims;

public:

	Scene () : m_p_camera (NULL) {
	}

	void set_camera (Camera * p_camera_) {
		m_p_camera = p_camera_;
	}

	void add_primitive (Primitive * p_prim_) {
		m_p_prims.push_back (p_prim_);
	}

	void add_light (Light * p_light_) {
		m_p_lights.push_back (p_light_);
	}

	const Camera * p_camera() const {
		return m_p_camera;
	}

	const vector<Light *>& p_lights () const {
		return m_p_lights;
	}

	const vector<Primitive *>& p_prims () const {
		return m_p_prims;
	}

	bool intersect (Ray& ray_, Isect * p_isect_) const {
		Isect isect;		
		bool has_isect = false;
		
		for (vector<Primitive *>::const_iterator it = m_p_prims.begin(); it != m_p_prims.end(); it++) {
			if ((*it)->intersect (ray_, &isect)) {
				has_isect = true;
				*p_isect_ = isect;
			}
		}

		return has_isect;
	}

	/**
	   test the visibility between a point and a light
	   @return true if they are mutually visible
	 */
	bool test_visibility (const Vector3D& pos_, Light * p_light_) const {
        Vector3D dir = p_light_->pos() - pos_;
        float l = dir.norm();
        dir = dir.normalize();
        Ray ray (pos_+dir*0.001f, dir);
        ray.set_max_t(l);
		Isect isect;
		
		for (vector<Primitive *>::const_iterator it = m_p_prims.begin(); it != m_p_prims.end(); it++) {
			if ((*it)->intersect (ray, &isect)) {
				return false;
			}
		}
		return true;
	}
	
};
