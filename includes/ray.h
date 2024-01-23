/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:02:13 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/23 19:42:38 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_hit_record
{
	t_point		p;
	t_vec		normal;
	double		t;
	double		u;
	double		v;
	int			front_face;
	int			hit_anything;
	t_material	material;
}				t_hit_record;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direction;
	double			time;
	t_interval		t;
}				t_ray;

#endif