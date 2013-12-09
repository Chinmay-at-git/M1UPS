#include "raytracing.h"

#include "scene.hpp"
#include "image.hpp"

#include "plane.hpp"
#include "sphere.hpp"
#include "cylinder.hpp"
#include "cone.hpp"
#include "box.hpp"
#include "csg.hpp"

#include "matte.hpp"
#include "plastic.hpp"
#include "metal.hpp"
#include "glass.hpp"


//====================
//global variables

/// The scene
Scene g_scene;

/// The camera
Camera g_camera;

/// The resulting image
Image * g_p_img = NULL;


//====================
//scene description


void set_camera (float pos_x_, float pos_y_, float pos_z_,
				 float aim_x_, float aim_y_, float aim_z_,
				 float up_x_, float up_y_, float up_z_,
				 float fov_, int x_res_, int y_res_) {
	g_camera = Camera (Vector3D (pos_x_, pos_y_, pos_z_),
					   Vector3D (aim_x_, aim_y_, aim_z_),
					   Vector3D (up_x_, up_y_, up_z_),
					   fov_, x_res_, y_res_);

	g_scene.set_camera (&g_camera);

	delete g_p_img;

	g_p_img = new Image (x_res_, y_res_);
}


void add_light (float pos_x_, float pos_y_, float pos_z_,
				float r_, float g_, float b_) {
	g_scene.add_light (new Light (Vector3D (pos_x_, pos_y_, pos_z_),
								  Color (r_, g_, b_)));
}

Geometry * create_plane (float pos_x_, float pos_y_, float pos_z_,
						 float normal_x_, float normal_y_, float normal_z_) {
	return new Plane (Vector3D (pos_x_, pos_y_, pos_z_),
					  Vector3D (normal_x_, normal_y_, normal_z_));
}


Geometry * create_sphere (float pos_x_, float pos_y_, float pos_z_,
						  float radius_) {
	return new Sphere (Vector3D (pos_x_, pos_y_, pos_z_), radius_);
}


Geometry * create_cylinder (float pos_x_, float pos_y_, float pos_z_,
                            float axis_x_, float axis_y_, float axis_z_,
                            float radius_, float length_) {
        return new Cylinder (Vector3D (pos_x_, pos_y_, pos_z_), Vector3D (axis_x_, axis_y_, axis_z_), radius_, length_);
}


Geometry * create_cone (float pos_x_, float pos_y_, float pos_z_,
                        float vertex_x_, float vertex_y_, float vertex_z_,
                        float radius_){
    return new Cone (Vector3D(pos_x_, pos_y_, pos_z_), Vector3D(vertex_x_, vertex_y_, vertex_z_), radius_);
}


Geometry * create_box (float pos_x_, float pos_y_, float pos_z_,
                       float x_base_x_, float x_base_y_, float x_base_z_,
                       float y_base_x_, float y_base_y_, float y_base_z_,
                       float extent_x_, float extent_y_, float extent_z_
                       ){
    return new Box3D (Vector3D(pos_x_, pos_y_, pos_z_),
                    Vector3D(x_base_x_, x_base_y_, x_base_z_),
                    Vector3D(y_base_x_, y_base_y_, y_base_z_),
                    Vector3D(extent_x_, extent_y_, extent_z_));
}


Material * create_matte_mat (float kd_r_, float kd_g_, float kd_b_) {
	return new Matte (Color (kd_r_, kd_g_, kd_b_));
}


Material * create_plastic_mat (float kd_r_, float kd_g_, float kd_b_,
							   float ks_r_, float ks_g_, float ks_b_,
							   float shininess_) {
	return new Plastic (Color (kd_r_, kd_g_, kd_b_),
						Color (ks_r_, ks_g_, ks_b_),
						shininess_);
}


Material * create_metal_mat (float kd_r_, float kd_g_, float kd_b_,
							 float kr_r_, float kr_g_, float kr_b_) {
	return new Metal (Color (kd_r_, kd_g_, kd_b_),
					  Color (kr_r_, kr_g_, kr_b_));
}


Material * create_glass_mat (float ks_r_, float ks_g_, float ks_b_,
							 float kt_r_, float kt_g_, float kt_b_,
							 float ior_) {
	return new Glass (Color (ks_r_, ks_g_, ks_b_),
					  Color (kt_r_, kt_g_, kt_b_),
					  ior_);
}


void add_object (Geometry * geom_, Material * mat_) {
	g_scene.add_primitive (new Primitive (geom_, mat_));
}

/**
   to initialize the scene with the default one.
*/
void make_default_scene (int xsize, int ysize) {
	//camera
	set_camera (0.f, 2.f, -6.f,
				0.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
                               90.f, xsize, ysize);

	//objects
	Material * matte = create_matte_mat (1.f, 0.2f, 0.2f);
	Material * plastic = create_plastic_mat (0.6f, 0.5f, 0.5f,
                                                  0.6f, 0.5f, 0.5f,
                                                  100.f);
	Material * metal = create_metal_mat (0.2f, 0.2f, 0.2f,
                                             1.f, 1.f, 1.f);
	Material * glass = create_glass_mat (1.f, 1.f, 1.f,
                                             1.f, 1.f, 1.f,
                                             1.25f);
        Material * transp = create_glass_mat (1.f, 1.f, 1.f,
                                              1.f, 1.f, 1.f,
                                              1.f);

        Geometry * sphere1 = create_sphere (-1.f, 0.f, -1.f, 1.f);
        Geometry * sphere2 = create_sphere (-1.f, 0.f, 1.f, 1.f);
        Geometry * sphere3 = create_sphere (1.f, 0.f, -1.f, 1.f);
        Geometry * sphere4 = create_sphere (1.f, 0.f, 1.f, 1.f);

        Geometry * sphere_top = create_sphere (0.f, 1.414f, 0.f, 1.f);

        Geometry * plane = create_plane (0.f, -1.f, 0.f,
                                         0.f, 1.f, 0.f);
	
        Geometry * cylinder1 = create_cylinder(0.f, 2.f, -0.25f,
                                               1.f, -1.f, -1.f,
                                               .25f, 3.f );

        Geometry * cylinder2 = create_cylinder(0.f, 2.f, -0.25f,
                                               1.f, 1.f, 1.f,
                                               .25f, 3.f );

        add_object (sphere1, metal);
	add_object (sphere2, matte);
        add_object (sphere3, glass);
        add_object (sphere4, plastic);

        add_object (sphere_top, transp);

        add_object (plane, plastic);

        add_object (cylinder1, plastic);
        add_object (cylinder2, plastic);


	//lights
	add_light (4.f, 2.f, 10.f,
                           0.1f, 0.1f, 0.9f);
        add_light (0.f, 5.f, -1.5f,
                           1.5f, 1.5f, 1.5f);
        add_light (-4.f, 5.f, -2.f,
                           0.9f, 0.1f, 0.1f);
}

//====================
//access to scene elements


int nb_lights () {
	return g_scene.p_lights().size();
}


Light * get_light (int i_) {
	return g_scene.p_lights()[i_];
}


void get_image_resolution (int * p_x_res_, int * p_y_res_) {
	*p_x_res_ = g_camera.x_res();
	*p_y_res_ = g_camera.y_res();
}

//====================
//rays-related operations


Ray camera_ray (int x_, int y_) {
	return g_camera.ray_for_pixel (x_, y_);
}


int intersect_scene (Ray * p_ray_, Isect * p_isect_) {
	return g_scene.intersect (*p_ray_, p_isect_) ? 1 : 0;
}


int test_visibility (Isect isect_, Light * light_) {
	return g_scene.test_visibility (isect_.dg().pos(), light_) ? 1 : 0;
}

int ray_depth (Ray ray_) {
	return ray_.depth();
}

float ray_importance (Ray ray_) {
	return ray_.importance().avg();
}

//====================
//color-related

/**
   return a black color
*/
Color black() {
	return Color (0.f);
}

Color init_color(float r_, float g_, float b_) {
	return Color (r_, g_, b_);
}

Color multiply_color_color (Color c1_, Color c2_) {
	return c1_ * c2_;
}

Color add_color_color (Color c1_, Color c2_) {
	return c1_ + c2_;
}

int color_is_black (Color color_) {
	return color_.is_zero() ? 1 : 0;
}


//====================
//light-transport

int isect_has_reflection (Isect isect_) {
	return isect_.bsdf().has_reflection();
}

int isect_has_refraction (Isect isect_) {
	return isect_.bsdf().has_refraction();
}

Color reflect (Ray ray_, Isect isect_, Ray * p_ray_) {
	Vector3D refl_dir;
	Color fs = isect_.bsdf().reflect_dir (-ray_.dir(), &refl_dir);

	*p_ray_ = Ray (ray_, fs, isect_.dg().pos(), refl_dir);

	return fs * fabsf (isect_.dg().normal().dot (refl_dir)); //cos(theta) here for easier use
}

Color refract (Ray ray_, Isect isect_, Ray * p_ray_) {
	Vector3D refr_dir;
	Color fs = isect_.bsdf().refract_dir (-ray_.dir(), &refr_dir);

	*p_ray_ = Ray (ray_, fs, isect_.dg().pos(), refr_dir);

	return fs * fabsf (isect_.dg().normal().dot (refr_dir)); //cos(theta) here for easier use
}

Color direct_lighting (Ray ray_, Isect isect_, Light * light_) {
	Vector3D dir_to_light = (light_->pos() - isect_.dg().pos()).normalize();
	return isect_.bsdf().evaluate (-ray_.dir(), dir_to_light) * light_->le() *
		fabsf (isect_.dg().normal().dot (dir_to_light));
}


//====================
//Image management

void set_pixel_color (int x_, int y_, Color color_) {
	g_p_img->pixel (x_, y_) = color_;
}

void save_image (const char * file_name_) {
	g_p_img->write_to_exr_file (std::string (file_name_));
}

//------------------
// CSG

Geometry *create_csg_intersection(Geometry *a, Geometry *b){
    return new CSGIntersection(a,b);
}

Geometry *create_csg_union(Geometry *a, Geometry *b){
    return new CSGUnion(a,b);
}

Geometry *create_csg_difference(Geometry *a, Geometry *b){
    return new CSGDifference(a,b);
}

