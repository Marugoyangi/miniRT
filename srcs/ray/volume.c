/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/12 04:25:14 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_volume(t_object *object, t_ray *ray, t_interval *closest, t_hit_record *rec)
{
	t_hit_record	tmp_rec1;
	t_hit_record	tmp_rec2;
	double			hit_random;
	t_ray			tmp_ray;
	t_interval		tmp;

	tmp_ray = *ray;
	tmp = interval(0.001, closest->max);
	tmp_ray.t = interval(0.001, INFINITY);
	if (object->transform.is_transformed)
		tmp_ray = ray_transform(&tmp_ray, object->transform.inverse);
	if (hit_object(object, &tmp_ray, &tmp, &tmp_rec1))
	{
		tmp = interval(tmp_rec1.t, INFINITY);
		tmp_ray.t = interval(tmp_rec1.t + 0.0001, INFINITY);
		if (hit_object(object, &tmp_ray, &tmp, &tmp_rec2))
		{
			if (tmp_rec1.t < tmp.min)
				tmp_rec1.t = tmp.min;
			if (tmp_rec2.t > tmp.max)
				tmp_rec2.t = tmp.max;
			if (tmp_rec1.t >= tmp_rec2.t)
				return (0);
			if (tmp_rec1.t < 0)
				tmp_rec1.t = 0;
			hit_random = (-1.0 / object->volume.density) * log(random_double(0.0, 1.0));
			if (vec_length(tmp_ray.direction) * (tmp_rec2.t - tmp_rec1.t) \
				< hit_random)
				return (0);
			rec->t = tmp_rec1.t + hit_random / vec_length(tmp_ray.direction);
			rec->p = ray_at(&tmp_ray, rec->t);
			rec->material.type = PHASE;
			rec->material.albedo = object->volume.color;
			rec->normal = vec(1, 0, 0);
			rec->front_face = 1;
			return (1);
		}
	}
	return (0);
}
