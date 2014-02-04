#pragma once

#include "intervaloperators.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

/** @defgroup IntervalAPI Interval operators API
 *  Application Programming Interface for the interval management for CSG objects
 *  @{
 *
 */

// Open interval set
// adapted from http://www.geometrictools.com/SampleMathematics/BooleanIntervalRectangle/IntervalSet.h

class Diff_Geom_MemoryLiberator{
public:
	void operator()(Diff_Geom* p) {
		delete p;
	}
};

/**
 * @brief The IntervalSet class.
 *
 *   Un ensemble d'intervalle est un tableau de bornes contenant n éléments permettant de définir n/2 intervalles
 *   Les fonctions union_of_intervals(), intersection_of_intervals() et difference_of_intervals() doivent être écrites
 *   par les étudiants. Voir \ref DevoirCSG pour les précisions.
 */
class IntervalSet {
    std::vector<Bound> m_bounds;
	static std::vector<Diff_Geom*> m_garbage;
	
	
public:
    IntervalSet(){}

    void add(Diff_Geom* in, Diff_Geom* out){
        Bound bound_in;
        bound_in.t = in->t();
        bound_in.data=in;
        Bound bound_out;
        bound_out.t = out->t();
        bound_out.data=out;
        m_bounds.push_back(bound_in);
        m_bounds.push_back(bound_out);
		m_garbage.push_back(in);
		m_garbage.push_back(out);
    }

    std::vector<Bound> &bounds(){
        return m_bounds;
    }

    void union_operator(const IntervalSet &other, IntervalSet &res){
        int size_res=0;
        res.m_bounds.resize(m_bounds.size() + other.m_bounds.size());
        union_of_intervals(const_cast<Bound *>(&(m_bounds[0])), m_bounds.size(), const_cast<Bound *>(&(other.m_bounds[0])), other.m_bounds.size(), &(res.m_bounds[0]), &size_res);
        res.m_bounds.resize(size_res);
    }

    void intersection_operator(const IntervalSet &other, IntervalSet &res){
        int size_res=0;
        res.m_bounds.resize(std::max(m_bounds.size(), other.m_bounds.size()));
        intersection_of_intervals(const_cast<Bound *>(&(m_bounds[0])), m_bounds.size(), const_cast<Bound *>(&(other.m_bounds[0])), other.m_bounds.size(), &(res.m_bounds[0]), &size_res);
        res.m_bounds.resize(size_res);
    }

    void difference_operator(const IntervalSet &other, IntervalSet &res){
        int size_res=0;
        res.m_bounds.resize(m_bounds.size() + other.m_bounds.size());
        difference_of_intervals(const_cast<Bound *>(&(m_bounds[0])), m_bounds.size(), const_cast<Bound *>(&(other.m_bounds[0])), other.m_bounds.size(), &(res.m_bounds[0]), &size_res);
        res.m_bounds.resize(size_res);
    }

	static void free_memory() {
		if (m_garbage.size() ) {
			for_each (m_garbage.begin(), m_garbage.end(), Diff_Geom_MemoryLiberator());
			m_garbage.clear();
		}
	}
	
};

/** @} */ // end of IntervalAPI group

