#pragma once

#include "diff_geom.hpp"


    /** @ingroup IntervalAPI
     * Une borne est défini par sa coordonnée t et une donnée opaque data.
     *
     * Un évenement est représenté par une borne.
     * Un intervalle est défini par deux évènements a et b de telle sorte que a.t < b.t
     */
    struct Bound {
        float t;
        Diff_Geom *data;
    };


   /**  @ingroup IntervalAPI
    * @brief Calcule l'union des deux ensembles d'évènements.
    * @param a Tableau des évènements ordonnés de a
    * @param size_a Taille du tableau a
    * @param b Tableau des évènements ordonnés de b
    * @param size_b Taille du tableau b
    * @param res Tableau des évènements ordonnés résultant
    * @param size_res Taille du tableau d'évènements résultant
    *
    * Calcule dans res l'union des deux ensemble d'évènements a et b contenant respectivement size_a et size_b évènements.
   */
    extern void union_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res);

    /**  @ingroup IntervalAPI
    * @brief Calcule l'intersection des deux ensembles d'évènements.
    * @param a Tableau des évènements ordonnés de a
    * @param size_a Taille du tableau a
    * @param b Tableau des évènements ordonnés de b
    * @param size_b Taille du tableau b
    * @param res Tableau des évènements ordonnés résultant
    * @param size_res Taille du tableau d'évènements résultant
    *
    * Calcule dans res l'intersection des deux ensemble d'évènements a et b contenant respectivement size_a et size_b évènements.
    */
    extern void intersection_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res);

    /**  @ingroup IntervalAPI
    * @brief Calcule la différence des deux ensembles d'évènements.
    * @param a Tableau des évènements ordonnés de a
    * @param size_a Taille du tableau a
    * @param b Tableau des évènements ordonnés de b
    * @param size_b Taille du tableau b
    * @param res Tableau des évènements ordonnés résultant
    * @param size_res Taille du tableau d'évènements résultant
    *
    * Calcule dans res la différence des deux ensemble d'évènements a et b contenant respectivement size_a et size_b évènements.
    */
    extern void difference_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res);


