#pragma once

#include "raytracing.h"

extern "C" {

/** Ajoute à la scene un tetraèdre en position (x,y,z) et de rayon r
  */
void add_tetrahedron(float x, float y, float z, float r);

/** Ajoute à la scene un hexaèdre en position (x,y,z) et de rayon r
  */
void add_hexahedron(float x, float y, float z, float r);

/** Ajoute à la scene un octaèdre en position (x,y,z) et de rayon r
  */
void add_octahedron(float x, float y, float z, float r);

/** Ajoute à la scene un dodecaèdre en position (x,y,z) et de rayon r
  */
void add_dodecahedron(float x, float y, float z, float r);

/** Ajoute à la scene un icosaèdre en position (x,y,z) et de rayon r
  */
void add_icosahedron(float x, float y, float z, float r);


/** Construit une scène représentant les solides de platon et visualisée dans une image de taille (xsize, ysize)
  @param xsize largeur de l'image
  @param ysize hauteur de l'image
  */
void make_platon_scene (int xsize, int ysize);

}

