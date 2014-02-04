#pragma once




#include "geometry.hpp"
#include "intervalset.hpp"
#include <cmath>
#include <cassert>
#include <vector>

// http://www.cse.ohio-state.edu/~parent/classes/681/Lectures/19.RayTracingCSG.pdf

/** @ingroup Raytracer
 * @brief The CSGNode class
 */
class CSGNode : public Geometry {
protected:
    Geometry *m_a;
    Geometry *m_b;
public:

    CSGNode(Geometry *a, Geometry *b):m_a(a), m_b(b){

    }

    virtual ~CSGNode(){}

    /**
     * @brief intersect a geometric object.
     * @param ray_ the ray
     * @param p_diff_geom_ the result of the intersection
     * @return true if the ray intersects the geometry
     * Modifies the ray_.max_t() value, intersect only if the intersection
     * is before ray_.max_t()
     */
    bool intersect (Ray& ray_, Diff_Geom * p_diff_geom_) const {
        IntervalSet bounds;
		bool rv;
        if (clip(ray_, bounds)) {
            unsigned int i;

            std::vector<Bound> &allbounds = bounds.bounds();
            for (i=0; i<allbounds.size(); ++i){
                if (allbounds[i].t >= ray_.ray_epsilon())
                    break;
            }
            if (i<allbounds.size()){
                Diff_Geom *inter_p = allbounds[i].data;
                if (  (inter_p->t() < ray_.max_t()) ){
                    ray_.set_max_t(inter_p->t());
                    *p_diff_geom_ = *inter_p;
                    rv=true;
                } else
                    rv=false;
            } else
                rv=false;
			
        } else {
            rv=false;
        }
		IntervalSet::free_memory();
		return rv;
    }
	
    /**
     * @brief clip a ray by a CSGNode.
     * @param ray_ the ray to clip
     * @param bounds ray-space sorted bounds of the resulting clipped segments.
     * @return  true if ray was clipped. bounds parameter is filled by this method
     *
     * For complex objects, values in bounds represent an ordered set of in - out events.
     * An in event is when the ray enters the geometry, an out is when the ray leaves the geometry.
     * The first event of this array is an in event, followed by an out and so on.
     *
     */
    virtual bool clip(Ray& ray_, IntervalSet &bounds) const =0;
	
};

/** @ingroup Raytracer
 * @brief The CSGIntersection class
 */
class CSGIntersection : public CSGNode {
public:
    CSGIntersection(Geometry *a, Geometry *b):CSGNode(a, b) {

    }

    /**
     * @brief clip a ray by a CSGIntersection.
     * @param ray_ the ray to clip
     * @param bounds ray-space sorted bounds of the resulting clipped segments.
     * @return  true if ray was clipped. bounds parameter is filled by this method
     *
     * bounds contain the intersection, in terms of intervals, of the clip bounds of each son of the node.
     *
     */
    bool clip(Ray& ray_, IntervalSet &bounds) const {
        IntervalSet set_a, set_b;
        if (m_a->clip(ray_, set_a)) {
            if (m_b->clip(ray_, set_b)){
                set_a.intersection_operator(set_b, bounds);
                return (bounds.bounds().size()>0);
            }
        }
        return false;
    }


};

/** @ingroup Raytracer
 * @brief The CSGUnion class
 */
class CSGUnion : public CSGNode {
public:
    CSGUnion(Geometry *a, Geometry *b) : CSGNode(a, b) {

    }

    /**
     * @brief clip a ray by a CSGUnion.
     * @param ray_ the ray to clip
     * @param bounds ray-space sorted bounds of the resulting clipped segments.
     * @return  true if ray was clipped. bounds parameter is filled by this method
     *
     * bounds contain the union, in terms of intervals, of the clip bounds of each son of the node.
     *
     */
    bool clip(Ray& ray_, IntervalSet &bounds) const {
        IntervalSet set_a, set_b;
        m_a->clip(ray_, set_a);
        m_b->clip(ray_, set_b);
        set_a.union_operator(set_b, bounds);
        return (bounds.bounds().size()>0);
     }


};

/** @ingroup Raytracer
 * @brief The CSGDifference class
 */
class CSGDifference : public CSGNode {
public:
    CSGDifference(Geometry *a, Geometry *b) : CSGNode(a, b) {

    }

    /**
     * @brief clip a ray by a CSGDifference.
     * @param ray_ the ray to clip
     * @param bounds ray-space sorted bounds of the resulting clipped segments.
     * @return  true if ray was clipped. bounds parameter is filled by this method
     *
     * bounds contain the difference, in terms of intervals, of the clip bounds of each son of the node.
     *
     */
    bool clip(Ray& ray_, IntervalSet &bounds) const {
        IntervalSet set_a, set_b;
        m_a->clip(ray_, set_a);
        m_b->clip(ray_, set_b);
        set_a.difference_operator(set_b, bounds);
        return (bounds.bounds().size()>0);
    }


};
