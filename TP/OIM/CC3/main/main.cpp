#include "raytracing.h"

#include "csg_parser.h"



/* --------------------------------------------------------------- */
/*                      Scene test CSG                             */
/* --------------------------------------------------------------- */
/**
 to initialize the scene with the default one.
 */
void make_test_scene (int xsize, int ysize) {
    //camera
    set_camera (0.f, 4.f, -4.f,
                0.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                90.f, xsize, ysize);
    //objects
    Material * plastic = create_plastic_mat (0.6f, 0.5f, 0.5f,
                                             0.6f, 0.5f, 0.5f,
                                             100.f);
	
    // ground plane
    Geometry * plane = create_plane (0.f, -1.f, 0.f,
                                     0.f, 1.f, 0.f);
    add_object (plane, plastic);

    // Up row
    // base objects
    Geometry *boxLeft = create_box (-2.f, 3.f, 0.f,
                                    1.f, 0.f, 0.f,
                                    0.f, 0.25f, 1.f,
                                    1.f, 1.f, 1.f);
    Geometry *sphereLeft = create_sphere (-2.f, 3.f, 0.f,
                                          0.65f);
    Geometry *boxCenter = create_box (0.f, 3.25f, 0.f,
                                      1.f, 0.f, 0.f,
                                      0.f, 0.25f, 1.f,
                                      1.f, 1.f, 1.f);
    Geometry *sphereCenter = create_sphere (0.f, 3.25f, 0.f,
                                            0.65f);
    Geometry *boxRight = create_box (2.f, 3.f, 0.f,
                                     1.f, 0.f, 0.f,
                                     0.f, 0.25f, 1.f,
                                     1.f, 1.f, 1.f);
    Geometry *sphereRight = create_sphere (2.f, 3.f, 0.f,
                                           0.65f);
    // CSG objects
    Geometry *unionUp = create_csg_union (boxLeft, sphereLeft);
    Geometry *intersectionUp = create_csg_intersection(boxCenter, sphereCenter);
    Geometry *differenceUp = create_csg_difference(boxRight, sphereRight);
	
    add_object (unionUp, plastic);
    add_object (intersectionUp, plastic);
    add_object (differenceUp, plastic);
	
    // Middle row
    // base objects
    Geometry *coneLeft = create_cone(-2.25f, 1.f, -1.25f,
                                     -2.25f, 3.f, -1.25f,
                                     0.5f);
    Geometry *cylinderLeft = create_cylinder(-2.25f, 1.75f, -1.25f,
                                             0.5f, 0.f, 1.f,
                                             0.25f, 1.5f);
    Geometry *coneCenter = create_cone(0.f, 1.5f, -0.75f,
                                       0.f, 3.5f, -0.75f,
                                       0.5f);
    Geometry *cylinderCenter = create_cylinder(0.f, 2.25f, -0.75f,
                                               0.5f, 0.f, 1.f,
                                               0.25f, 1.5f);
    Geometry *coneRight = create_cone(2.25f, 1.f, -1.25f,
                                      2.25f, 3.f, -1.25f,
                                      0.5f);
    Geometry *cylinderRight = create_cylinder(2.25f, 1.75f, -1.25f,
                                              0.5f, 0.f, 1.f,
                                              0.25f, 1.5f);
    // CSG objects
    Geometry * unionDown = create_csg_union (coneLeft, cylinderLeft);
    Geometry * intersectionDown = create_csg_intersection(coneCenter, cylinderCenter);
    Geometry * differenceDown = create_csg_difference(coneRight, cylinderRight);
	
    add_object (unionDown, plastic);
    add_object (intersectionDown, plastic);
    add_object (differenceDown, plastic);
	
    // front object
    char complex_tree[] = "(- (* (bo 0. 2.5 -3.25 1. 0. 0. 0. 0. 1. 1.0 1.0 1.0) (sp 0. 2.5 -3.25 0.65) ) (+ (cy 0. 2.5 -3.25 1.0 0.0 0.0 0.3 1.75) (+ (cy 0. 2.5 -3.25 0.0 1.0 0.0 0.3 1.75) (cy 0. 2.5 -3.25 0.0 0.0 1.0 0.3 1.75) ) ) )";
    Geometry *tree = csg_parse(complex_tree);
    if (tree)
        add_object (tree, plastic);

    //lights
	// Front light -- white
    add_light (0.f, 5.f, -1.5f, 1.5f, 1.5f, 1.5f);
	// Back light -- blue
    add_light (4.f, 2.f, 10.f, 0.1f, 0.1f, 0.9f);
	// Left light -- red
    add_light (-4.f, 5.f, -2.f, 0.9f, 0.1f, 0.1f);
}


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
    int i, isVisible;
    Light* light_;

    l = init_color (0.f, 0.f, 0.f);
    
    for (i=0; i<nb_lights(); i++){
      light_ = get_light(i);
      isVisible =  test_visibility ( isect_, light_);
      if (isVisible!=0){
    l = l+direct_lighting (ray_, isect_, light_);
      }
    }

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

  Color l = init_color (0.075f, 0.075f, 0.075f);
  Isect isect_;
  
  int isInter = intersect_scene (&ray_, &isect_ );
  
  if (isInter!=0){
    l = compute_direct_lighting (ray_, isect_);
  }
  
  if (ray_depth(ray_)>10 || ray_importance(ray_)<0.01f)
    return (l);
  
  //reflection
  if(isect_has_reflection(isect_)){
    Ray refl_ray;
    Color refl_col = reflect(ray_, isect_, &refl_ray);
    l = l+refl_col*(trace_ray(refl_ray));
  }
  //refraction
  if(isect_has_refraction(isect_)){
   Ray rafr_ray;
   Color rafr_col = refract(ray_, isect_, &rafr_ray);
   if(color_is_black(rafr_col)==0)
    l = l+rafr_col*(trace_ray(rafr_ray));
  }

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

  int i,j, img_height, img_width;
  Ray ray;
  Color color;

  get_image_resolution(&img_width, &img_height);
  
  for(i=0; i<img_width; i++){
   for(j=0; j<img_height; j++){
     ray = camera_ray(i,j);
     color = trace_ray (ray);
     set_pixel_color (i, j, color);
   }
  }
}

/***************************************************/
/*******
 Fonctions données
 ******/
/**
 * \callgraph
 */
int main () {

  // At the end of practical work, the following will give you the default scene
  // make_default_scene(800, 600);
  // At the end of the homework, the following will give you the validation scene
  make_test_scene(800, 800);
	
	compute_image();
	std::cerr << "Sauvegarde image ... " << std::endl;
  save_image ("monimage.exr");

	return 0;
}
