/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:53:18 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/07 18:07:25 by jeongbpa         ###   ########.fr       */
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

t_ray	ray(t_point origin, t_vec direction, double time)
{
	t_ray	ret;

	ret.origin = origin;
	ret.direction = direction;
	ret.t.max = INFINITY;
	ret.t.min = 0.001;
	ret.time = time;
	return (ret);
}

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	ret;

	ret = vec_add(ray->origin, vec_mul_const(ray->direction, t));
	return (ret);
}

t_color	ray_color(t_bvh *node, t_ray *r, int depth, t_minirt *minirt)
{
	t_ray			tmp_ray;
	t_hit_record	rec;
	t_interval		closest;

	if (depth <= 0)
		return (color(0, 0, 0));
	rec.hit_anything = 0;
	rec.img_width = minirt->img_width;
	rec.img_height = minirt->img_height;
	closest = r->t;
	bvh_hit(node, r, &closest, &rec);
	if (rec.hit_anything)
	{
		if (scatter(r, &rec, &tmp_ray))
			return (vec_add(vec_mul(ray_color(node, &tmp_ray, depth - 1, minirt), \
			rec.material.albedo), rec.material.emitted));
		return (rec.material.emitted);
	}
	return (minirt->camera.background);
}
