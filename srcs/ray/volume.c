/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   volume.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 11:45:11 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	phase_scatter(t_ray *_ray, t_hit_record *rec, \
				t_ray *scattered, t_scatter_record *srec)
{
	t_vec	random;

	random = random_cosine_direction();
	random = vec_unit(random);
	*scattered = ray(rec->p, random, _ray->time);
	srec->is_specular = 0;
	srec->attenuation = rec->material.albedo;
	return (1);
}

void	hit_volume_record_obj(double t, t_ray *ray, t_hit_record *rec, \
						t_object *object)
{
	rec->t = t;
	rec->p = ray_at(ray, t);
	if (object->transform.is_transformed)
		rec->p = matrix_apply(object->transform.matrix, rec->p, 1);
	rec->material.type = PHASE;
	rec->material.albedo = object->volume.color;
	rec->normal = vec(1, 0, 0);
	rec->front_face = 1;
	rec->object = object;
}

int	hit_volume_record(double (*n)[3], t_ray *tmp_ray, \
					t_hit_record (*rec)[2], t_object *object)
{
	(*n)[0] = vec_length(tmp_ray->direction);
	(*n)[1] = ((*rec)[1].t - (*rec)[0].t) * (*n)[0];
	(*n)[2] = (-1.0 / object->volume.density) * log(random_double(0.0, 1.0));
	if ((*n)[2] > (*n)[1])
		return (0);
	return (1);
}

int	hit_volume_clamp(t_hit_record (*rec)[2], t_interval *closest)
{
	if ((*rec)[0].t < closest->min)
		(*rec)[0].t = closest->min;
	if ((*rec)[1].t > closest->max)
		(*rec)[1].t = closest->max;
	if ((*rec)[0].t >= (*rec)[1].t)
		return (0);
	if ((*rec)[0].t < 0)
		(*rec)[0].t = 0;
	return (1);
}

int	hit_volume(t_object *object, t_ray *_ray, \
				t_interval *closest, t_hit_record *rec)
{
	t_hit_record	tmp_rec[2];
	double			n[3];
	t_ray			tmp_ray;
	t_interval		tmp;

	tmp = interval(0.0001, closest->max);
	tmp_ray = *_ray;
	if (object->transform.is_transformed)
		tmp_ray = ray_transform(&tmp_ray, object->transform.inverse);
	if (!hit_object(object, &tmp_ray, &tmp, &tmp_rec[0]))
		return (0);
	tmp = interval(tmp_rec[0].t + 0.00001, closest->max);
	tmp_ray.t = tmp;
	if (!hit_object(object, &tmp_ray, &tmp, &tmp_rec[1]))
		return (0);
	if (!hit_volume_clamp(&tmp_rec, closest))
		return (0);
	if (!hit_volume_record(&n, &tmp_ray, &tmp_rec, object))
		return (0);
	hit_volume_record_obj((tmp_rec[0].t + n[2] / n[0]), \
	&tmp_ray, rec, object);
	closest->max = tmp_rec[0].t;
	return (1);
}
