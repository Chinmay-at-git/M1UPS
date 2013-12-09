#pragma once

#include "vector3d.hpp"
#include "ray.hpp"

/** @ingroup Raytracer 
 *  Viewpoint management
 */
class Camera {
private:

	/** position of the observator, starting point of the rays */
	Vector3D m_pos; 
	
	/** center of image plane */
	Vector3D m_center; 

	Vector3D m_x, m_y;

	int m_x_res, m_y_res;

public:

	Camera () : m_x_res (0), m_y_res (0) {
	}

	/**
	   fov in degrees
	*/
	Camera (const Vector3D& pos_, const Vector3D& aim_, const Vector3D& up_,
			float fov_, int x_res_, int y_res_) : m_pos (pos_), m_x_res (x_res_), m_y_res (y_res_) {
		Vector3D z = (aim_ - pos_).normalize();
		m_x = (z.cross_product (up_)).normalize();
		m_y = (m_x.cross_product (z)) * (float(y_res_) / float (x_res_)); //aspect ratio

		m_center = m_pos + z * (1.f / tanf ((fov_ * (float)M_PI / 180.f) * 0.5f));
	}

	Ray ray_for_pixel (int x_, int y_) const {
		float delta_x = float((x_ + 0.5f) - m_x_res * 0.5f) / (m_x_res * 0.5f);
		float delta_y = float((y_ + 0.5f) - m_y_res * 0.5f) / (m_y_res * 0.5f);

		//-delta_y to have the first row correspond to the top of the image
		return Ray (m_pos, ((m_center - (m_x * delta_x) - (m_y * delta_y)) - m_pos).normalize());
	}

	Ray ray_for_screen_coords (float x_, float y_) const {
		float delta_x = (x_ - m_x_res * 0.5f) / (m_x_res * 0.5f);
		float delta_y = (y_ - m_y_res * 0.5f) / (m_y_res * 0.5f);

		//-delta_y to have the first row correspond to the top of the image
		return Ray (m_pos, ((m_center - (m_x * delta_x) - (m_y * delta_y)) - m_pos).normalize());
	}

	int x_res () const {
		return m_x_res;
	}

	int y_res () const {
		return m_y_res;
	}
};

	
