/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:59:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 17:48:37 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_at(t_ray ray, double t)
{
	t_ray	r;

	r.origin = ray.origin;
	r.direction = ray.direction;
	r.origin = vec_add(r.origin, vec_mul_const(r.direction, t));
	return (r);
}

t_color	ray_color(t_ray ray)
{
	t_vec	unit_direction;
	double	t;

	if (hit_sphere(vec(0, 0, -1), 0.5, ray))
		return (vec(1, 0, 0));
	unit_direction = vec_unit(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec_add(vec_mul_const(vec(1.0, 1.0, 1.0), 1.0 - t) \
		, vec_mul_const(vec(0.5, 0.7, 1.0), t)));
}
