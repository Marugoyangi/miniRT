/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:59:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 08:53:10 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_ray *ray, t_vec outward_normal, t_hit_record *rec)
{
	rec->front_face = vec_dot(ray->direction, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec_mul_const(outward_normal, -1);
}

t_ray	ray(t_point origin, t_vec direction)
{
	t_ray	ret;

	ret.origin = origin;
	ret.direction = direction;
	ret.record.hit_anything = 0;
	ret.record.t = 0;
	ret.record.p = vec(0, 0, 0);
	ret.record.normal = vec(0, 0, 0);
	ret.record.front_face = 0;
	ret.t_max = INFINITY;
	ret.t_min = 0.001;
	return (ret);
}

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	ret;

	ret = vec_add(ray->origin, vec_mul_const(ray->direction, t));
	return (ret);
}

t_color	ray_color(t_ray *r, t_object **objects, int depth)
{
	t_vec	unit_direction;
	t_ray	tmp_ray;
	double	t;

	if (depth <= 0)
		return (color(0, 0, 0));
	if (hit_object(objects, r))
	{
		unit_direction = vec_add(r->record.normal, \
		random_on_hemisphere(r->record.normal));
		tmp_ray = ray(r->record.p, unit_direction);
		return (vec_mul_const(ray_color(&tmp_ray, objects, depth - 1), 0.5));
	}
	unit_direction = vec_unit(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec_add(vec_mul_const(vec(1.0, 1.0, 1.0), 1.0 - t) \
		, vec_mul_const(vec(0.5, 0.7, 1.0), t)));
}
