#pragma once

#include "geometry.hpp"
#include "plane.hpp"

/** @ingroup Raytracer 
 *  Cylinder geometric object
 */
class Cylinder : public Geometry {
private:

    Vector3D m_base;
    Vector3D m_axis;
    float m_radius;
    float m_length;
	
public:

        Cylinder () : m_radius (0.f) {
	}

        Cylinder (const Vector3D& center_, const Vector3D& axis_, float radius_, float length_) : m_base (center_), m_axis(axis_.normalize()), m_radius (radius_), m_length(length_/2.f) {
	}

	/**
	   modifies the ray_.max_t() value, intersect only if the intersection
	   is before ray_.max_t()
	*/
	bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
            Vector3D centerToRay = ray_.ori() - m_base;
            Vector3D intersectionPlane = ray_.dir().cross_product(m_axis);
            Vector3D vd;
            float ln = intersectionPlane.norm();
            float d;

            if  ( ln < Ray::ray_epsilon() ) {	/* ray parallel to cyl	*/
                d	 = centerToRay.dot(m_axis);
                vd = centerToRay - m_axis*d;
                d = vd.norm();
                /* (d <= radius) if ray is in cyl*/
                if (d <= m_radius) {
                    if  (ray_.dir().dot(m_axis) > 0)  {
                        /* intersect base cap */
                        Plane cap(m_base+m_axis*-m_length, m_axis*-1.f);
                        return cap.intersect(ray_, p_diff_geom_);
                    } else {
                        /* intersect top cap */
                        Plane cap(m_base+m_axis*m_length, m_axis);
                        return cap.intersect(ray_, p_diff_geom_);
                    }
                }
                return false;
            }

            intersectionPlane = intersectionPlane.normalize();
            d = fabsf(centerToRay.dot(intersectionPlane));
            bool hit = (d <= m_radius);
            if  (hit) {				/* if ray hits cylinder */
                vd = centerToRay.cross_product(m_axis);
                float t = - vd.dot(intersectionPlane)/ln;
                vd = intersectionPlane.cross_product(m_axis);
                vd = vd.normalize();
                float s = fabsf(sqrtf(m_radius*m_radius - d*d) / ray_.dir().dot(vd) );

                float tin = t-s;
                float tout = t+s;
                if ((tout < Ray::ray_epsilon()) || (tin > ray_.max_t())) {
                    return false;
                }

                /* Compute intersection point and normal. Beware of capping */
                float isect_t;
                float isect_h;
                Vector3D isect_p;

                if (tin >= Ray::ray_epsilon()) {
                    isect_t = tin;
                    isect_p = ray_.at (isect_t);
                    Vector3D pl = isect_p - m_base;
                    isect_h = m_axis.dot(pl);
                    if ( (isect_h <= m_length) && (isect_h >= -m_length) ) {
                        /*side is intersected*/
                        Vector3D pp = m_axis*isect_h;
                        ray_.set_max_t (isect_t);
                        Vector3D normal = (pl - pp).normalize();
                        *p_diff_geom_ = Diff_Geom (isect_p, normal);
                        return true;
                    } else {
                        float cfh = isect_h;
                        isect_t = tout;
                        if (isect_t > ray_.max_t()) {
                                return false;
                        }
                        isect_p = ray_.at (isect_t);
                        pl = isect_p - m_base;
                        isect_h = m_axis.dot(pl);
                        if ( (isect_h > m_length) || (isect_h <-m_length) ) {
                            return false;
                        }
                        if (cfh < -m_length) {
                            /* intersect base cap */
                            Plane cap(m_base+m_axis*-m_length, m_axis*-1.f);
                            return cap.intersect(ray_, p_diff_geom_);
                        } else {
                            /* intersect top cap */
                            Plane cap(m_base+m_axis*m_length, m_axis);
                            return cap.intersect(ray_, p_diff_geom_);
                        }
                    }
                } else {
                    /* intersect only cap */
                    isect_t = tout;
                    isect_p = ray_.at (isect_t);
                    Vector3D pl = isect_p - m_base;
                    isect_h = m_axis.dot(pl);
                    if ( (ray_.dir().dot(m_axis) > 0) &&  (isect_h > -m_length)) {
                        /* intersect base cap */
                        Plane cap(m_base+m_axis*-m_length, m_axis*-1.f);
                        return cap.intersect(ray_, p_diff_geom_);
                    } else if ( (ray_.dir().dot(m_axis) <= 0) &&  (isect_h < m_length)) {
                        /* intersect base cap */
                        Plane cap(m_base+m_axis*m_length, m_axis);
                        return cap.intersect(ray_, p_diff_geom_);
                    } else {
                        return false;
                    }
                }
            }
            return false;
	}
};
