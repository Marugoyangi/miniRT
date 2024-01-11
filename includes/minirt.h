/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:24:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 02:49:54 by jeongbpa         ###   ########.fr       */
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
# include "ray.h"
# include "object.h"

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
	double		viewpoint_width;
	double		viewpoint_height;
	double		focal_length;
	t_object	**objects;
}				t_minirt;

# define PI			3.1415926535897932385
# define EPSILON	1e-6	//0.000001

# define SPHERE		1
# define PLANE		2
# define CYLINDER	3
# define CONE		4

//utils
int				ft_close(t_minirt *minirt, char *error, int flag);
void			*ft_malloc(int size);
void			ft_error(char *str);
double			degree_to_rad(double degree);

//vector
t_vec			vec(double x, double y, double z);
t_vec			vec_add(t_vec vec1, t_vec vec2);
t_vec			vec_sub(t_vec vec1, t_vec vec2);
t_vec			vec_mul(t_vec vec1, t_vec vec2);
t_vec			vec_div(t_vec vec1, t_vec vec2);

//cals
double			vec_dot(t_vec vec1, t_vec vec2);
t_vec			vec_cross(t_vec vec1, t_vec vec2);
double			vec_length(t_vec vec);
t_vec			vec_unit(t_vec vec);
double			vec_length_squared(t_vec vec);

//const cals
t_vec			vec_div_const(t_vec vec, double c);
t_vec			vec_add_const(t_vec vec, double c);
t_vec			vec_sub_const(t_vec vec, double c);
t_vec			vec_mul_const(t_vec vec, double c);
t_vec			vec_dot_const(t_vec vec, double c);

//color
unsigned int	set_color(t_color color);
void			print_color(t_minirt *minirt);

//ray
t_ray			ray(t_point origin, t_vec direction);
t_color			ray_color(t_ray *ray, t_object **objects);
t_vec			ray_at(t_ray *ray, double t);
void			set_face_normal(t_ray *ray, t_vec outward_normal, \
								t_hit_record *rec);

//object
t_object		*object(int type, void *element);
void			object_clear(t_object **objects);
void			object_add_back(t_object **objects, t_object *new);
int				hit_object(t_object **objects, t_ray *ray);

//sphere
t_sphere		*sphere(t_point center, double radius);
int				hit_sphere(t_ray *ray, t_sphere *sphere, double t_max, \
							t_hit_record *rec);

#endif
