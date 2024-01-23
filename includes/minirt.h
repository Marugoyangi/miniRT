/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:24:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 03:31:52 by jeongbpa         ###   ########.fr       */
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
	void		*mlx;
	void		*win;
	t_data		*img;
	int			img_width;
	int			img_height;
	t_camera	camera;
	t_object	*object;
	t_bvh		*bvh;
	t_aabb		box;
	int			thread_num;
}				t_minirt;

# define PI			3.1415926535897932385

//object type
# define SPHERE		1
# define PLANE		2
# define CYLINDER	3
# define CONE		4

//material type
# define LAMBERTIAN	1
# define METAL		2
# define DIELECTRIC	3

//texture type
# define SOLID		1
# define CHECKER	2
# define IMAGE		3

//utils
int				ft_close(t_minirt *minirt, char *error, int flag);
void			*ft_malloc(int size);
void			ft_error(char *str);
double			degree_to_rad(double degree);

//random
double			random_double(double min, double max);
double			random_clamp(double x, double min, double max);
t_vec			random_vec(double min, double max);

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
double			q_rsqrt(double number);

//color
unsigned int	set_color(t_color color, int samples_per_pixel);
void			print_color(t_minirt *minirt);
void			multi_thread(t_minirt *minirt);
t_color			color(double r, double g, double b);

//ray
t_ray			ray(t_point origin, t_vec direction, double time);
t_color			ray_color(t_bvh *node, t_ray *r, int depth);
t_vec			ray_at(t_ray *ray, double t);
void			set_face_normal(t_ray *ray, t_vec outward_normal, \
								t_hit_record *rec);

//scatter
int				scatter(t_ray *_ray, t_hit_record *rec, t_ray *scattered);
t_vec			reflect(t_vec vec, t_vec normal);
t_vec			refract(t_vec vec, t_vec normal, double ratio, double cos_theta);
double			reflectance(double cosine, double ratio);

//camera
void			set_camera(t_minirt *minirt);
t_ray			get_ray(t_minirt *minirt, double u, double v);

//camera utils
t_vec			random_in_unit_disk(void);

//object
t_object		*object(int type, void *element);
void			object_clear(t_object **objects);
void			object_add_back(t_minirt *minirt, t_object *new);
int				hit_object(t_object *object, t_ray *ray, t_interval *closest, \
				t_hit_record *rec);

//object_utisl
t_object		*object_copy(t_object **object, int idx);

//material
t_material		material(int type, t_vec albedo, double fuzz, double ref_idx);
int				metal_scatter(t_ray *_ray, t_hit_record *rec, \
				t_color *attenuation, t_ray *scattered);
int				lambertian_scatter(t_ray *_ray, t_hit_record *rec, t_color *attenuation, \
				t_ray *scattered);
int				dielectric_scatter(t_ray *_ray, t_hit_record *rec, \
				t_color *attenuation, t_ray *scattered);

//sphere
t_sphere		*sphere(t_point center, double radius, t_material material, \
				t_vec velocity);
int				hit_sphere(t_ray *ray, t_sphere *sphere, double t, \
							t_hit_record *rec);

//diffuse
t_vec			random_on_hemisphere(t_vec normal);
t_vec			random_in_sphere(void);

//interval
t_interval	interval(double min, double max);
int	interval_is_overlap(t_interval a, t_interval b);
t_interval	interval_padding(t_interval interval, double padding);
double	interval_size(t_interval interval);
t_interval	interval_union(t_interval a, t_interval b);

//aabb
t_aabb	aabb_b(t_aabb a, t_aabb b);
t_aabb	aabb(t_point min, t_point max);
t_interval	axis(t_aabb aabb, int n);
int	aabb_hit(t_aabb aabb, t_ray *ray, t_interval ray_t);

//aabb_utils
void	ft_swap(double *a, double *b);
t_aabb	get_box(t_object *object);

//bvh
int		bvh_hit(t_bvh *node, t_ray *ray, t_interval *closest, t_hit_record *rec);
t_bvh	*bvh_node(t_object **objects, int start, int end);

//bvh_compare
int	box_compare_x(t_object *a, t_object *b);
int	box_compare_y(t_object *a, t_object *b);
int	box_compare_z(t_object *a, t_object *b);

//bvh_utils
t_object	**object_vector(t_object **object, int start, int end);
t_object	**object_vector_init(t_object *object, int start, int end);
int			ft_lstsize(t_object *lst);
void		sort_bvh(t_object **objects, int start, int end, \
				int (*comparator)(t_object *, t_object *));
void			bvh_search(t_object *root, t_ray *r, t_interval *closes, \
				t_hit_record *rec);

//texture
t_color	checker(t_checker *checker, t_hit_record *rec);


//image
t_color	image_color(t_texture *texture, t_image *image, t_hit_record *rec);
t_image	*image_init(void *mlx, char *path);
t_color	image_normal(t_minirt *minirt, t_hit_record *rec);
#endif
