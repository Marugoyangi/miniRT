/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:02:13 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 01:16:24 by jeongbpa         ###   ########.fr       */
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
	int			front_face;
	int			hit_anything;
}				t_hit_record;

typedef struct s_ray
{
	t_point			origin;
	t_vec			direction;
	t_hit_record	record;
	double			t_min;
	double			t_max;
}				t_ray;

#endif