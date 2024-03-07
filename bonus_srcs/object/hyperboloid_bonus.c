/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:41:29 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	hit_hyperboloid_record(double t, t_hit_record *rec, \
							t_ray *ray, t_hyperboloid *hyperboloid)
{
	t_vec	tmp;

	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vec(2.0 * (rec->p.x - hyperboloid->center.x), \
	-2.0 * (rec->p.y - hyperboloid->center.y), \
	2.0 * (rec->p.z - hyperboloid->center.z));
	rec->normal = vec_unit(rec->normal);
	set_face_normal(ray, rec->normal, rec);
	rec->material = hyperboloid->material;
	tmp = vec_sub(rec->p, hyperboloid->center);
	rec->u = atan2(tmp.z, tmp.x) / (2 * PI);
	rec->v = (tmp.y + hyperboloid->height / 2) / hyperboloid->height;
}

int	hit_hyperboloid_set(double (*abc)[5], t_ray *ray, \
							t_hyperboloid *hyperboloid)
{
	t_vec	oc;
	double	discriminant;
	double	tmp;

	tmp = hyperboloid->diameter * hyperboloid->diameter / 16;
	oc = vec_sub(ray->origin, hyperboloid->center);
	(*abc)[0] = ray->direction.y * ray->direction.y - \
	ray->direction.x * ray->direction.x / tmp * 32 \
	- ray->direction.z * ray->direction.z / tmp * 32;
	(*abc)[1] = 2.0 * (oc.y * ray->direction.y - oc.x * ray->direction.x / \
	tmp * 32 - oc.z * ray->direction.z / tmp * 32);
	(*abc)[2] = oc.y * oc.y + hyperboloid->k * hyperboloid->k - \
	oc.x * oc.x / tmp * 32 - oc.z * oc.z / tmp * 32;
	discriminant = (*abc)[1] * ((*abc)[1]) - 4.0 * ((*abc)[0]) * ((*abc)[2]);
	if (discriminant < 0 || discriminant < 0.000001)
		return (0);
	(*abc)[2] = (-((*abc)[1]) - sqrt(discriminant)) / (2.0 * ((*abc)[0]));
	(*abc)[1] = (-((*abc)[1]) + sqrt(discriminant)) / (2.0 * ((*abc)[0]));
	return (1);
}

int	hit_hyperboloid(t_ray *ray, t_hyperboloid *hyperboloid, \
				t_interval _t, t_hit_record *rec)
{
	double	abc[5];

	if (!hit_hyperboloid_set(&abc, ray, hyperboloid))
		return (0);
	abc[3] = fmin(abc[2], abc[1]);
	abc[4] = fmax(abc[2], abc[1]);
	if (abc[3] < _t.min || abc[3] > _t.max)
	{
		if (abc[4] < _t.min || abc[4] > _t.max)
			return (0);
	}
	if (ray_at(ray, abc[3]).y > hyperboloid->center.y + hyperboloid->height / 2 \
	|| ray_at(ray, abc[3]).y < hyperboloid->center.y - hyperboloid->height / 2)
	{
		if (ray_at(ray, abc[4]).y > hyperboloid->center.y + \
		hyperboloid->height / 2 || ray_at(ray, abc[4]).y < \
		hyperboloid->center.y - hyperboloid->height / 2)
			return (0);
		abc[3] = abc[4];
	}
	if (abc[3] < _t.min || abc[3] > _t.max)
		return (0);
	hit_hyperboloid_record(abc[3], rec, ray, hyperboloid);
	return (1);
}

t_hyperboloid	*hyperboloid(t_point center, double diameter, \
						double height, t_material material)
{
	t_hyperboloid	*hyperboloid;

	hyperboloid = (t_hyperboloid *)ft_malloc(sizeof(t_hyperboloid));
	hyperboloid->center = center;
	hyperboloid->diameter = diameter;
	hyperboloid->height = height;
	hyperboloid->material = material;
	hyperboloid->k = 6;
	hyperboloid->bounding_box = aabb_pad(aabb(vec(center.x - \
	diameter, center.y - height / 2, center.z - diameter), \
	vec(center.x + diameter, center.y + height / 2, center.z + diameter)));
	return (hyperboloid);
}
