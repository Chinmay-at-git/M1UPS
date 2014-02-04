#pragma once

#include "geometry.hpp"
#include "plane.hpp"
#include <cmath>
#include <cassert>

/** @ingroup Raytracer
 *  Cone geometric object
 */
class Cone : public Geometry {
private:
    /// The position of the vertex
    Vector3D m_vertex;
    /// The axis of the cone
    Vector3D m_axis;
    /// The radius at the base
    float m_radius;
    /// The height of the cone
    float m_height;

    /// The cos(angle) of the cone
    float m_costheta;

    /**
     * @brief compute_normal
     * @param p_
     * @return The normal of the cone at point p_
     */
    Vector3D compute_normal(const Vector3D & p_) const{
        // compute the cone normal at point p_
        Vector3D e = p_ - m_vertex;
        Vector3D h = e.cross_product(m_axis);
        Vector3D n = e.cross_product(h);
        return n.normalize();
    }

    /**
     * @brief get_clip_points
     * @param ray_
     * @param ipoints
     * @param t
     * @return the number of clipping position on the ray (0 to 2)
     */
    int get_clip_points(Ray& ray_, Diff_Geom ipoints[2], float t[2]) const{
        int numintersection = 0;
        Vector3D E = ray_.ori() - m_vertex;
        float AdD = m_axis.dot(ray_.dir());
        float cosSqr = m_costheta*m_costheta;
        float AdE = m_axis.dot(E);
        float DdE = ray_.dir().dot(E);
        float EdE = E.dot(E);
        float c2 = AdD*AdD-cosSqr;
        float c1 = AdD*AdE - cosSqr*DdE;
        float c0 = AdE*AdE - cosSqr*EdE;
        float dot;
        if (std::fabs(c2)>0) {
            float discr = c1*c1 - c0*c2;
            float invC2 = 1.f/c2;
            if (discr < 0) {
                // No intersection
                return  0;
            } else if (discr > 0) {
                // two distinct intersections
                float root = std::sqrt(discr);
                // entry point
                t[numintersection] = (-c1 + root) * invC2;
                ipoints[numintersection].set_pos(ray_.at(t[numintersection]));
                E = ipoints[numintersection].pos() - m_vertex;
                dot = E.dot(m_axis);
                if ( (dot > 0) && (dot <= m_height))
                {
                    Vector3D normal=compute_normal(ipoints[numintersection].pos());
                    ipoints[numintersection].set_normal(normal);
                    ipoints[numintersection].set_t(t[numintersection]);
                    ++numintersection;
                }

                // exit point
                t[numintersection] = (-c1 - root) * invC2;
                ipoints[numintersection].set_pos(ray_.at(t[numintersection]));
                E = ipoints[numintersection].pos() - m_vertex;
                dot = E.dot(m_axis);
                if ( (dot > 0)  && (dot <= m_height))
                {
                    Vector3D normal=compute_normal(ipoints[numintersection].pos());
                    ipoints[numintersection].set_normal(normal);
                    ipoints[numintersection].set_t(t[numintersection]);
                    ++numintersection;
                }

                return numintersection;
          } else {
                // one reapeated intersection : ray is tangent to the cone
                // may be return 0 instead of an intersection ?
                return 0;
                t[numintersection] = -c1 * invC2;
                ipoints[numintersection].set_pos(ray_.at(t[numintersection]));
                E = ipoints[numintersection].pos() - m_vertex;
                dot = E.dot(m_axis);
                if ( (dot > 0) && (dot <= m_height)) {
                    Vector3D normal=compute_normal(ipoints[numintersection].pos());
                    ipoints[numintersection].set_normal(normal);
                    ipoints[numintersection].set_t(t[numintersection]);
                    ++numintersection;
                }
                return numintersection;
           }
        } else if (std::fabs(c1) > 0) {
            // the ray is on the boundary of the cone
            // we consider no intersection
            // TODO : check this for CSG
            return 0;
        } else {
            //return false;
            // Cone contains ray V+tD
            // The ray intersect the cone exactly at its vertex :(
            ipoints[numintersection].set_pos(m_vertex);
            ipoints[numintersection].set_normal(-m_axis);
            E = ray_.ori() - m_vertex;
            t[numintersection] = ( (E.dot(ray_.dir())<0) ? std::sqrt(EdE) : -std::sqrt(EdE) ) ;
            ipoints[numintersection].set_t(t[numintersection]);
            ++numintersection;
            // TODO compute cap plane intersection

            // check with cap plane
            Plane cap(m_vertex + m_axis * m_height, m_axis);
            IntervalSet capset;
            if (cap.clip(ray_, capset)) {
                if (capset.bounds()[0].t < t[numintersection-1]) {
                    t[numintersection] = t[numintersection-1];
                    ipoints[numintersection] = ipoints[numintersection-1];
                    --numintersection;
                }
                ipoints[numintersection] = *(capset.bounds()[0].data);
                delete capset.bounds()[0].data;
                delete capset.bounds()[1].data;
                return 2;
            } else {
                // must never reach this point !
                assert(false);
                return 0;
            }
        }
    }

public:

    Cone () : m_vertex(0.f,0.f, 1.f), m_axis(0.f, 0.f, -1.f), m_radius (1.f), m_height(1.f) {
        m_costheta = std::cos(std::atan2(m_radius, m_height));

    }

    Cone (const Vector3D &center_, const Vector3D& vertex_, float radius_) : m_vertex(vertex_), m_radius (radius_) {
        m_axis = center_ - m_vertex;
        m_height = m_axis.norm();
        m_axis =   m_axis.normalize();
        m_costheta = std::cos(std::atan2(m_radius, m_height));
    }


    /**
     * @brief intersect a ray and a cone.
     * @param ray_ the ray
     * @param p_diff_geom_ the result of the intersection
     * @return true if the ray intersects the cone
     * Modifies the ray_.max_t() value, intersect only if the intersection
     * is before ray_.max_t()
     *
     * Adapted from http://www.geometrictools.com/LibMathematics/Intersection/Wm5IntrLine3Cone3.cpp
     */
    bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
        Diff_Geom ipoints[2];
        float t[2];

        int numintersection = get_clip_points(ray_, ipoints,  t);
        /* numintersection == 2 -> two intersections with the cone above vertex :
         *          return the smallest t
         * numintersection == 1 -> one intersection with the cone above vertex :
         *          check cap plane (that will add an intersection point) before choosing the smalest positive t
         * numintersection == 0 -> no intersection
         */
        if (numintersection == 0)
            return false;
        else if (numintersection == 2) {
            int i=0;
            while ( (i<numintersection) && (t[i] < ray_.ray_epsilon())  )
                i++;
            if ( (i < numintersection) && (t[i] < ray_.max_t()) ) {
                *p_diff_geom_ = ipoints[i];
                ray_.set_max_t (t[i]);
                return true;
            } else
                return false;
        } else {
            // check with cap plane
            Plane cap(m_vertex + m_axis * m_height, m_axis);
            Diff_Geom plane_intersection;
            if (cap.intersect(ray_, &plane_intersection)) {
                if (ray_.max_t() < t[0]) {
                    // beware of in/out status
                    *p_diff_geom_ = plane_intersection;
                    return true;
                }
            }
            if (t[0] > ray_.ray_epsilon()) {
                // beware of in/out status
                *p_diff_geom_ = ipoints[0];
                ray_.set_max_t(t[0]);
                return true;
            } else
                return false;
        }
        return false;
    }


    /**
     * @brief clip a ray by a Cone.
     * @param ray_ the ray to clip
     * @param bounds ray sorted bounds of the resulting clipping segment.
     * @return  true if ray was clipped. bounds parameter is filld by this method
     *
     * For simple convex objects, there is two values in  bounds that represent in and out events.
     * An in event is whe the ray enters the geometry, an out is when the ray leaves the geometry.
     *
     * Adapted from http://www.geometrictools.com/LibMathematics/Intersection/Wm5IntrLine3Cone3.cpp
     *
     */
    bool clip(Ray& ray_, IntervalSet &bounds) const {
        Diff_Geom ipoints[2];
        float t[2];

        int numintersection = get_clip_points(ray_, ipoints,  t);
        if (numintersection == 0)
            return false;
        else if (numintersection == 2) {
            Diff_Geom *in = new Diff_Geom(ipoints[0].pos(), ipoints[0].normal(), t[0]);
            Diff_Geom *out = new Diff_Geom(ipoints[1].pos(), ipoints[1].normal(), t[1]);
            bounds.add(in, out);
            return true;
        } else {
            Diff_Geom *in, *out;
            IntervalSet capset;
            // check with cap plane
            Plane cap(m_vertex + m_axis * m_height, m_axis);
            if (cap.clip(ray_, capset) ) {
				/* Beuark mais ca facilite la gestion mémoire ... */
                Diff_Geom *tmp =capset.bounds()[0].data;
				in = new Diff_Geom(*tmp);
                if (in->t()< t[0]) {
                    out = new Diff_Geom(ipoints[0].pos(), ipoints[0].normal(), t[0]);
                } else {
                    out = in;
                    in = new Diff_Geom(ipoints[0].pos(), ipoints[0].normal(), t[0]);
                }

                bounds.add(in, out);
                return true;
            } else {
                return false;
            }
        }
    }
};
