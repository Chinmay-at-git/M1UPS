//#include "raytracing.h"
#include "solidesplaton.h"

/*******
 Fonction à écrire par les etudiants
 ******/
Color compute_direct_lighting (Ray ray_, Isect isect_) {
/**
 * \todo : compute here direct lighting
 *
 * Le rôle de la fonction compute_direct_lighting() est de calculer la somme, pour chaque source de lumière de la scène, de l'éclairage
 * élémentaire dû à cette source. Cette somme est calculée en ajoutant à une couleur noire (triplet \b RGB [0, 0, 0], élément neutre de 
 * l'addition des couleurs), la valeur de l'éclairage direct lié à chaque source de la scène. La fonction compute_direct_lighting()
 * utilise pour cela les fonctions des modules \ref SceneAPI (pour accéder à l'ensemble des sources lumineuses de la scène), 
 * \ref RayAPI (pour calculer la visibilité entre un point et une source de lumière) et \ref LightAPI (pour calculer l'éclairage direct).
 */
    Color l;

    l = init_color (0.f, 0.f, 0.f);

 
    return l;

}

/***************************************************/
/*******
 Fonction à écrire par les etudiants
 ******/
Color trace_ray (Ray ray_) {
/**
 * \todo : recursive raytracing
 *
 * La fonction trace_ray() renvoie une couleur obtenue par la somme de l'éclairage direct (couleur calculée par la fonction 
 * compute_direct_lighting()) et des couleurs provenant des reflets et transparences éventuels aux points d'intersection. 
 * Dans la première partie du TP, seul l'éclairage direct sera calculé. Dans la seconde partie, les reflets et transparences seront rajoutés.
 *
 * Pour la première étape, la fonction trace_ray() ne calculant que les rayons primaires, l'intersection 
 * entre le rayon et la scène doit être calculée (fonction intersect_scene() du module \ref RayAPI).
 * S'il n'y a pas d'intersection, une couleur blanche (triplet RGB [1, 1, 1], élément neutre de la multiplication des couleurs) 
 * devra être retournée.
 * S'il y a une intersection, la couleur retournée sera la couleur résultante de l'éclairage direct du point d'intersection par les 
 * sources lumineuses de la scène et calculée par la fonction compute_direct_lighting() à écrire dans la suite.
 *
 * Pour la deuxième étape, à partir des fonctions définies dans le module \ref RayAPI et permettant d'accéder aux informations de 
 * profondeur et d'importance sur le rayon, définir un cas d'arêt dela récursivité et renvoyer si ce cas est vérifié la couleur 
 * résultante de l'éclairage direct. Si la récursivité n'est pas terminée, en utilisant les fonctions définies dans le module \ref LightAPI,
 * calculer la couleur réfléchie. Pour cela, il  faut tester si le matériau est réflechissant et, si c'est le cas, calculer le rayon 
 * réfléchi et le coefficient de réflexion (une couleur). La couleur calculée en lançant le rayon réfléchi devra alors être multipliée par ce coefficient avant d'être ajoutée
 * à la couleur renvoyée par trace_ray().
 *
 * Pour la troisème étape et de façon très similaire à la réflexion, utiliser les fonctions définies dans le module \ref LightAPI pour calculer la couleur réfractée.
 * Pour cela, il  faut tester si le matériau est transparent et, si c'est le cas, calculer le rayon réfracté et le coefficient de 
 * transparence (une couleur). La couleur calculée en lançant le rayon réfracté devra alors être multipliée par ce coefficient avant
 * d'être ajoutée à la couleur renvoyée par trace_ray().
 *
*/

	Color l = init_color (0.f, 0.f, 0.f);

	return l;
}

/***************************************************/
/*******
 Fonction à écrire par les etudiants
 ******/
void compute_image () {
/**
 * \todo : main rendering loop
 *
 * Le calcul d'une image de synthèse consiste à calculer une couleur pour tous les pixels d'une image en fonction 
 * d'une modélisation d'un capteur virtuel.
 * Ce capteur est ici représenté par une Camera qui permet, à partir des coordonnées (x,y) d'un pixel d'une image, 
 * de créer le rayon passant par ce pixel. La manière dont est créé ce rayon dépend de la Camera. 
 * La scène étant crée avec une caméra par défaut de type \b pinhole, la fonction camera_ray() 
 * devra être utilisée afin de créer le rayon primaire. 
 * Ce rayon est ensuite tracé dans la scène (par la fonction trace_ray())
 * et la couleur calculée à l'aide de ce rayon doit être stockée sur le pixel (x,y).
*/

}

/***************************************************/
/*******
 Fonctions données
 ******/
/**
 * \callgraph
 */
int main () {

        //make_platon_scene (800, 600);
        make_default_scene(800, 600);

	compute_image();
	
	save_image ("monimage.exr");

	return 0;
}
