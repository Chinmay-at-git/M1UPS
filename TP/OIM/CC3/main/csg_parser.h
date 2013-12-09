#pragma once

#include "raytracing.h"

/**
 * @brief csg_parse : analyse la chaine str et construit l'arbre CSG résultant
 * @param str la chaine à analyser
 * @return l'arbre CSG à travers son noeud racine.
 *
 * En cas d'erreur d'analyse, cette fonction renvoie NULL
 *
 * @todo Cette fonction est à écrire, dans le fichier csg_parser.cpp, pour la question 2 du devoir \ref DevoirCSG.
 *
 */
Geometry *csg_parse(char *str);

