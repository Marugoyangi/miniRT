/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:59:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 19:20:12 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	ray_at(t_ray ray, double t)
{
	t_vec	ret;

	ret = vec_add(ray.origin, vec_mul_const(ray.direction, t));
	return (ret);
}

t_color	ray_color(t_ray ray)
{
	t_vec	unit_direction;
	double	t;

	t = hit_sphere(vec(0, 0, -1), 0.5, ray);
	if (t > 0.0)
	{
		unit_direction = vec_unit(vec_sub(ray_at(ray, t), vec(0, 0, -1)));
		unit_direction = vec_mul_const(vec(unit_direction.x + 1, \
		unit_direction.y + 1, unit_direction.z + 1), 0.5);
		return (unit_direction);
	}
	unit_direction = vec_unit(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec_add(vec_mul_const(vec(1.0, 1.0, 1.0), 1.0 - t) \
		, vec_mul_const(vec(0.5, 0.7, 1.0), t)));
}
