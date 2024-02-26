/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:24:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/27 03:11:52 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//allowed functions
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../mlx/mlx.h"

//including headers
# include "vector.h"
# include "interval.h"
# include "texture.h"
# include "object.h"
# include "ray.h"
# include "camera.h"

//bonus
# include <pthread.h>
# define THREAD_MAX	8

typedef struct s_minirt	t_minirt;
typedef struct s_thread
{
	int			id;
	t_minirt	*minirt;
}				t_thread;

//mlx data type
typedef struct s_data
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}			t_data;

//general data
typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_data			*img;
	int				img_width;
	int				img_height;
	double			aspect_ratio;
	t_camera		camera;
	t_object		*object;
	t_bvh			*bvh;
	t_aabb			box;
	pthread_t		thread[THREAD_MAX];
	t_thread		thread_data[THREAD_MAX];
	t_object		*light;
}				t_minirt;

# define PI			3.141592653589793238

//object type
# define SPHERE		1
# define QUAD		2
# define CYLINDER	3
# define HYPOBOLOID	4
# define BOX		5

//material type
# define LAMBERTIAN	1
# define METAL		2
# define DIELECTRIC	3
# define DIFFUSE	4
# define PHASE		5

//texture type
# define SOLID		1
# define CHECKER	2
# define IMAGE		3
# define NOISE		4

//key
# define ESC		53
# define ARROW_U	126
# define ARROW_D	125
# define ARROW_L	123
# define ARROW_R	124
# define SPACE		49
# define PLUS		24
# define MINUS		27

//utils
int				ft_close(t_minirt *minirt);
void			*ft_malloc(int size);
void			ft_error(char *str);
double			degree_to_rad(double degree);
void			free_all(t_minirt *minirt);

//random
double			random_double(double min, double max);
double			random_clamp(double x, double min, double max);
t_vec			random_vec(double min, double max);
int				random_int(int min, int max);
t_vec			random_cosine_direction(void);
t_vec			random_to_sphere(double radius, double distance_squared);

//vector
t_vec			vec(double x, double y, double z);
t_vec			vec_add(t_vec vec1, t_vec vec2);
t_vec			vec_sub(t_vec vec1, t_vec vec2);
t_vec			vec_mul(t_vec vec1, t_vec vec2);
t_vec			vec_div(t_vec vec1, t_vec vec2);

//vector cals
double			vec_dot(t_vec vec1, t_vec vec2);
t_vec			vec_cross(t_vec vec1, t_vec vec2);
double			vec_length(t_vec vec);
t_vec			vec_unit(t_vec vec);
double			vec_length_squared(t_vec vec);

//vector const cals
t_vec			vec_div_const(t_vec vec, double c);
t_vec			vec_add_const(t_vec vec, double c);
t_vec			vec_sub_const(t_vec vec, double c);
t_vec			vec_mul_const(t_vec vec, double c);
t_vec			vec_dot_const(t_vec vec, double c);

//vector utils
int				is_near_zero(t_vec vec);

//color
unsigned int	set_color(t_color color, int samples_per_pixel);
void			print_color(void *thread);
void			multi_thread(t_minirt *minirt);
t_color			color(double r, double g, double b);

//ray
t_ray			ray(t_point origin, t_vec direction, double time);
t_color			ray_color(t_bvh *node, t_ray *r, int depth, t_minirt *minirt);
t_vec			ray_at(t_ray *ray, double t);
void			set_face_normal(t_ray *ray, t_vec outward_normal, \
								t_hit_record *rec);

//scatter
int				scatter(t_ray *_ray, t_hit_record *rec, t_ray *scattered, \
				t_scatter_record *srec);
t_vec			reflect(t_vec vec, t_vec normal);
t_vec			refract(t_vec vec, t_vec normal, double ratio, \
				double cos_theta);
double			reflectance(double cosine, double ratio);

//camera
void			set_camera(t_minirt *minirt, int fov, t_vec cam[], \
				double dof);
t_ray			get_ray(t_minirt *minirt, double u, double v);

//camera utils
t_vec			random_in_unit_disk(void);

//object
t_object		*object(int type, void *element);
void			object_add_back(t_minirt *minirt, t_object *new);
int				hit_object(t_object *object, t_ray *ray, t_interval *closest, \
				t_hit_record *rec);

//material
t_material		material(int type, t_vec albedo, double fuzz, double ref_idx);
int				metal_scatter(t_ray *_ray, t_hit_record *rec, \
				t_scatter_record *srec);
int				lambertian_scatter(t_ray *_ray, t_hit_record *rec, \
				t_ray *scattered, t_scatter_record *srec);
int				dielectric_scatter(t_ray *_ray, t_hit_record *rec, \
				t_scatter_record *srec);
int				phase_scatter(t_ray *_ray, t_hit_record *rec, \
				t_ray *scattered, t_scatter_record *srec);

//sphere
t_sphere		*sphere(t_point center, double radius, t_material material, \
				t_vec velocity);
int				hit_sphere(t_ray *ray, t_sphere *sphere, t_interval t, \
							t_hit_record *rec);

//quad
t_quad			*quad(t_point q, t_vec u, t_vec v, t_material material);
int				hit_quad(t_ray *ray, t_quad *quad, t_interval closest, \
							t_hit_record *rec);

//cylinder
t_cylinder		*cylinder(t_vec center, double diameter, double height, \
				t_material material);
int				hit_cylinder(t_ray *ray, t_cylinder *cylinder, \
				t_interval t, t_hit_record *rec);

//hypoboloid
t_hypoboloid	*hypoboloid(t_point center, double diameter, \
				double height, t_material material);
int				hit_hypoboloid(t_ray *ray, t_hypoboloid *hypoboloid, \
				t_interval t, t_hit_record *rec);

//box
t_box			*box(t_point min, t_point max, t_material material);
int				hit_box(t_object *object, t_ray *ray, \
				t_interval *closest, t_hit_record *rec);

//diffuse
t_vec			random_on_hemisphere(t_vec normal);
t_vec			random_in_sphere(void);

//interval
t_interval		interval(double min, double max);
int				interval_is_overlap(t_interval a, t_interval b);
t_interval		interval_padding(t_interval interval, double padding);
double			interval_size(t_interval interval);
t_interval		interval_union(t_interval a, t_interval b);

//aabb
t_aabb			aabb_b(t_aabb a, t_aabb b);
t_aabb			aabb(t_point min, t_point max);
t_interval		axis(t_aabb aabb, int n);
int				aabb_hit(t_aabb aabb, t_ray *ray, t_interval ray_t);
t_aabb			aabb_pad(t_aabb aabb);

//aabb_utils
void			ft_swap(double *a, double *b);
t_aabb			get_box(t_object *object);

//bvh
int				bvh_hit(t_bvh *node, t_ray *ray, t_interval *closest, \
				t_hit_record *rec);
t_bvh			*bvh_node(t_object **objects, int start, int end);

//bvh_compare
int				box_compare_x(t_object *a, t_object *b);
int				box_compare_y(t_object *a, t_object *b);
int				box_compare_z(t_object *a, t_object *b);

//bvh_utils
t_object		**object_vector(t_object **object, int start, int end);
t_object		**object_vector_init(t_object *object, int start, int end);
int				ft_lstsize(t_object *lst);
void			sort_bvh(t_object **objects, int start, int end, \
				int (*comparator)(t_object *, t_object *));

//texture
t_color			checker(t_checker *checker, t_hit_record *rec);

//image
t_color			image_color(t_image *image, t_hit_record *rec);
t_image			*image_init(void *mlx, char *path);

//noise
void			perlin_generate(t_perlin *perlin, double scale);
double			noise(t_perlin *perlin, t_point p);
double			noise_turb(t_perlin *perlin, t_point p);

//transform
void			transform(t_object *obj, t_vec rotation, \
				t_vec translation, t_vec scale);
void			transform_aabb(t_aabb *bbox, t_matrix m);
t_matrix		matrix_inverse(t_matrix m);
t_matrix		matrix_new(void);
t_matrix		matrix_translate(t_vec translation);
t_matrix		matrix_scale(t_vec scale);
t_vec			matrix_apply(t_matrix m, t_vec vec, int w);
t_matrix		matrix_mul(t_matrix a, t_matrix b);
int				hit_transformed(t_object *obj, t_ray *ray, \
				t_interval *closest, t_hit_record *rec);
double			matrix_determinant(t_matrix m);

//volume
int				hit_volume(t_object *object, t_ray *ray, \
				t_interval *closest, t_hit_record *rec);
t_ray			ray_transform(t_ray *ray, t_matrix inverse);

//control
int				key_input(int key, t_minirt *minirt);
void			set_camera_basis(t_minirt *minirt);

//pdf
t_pdf			pdf_cosine(t_ray *ray, t_hit_record *rec, \
				t_ray *scattered, t_vec *direction);
t_pdf			pdf_sphere(t_object *object, t_vec origin, \
				t_ray *tmp_ray, t_vec *direction);
t_vec			onb_local(t_onb uvw, t_vec a);
t_onb			onb(t_vec w);
double			scatter_pdf(t_hit_record *rec, t_ray *scattered);
t_pdf			pdf_quad(t_object *object, t_vec origin, t_ray *ray, \
				t_vec *direction);
void			light_add_back(t_minirt *minirt, t_object *new);
t_pdf			pdf_mixture(t_pdf object, t_pdf light, t_ray *ray, \
				t_hit_record *rec);
t_pdf			pdf_light(t_object *object, t_hit_record *rec, \
				t_ray *tmp_ray, t_vec *direction);
t_pdf			pdf_mix_light(t_object *object, t_hit_record *rec, \
				t_ray *tmp_ray, t_vec *direction);

//init
void			minirt_init(t_minirt *minirt, int width, double aspect_ratio);

//tests
void	minirt_random_spheres(t_minirt *minirt);
void	two_spheres(t_minirt *minirt);
void	earth(t_minirt *minirt);
void	two_perlin_spheres(t_minirt *minirt);
void	quads(t_minirt *minirt);
void	simple_light(t_minirt *minirt);
void	cornell_box(t_minirt *minirt);
void	cornell_box_volume(t_minirt *minirt);
void	final_scene(t_minirt *minirt);
void	bump_test(t_minirt *minirt);
void	cylinder_test(t_minirt *minirt);

#endif
