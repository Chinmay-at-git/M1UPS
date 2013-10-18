#include "solidesplaton.h"

#include "../coreraytracer/scene.hpp"
#include "../coreraytracer/image.hpp"

#include "../coreraytracer/plane.hpp"
#include "../coreraytracer/sphere.hpp"
#include "../coreraytracer/cylinder.hpp"

#include "../coreraytracer/matte.hpp"
#include "../coreraytracer/plastic.hpp"
#include "../coreraytracer/metal.hpp"
#include "../coreraytracer/glass.hpp"

#define EPSILON 1e-6

/* Nombre d'or */
#define PHI ((1.f + sqrtf(5.f))/2.f)

/* Taille des géométries par rapport au rayon des solides */
#define SPHERERATIO 7.5f
#define CYLINDERRATIO (2.f*SPHERERATIO*PHI)

/* Matériaux des sommets et aretes */
Material *vertexMat;
Material *edgeMat;

/* Fonction de génération de la géométrie et de peuplement de la scène, indépendante du solide construit.
    Cette fonction ajoute une sphere en chaque point du tableau tabPoints et un cylindre entre chaque points distants de edgeSize
*/
void populateScene(Vector3D center, float sphereRadius, float cylinderRadius,
                   Vector3D *tabPoints, int nbVertex, float edgeSize){
}


/* Construction tetraèdre :
    http://www.mathcurve.com/polyedres/tetraedre/tetraedre.shtml
*/
void add_tetrahedron(float x, float y, float z, float r){
}

/* Construction hexaèdre:
  http://www.mathcurve.com/polyedres/cube/cube.shtml
*/
void add_hexahedron(float x, float y, float z, float r){
}


/* Construction octaèdre:
  http://www.mathcurve.com/polyedres/octaedre/octaedre.shtml
*/
void add_octahedron(float x, float y, float z, float r){
}

/* Construction dodecaèdre:
  http://www.mathcurve.com/polyedres/octaedre/octaedre.shtml
*/
void add_dodecahedron(float x, float y, float z, float r){
}

/* Construction icosaèdre :
  http://www.mathcurve.com/polyedres/icosaedre/icosaedre.shtml
*/
void add_icosahedron(float x, float y, float z, float r){
}


/* Constuction de la scène de démonstration des solides de Platon
  */
void make_platon_scene (int xsize, int ysize) {
	//camera
        set_camera (0.f, 0.f, -10.f,
				0.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
                               62.f, xsize, ysize);
        //lights
        // front light
        add_light (0.f, 1.f, -4.f, 1.5f, 1.5f, 1.5f);
        // side light
        add_light (-3.f, 3.f, -4.f, 0.5f, 0.5f, 0.5f);
        // back light
        add_light (3.f, 0.f, 5.f, 1.5f, 1.5f, 1.5f);

	//objects

        vertexMat = create_plastic_mat (0.6f, 0.01f, 0.025f,
                                        0.25f, 0.25f, 0.25f,
                                        300.f);

        /*vertexMat = create_metal_mat (0.8f, 0.2f, 0.2f,  1.f, 1.f, 1.f);*/
        edgeMat = create_plastic_mat (0.01f, 0.6f, 0.0f,
                                      0.01f, 0.6f, 0.0f,
                                      100.f);
        /* pour un reflet sur le fond */
        Geometry * sphere = create_sphere (0.f, 0.f, 30.f, 24.f);
        Material * transp = create_metal_mat (0.01f, 0.01f, 0.01f,
                                              5.f, 5.f, 5.f );

        add_object(sphere, transp);

#if 0
        add_dodecahedron(0.f, 0.f, 0.f, 3.f);
#else

        float radius=3.f;
        float solidRadius = 1.5f;
        float angle = 2.f*M_PI/10.f;
        float x, y, z;

        x = radius*cos(angle);
        y = radius*sin(angle);
        z = 0;

        add_tetrahedron(x, y, z, solidRadius);

        angle += 2.f*M_PI/5.f;
        x = radius*cos(angle);
        y = radius*sin(angle);
        z = 0;
        add_hexahedron(x, y, z, solidRadius);

        angle += 2.f*M_PI/5.f;
        x = radius*cos(angle);
        y = radius*sin(angle);
        z = 0;
        add_octahedron(x, y, z, solidRadius);

        angle += 2.f*M_PI/5.f;
        x = radius*cos(angle);
        y = radius*sin(angle);
        z = 0;
        add_dodecahedron(x, y, z, solidRadius);

        angle += 2.f*M_PI/5.f;
        x = radius*cos(angle);
        y = radius*sin(angle);
        z = 0;
        add_icosahedron(x, y, z, solidRadius);
#endif
}

/*
  Voir aussi:
http://www.math.ens.fr/culturemath/video/Dupas-polyedres/patrons/Construction.html
*/
