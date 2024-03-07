/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_transformed_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:28:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	matrix_apply(t_matrix m, t_vec vec, int w)
{
	t_vec	ret;

	ret.x = m.m1[0] * vec.x + m.m1[1] * vec.y + m.m1[2] * vec.z + m.m1[3] * w;
	ret.y = m.m2[0] * vec.x + m.m2[1] * vec.y + m.m2[2] * vec.z + m.m2[3] * w;
	ret.z = m.m3[0] * vec.x + m.m3[1] * vec.y + m.m3[2] * vec.z + m.m3[3] * w;
	return (ret);
}

t_ray	ray_transform(t_ray *ray, t_matrix inverse)
{
	t_ray		ret;

	ret = *ray;
	ret.origin = matrix_apply(inverse, ray->origin, 1);
	ret.direction = matrix_apply(inverse, ray->direction, 0);
	return (ret);
}

int	hit_transformed(t_object *obj, t_ray *_ray, t_interval *closest, \
					t_hit_record *rec)
{
	t_ray			tmp_ray;

	tmp_ray = *_ray;
	tmp_ray = ray_transform(&tmp_ray, obj->transform.inverse);
	if (!hit_object(obj, &tmp_ray, closest, rec))
		return (0);
	closest->max = rec->t;
	rec->p = matrix_apply(obj->transform.matrix, rec->p, 1);
	rec->normal = matrix_apply(obj->transform.matrix, rec->normal, 0);
	rec->normal = vec_unit(rec->normal);
	return (1);
}
