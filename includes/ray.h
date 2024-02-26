/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:02:13 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/21 23:13:22 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_hit_record
{
	int			front_face;
	int			hit_anything;
	int			img_width;
	int			img_height;
	t_point		p;
	t_vec		normal;
	double		t;
	double		u;
	double		v;
	t_material	material;
	t_object	*object;
}				t_hit_record;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direction;
	double			time;
	t_interval		t;
}				t_ray;

typedef struct s_scatter_record
{
	t_color	attenuation;
	int		is_specular;
	t_ray	specular_ray;
	t_pdf	pdf[2];
}			t_scatter_record;

#endif