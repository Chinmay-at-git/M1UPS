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


    /**
     * @brief get_clip_points
     * @param ray_
     * @param ipoints
     * @param t
     * @return the number of clipping position on the ray (0 to 2)
     *
     * adapted from http://www.geometrictools.com/LibMathematics/Intersection/Wm5IntrLine3Cylinder3.cpp
     */
    int get_clip_points(Ray& ray_, Diff_Geom ipoints[2], float t[2]) const{
        Vector3D U, V, W = m_axis;
        Vector3D::make_basis(U, V, W);
        float rSqr = m_radius*m_radius;

        // convert incoming line origin to cylinder coordinates
        Vector3D diff = ray_.ori() - m_base;
        Vector3D P(U.dot(diff), V.dot(diff), W.dot(diff));
        // Get the z-value, in cylinder coordinates, of the incoming line's
        // unit-length direction.
        float dz = W.dot(ray_.dir());

        if (std::fabs(dz) >= 1.f - ray_.ray_epsilon()) { // 0?
            // The line is parallel to the cylinder axis.  Determine if the line
            // intersects the cylinder end disks.
            float radialSqrDist = rSqr - P.x()*P.x() - P.y()*P.y();
            if (radialSqrDist < 0.f) { // epsilon ?
                // Line outside the cylinder, no intersection.
                return 0; // 0
            }
            // Line intersects the cylinder end disks.
            // todo verify normals
            if (dz > 0.f) {
                t[0] = -P.z() - m_length;
                ipoints[0].set_t(t[0]);
                ipoints[0].set_pos(ray_.at(t[0]));
                ipoints[0].set_normal(m_axis);
                t[1] = -P.z() + m_length;
                ipoints[1].set_t(t[1]);
                ipoints[1].set_pos(ray_.at(t[1]));
                ipoints[1].set_normal(-m_axis);
            } else {
                t[0] = P.z() - m_length;
                ipoints[0].set_t(t[0]);
                ipoints[0].set_pos(ray_.at(t[0]));
                ipoints[0].set_normal(-m_axis);
                t[1] = P.z() + m_length;
                ipoints[1].set_t(t[1]);
                ipoints[1].set_pos(ray_.at(t[1]));
                ipoints[1].set_normal(m_axis);
            }
            return 2;
        }
        // convert incoming line unit-length direction to cylinder coordinates
        Vector3D D(U.dot(ray_.dir()),V.dot(ray_.dir()),dz);
        float a0, a1, a2, discr, root, inv, tValue;
        if (std::fabs(D.z()) <= ray_.ray_epsilon()) { // 0?
            // The line is perpendicular to the cylinder axis.
            if (std::fabs(P.z()) > m_length) {
                // Line is outside the planes of the cylinder end disks.
                return 0;
            }
            // Test intersection of line P+t*D with infinite cylinder
            // x^2+y^2 = r^2.  This reduces to computing the roots of a
            // quadratic equation.  If P = (px,py,pz) and D = (dx,dy,dz),
            // then the quadratic equation is
            //   (dx^2+dy^2)*t^2 + 2*(px*dx+py*dy)*t + (px^2+py^2-r^2) = 0
            a0 = P.x()*P.x() + P.y()*P.y() - rSqr;
            a1 = P.x()*D.x() + P.y()*D.y();
            a2 = D.x()*D.x() + D.y()*D.y();
            discr = a1*a1 - a0*a2;
            if (discr < 0.f) {
                // Line does not intersect cylinder.
                return 0;
            }
            else if (discr > 0) { // epsilon ?
                // Line intersects cylinder in two places.
                root = std::sqrt(discr);
                inv = 1.f/a2;
                t[0] = (-a1 - root)*inv;
                ipoints[0].set_t(t[0]);
                ipoints[0].set_pos(ray_.at(t[0]));
                Vector3D cp = ipoints[0].pos() - m_base;
                Vector3D ap = m_axis.cross_product(cp);
                Vector3D nl = ap.cross_product(m_axis);
                ipoints[0].set_normal(nl.normalize());
                t[1] = (-a1 + root)*inv;
                ipoints[1].set_t(t[1]);
                ipoints[1].set_pos(ray_.at(t[1]));
                cp = ipoints[1].pos() - m_base;
                ap = m_axis.cross_product(cp);
                nl = ap.cross_product(m_axis);
                ipoints[1].set_normal(nl.normalize());
                return 2;
            }
            else
            {
                // Line is tangent to the cylinder.
                //t[0] = -a1/a2;
                //return 1;
                return 0;
            }
        }
        // Test plane intersections first.
        int quantity = 0;
        inv = 1.0f/D.z();

        float t0 = (-m_length - P.z())*inv;
        float xTmp = P.x() + t0*D.x();
        float yTmp = P.y() + t0*D.y();
        if (xTmp*xTmp + yTmp*yTmp <= rSqr) {
            // Planar intersection inside the top cylinder end disk.
            t[quantity] = t0;
            ipoints[quantity].set_t(t[quantity]);
            ipoints[quantity].set_pos(ray_.at(t[quantity]));
            ipoints[quantity].set_normal(m_axis); // TODO check normal
            ++quantity;
        }

        float t1 = (+m_length - P.z())*inv;
        xTmp = P.x() + t1*D.x();
        yTmp = P.y() + t1*D.y();
        if (xTmp*xTmp + yTmp*yTmp <= rSqr) {
            // Planar intersection inside the bottom cylinder end disk.
            t[quantity] = t1;
            ipoints[quantity].set_t(t[quantity]);
            ipoints[quantity].set_pos(ray_.at(t[quantity]));
            ipoints[quantity].set_normal(-m_axis); // TODO check normal
            ++quantity;
        }

        if (quantity == 2) {
            // Line intersects both top and bottom cylinder end disks.
            if (t[0] > t[1]) {
                float save = t[0];
                t[0] = t[1];
                t[1] = save;
                Diff_Geom gds = ipoints[0];
                ipoints[0] = ipoints[1];
                ipoints[1] = gds;
            }
            return 2;
        }
        // If quantity == 1, then the line must intersect cylinder wall in a
        // single point somewhere between the end disks.  This case is detected
        // in the following code that tests for intersection between line and
        // cylinder wall.
        a0 = P.x()*P.x() + P.y()*P.y() - rSqr;
        a1 = P.x()*D.x() + P.y()*D.y();
        a2 = D.x()*D.x() + D.y()*D.y();
        discr = a1*a1 - a0*a2;
        if (discr < 0.f) { // epsilon ?
            // Line does not intersect cylinder wall.
            //assertion(quantity == 0, "Unexpected condition\n");
            return 0;
        } else if (discr > 0.f) { // epsilon ?
            root = std::sqrt(discr);
            inv = 1.f/a2;
            tValue = (-a1 - root)*inv;
            if (t0 <= t1) {
                if (t0 <= tValue && tValue <= t1) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            } else {
                if (t1 <= tValue && tValue <= t0) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            }

            if (quantity == 2) {
                // Line intersects one of the cylinder end disks and once on the
                // cylinder wall.
                if (t[0] > t[1]) {
                    float save = t[0];
                    t[0] = t[1];
                    t[1] = save;
                    Diff_Geom gds = ipoints[0];
                    ipoints[0] = ipoints[1];
                    ipoints[1] = gds;
                }
                return 2;
            }

            tValue = (-a1 + root)*inv;
            if (t0 <= t1) {
                if (t0 <= tValue && tValue <= t1) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            } else {
                if (t1 <= tValue && tValue <= t0) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            }
        } else {
            tValue = -a1/a2;
            if (t0 <= t1) {
                if (t0 <= tValue && tValue <= t1) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            } else {
                if (t1 <= tValue && tValue <= t0) {
                    t[quantity] = tValue;
                    ipoints[quantity].set_t(t[quantity]);
                    ipoints[quantity].set_pos(ray_.at(t[quantity]));
                    Vector3D cp = ipoints[quantity].pos() - m_base;
                    Vector3D ap = m_axis.cross_product(cp);
                    Vector3D nl = ap.cross_product(m_axis);
                    ipoints[quantity].set_normal(nl.normalize());
                    ++quantity;
                }
            }
        }

        if (quantity == 2) {
            if (t[0] > t[1]) {
                float save = t[0];
                t[0] = t[1];
                t[1] = save;
                Diff_Geom gds = ipoints[0];
                ipoints[0] = ipoints[1];
                ipoints[1] = gds;
            }
        }

        return quantity;


    }


public:

        Cylinder () : m_radius (0.f) {
	}

        Cylinder (const Vector3D& center_, const Vector3D& axis_, float radius_, float length_) : m_base (center_), m_axis(axis_.normalize()), m_radius (radius_), m_length(length_/2.f) {
	}

    /**
    * @brief intersect a cylinder .
    * @param ray_ the ray
    * @param p_diff_geom_ the result of the intersection
    * @return true if the ray intersects the cylinder
    * Modifies the ray_.max_t() value, intersect only if the intersection
    * is before ray_.max_t()
    *
	*/
	bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
        Diff_Geom ipoints[2];
        float t[2];
        int numintersection = get_clip_points(ray_, ipoints,  t);
        if (numintersection == 0)
            return false;
        else if (numintersection == 2) {
            int i;
            for (i=0; (i<numintersection) && (t[i] < ray_.ray_epsilon()); i++);
            /*int i=0;
            while ( (i<numintersection) && (t[i] < ray_.ray_epsilon())  )
                i++;*/
            if ( (i < numintersection) && (t[i] < ray_.max_t()) ) {
                *p_diff_geom_ = ipoints[i];
                ray_.set_max_t (t[i]);
                return true;
            } else
                return false;
        } else
            return false;
    }

    /**
     * @brief clip a ray by a cylinder.
     * @param ray_ the ray to clip
     * @param bounds ray sorted bounds of the resulting clipping segment.
     * @return  true if ray was clipped. bounds parameter is filld by this method
     *
     * For simple convex objects, there is two values in  bounds that represent in and out events.
     * An in event is whe the ray enters the geometry, an out is when the ray leaves the geometry.
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
            return false;
        }
    }
};
