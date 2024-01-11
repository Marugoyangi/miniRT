/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:24:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 18:35:49 by jeongbpa         ###   ########.fr       */
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
}				t_minirt;

//functions
int				ft_close(t_minirt *minirt, char *error, int flag);
void			print_color(t_minirt *minirt);

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

//const cals
t_vec			vec_div_const(t_vec vec, double c);
t_vec			vec_add_const(t_vec vec, double c);
t_vec			vec_sub_const(t_vec vec, double c);
t_vec			vec_mul_const(t_vec vec, double c);
t_vec			vec_dot_const(t_vec vec, double c);

//color
unsigned int	set_color(t_color color);

//ray
t_color			ray_color(t_ray ray);
int				hit_sphere(t_point center, double r, t_ray ray);

#endif
