/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypoboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:33:56 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 22:02:47 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_cap_record2(double t, t_hit_record *rec, \
					t_ray *ray, t_hypoboloid *hypoboloid)
{
	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	if (rec->p.y < hypoboloid->center.y)
		rec->normal = vec(0, -1, 0);
	else
		rec->normal = vec(0, 1, 0);
	rec->material = hypoboloid->material;
	return (1);
}

int	hit_cap2(t_ray *ray, t_hypoboloid *hypoboloid, \
			t_interval _t, t_hit_record *rec)
{
	t_vec	oc;
	double	t;
	t_point	tmp;

	oc = vec_sub(ray->origin, hypoboloid->center);
	if (oc.x * oc.x + oc.z * oc.z <= pow(hypoboloid->diameter / 2, 2) \
	&& oc.y >= -hypoboloid->height / 2 - hypoboloid->k && \
	oc.y <= hypoboloid->height / 2 + hypoboloid->k)
		return (0);
	if (oc.y < -hypoboloid->height / 2 - hypoboloid->k || \
	oc.y > hypoboloid->height / 2 + hypoboloid->k)
		if (oc.y * ray->direction.y > 0)
			return (0);
	t = -(oc.y) / ray->direction.y;
	if (oc.y > 0)
		t = -(oc.y - hypoboloid->height / 2) / ray->direction.y;
	else if (oc.y < 0)
		t = -(oc.y + hypoboloid->height / 2) / ray->direction.y;
	if (t < _t.min || t > _t.max)
		return (0);
	tmp = vec(oc.x + t * ray->direction.x, oc.y + t * \
	ray->direction.y, oc.z + t * ray->direction.z);
	if (tmp.x * tmp.x + tmp.z * tmp.z <= pow(hypoboloid->diameter, 2))
		return (hit_cap_record2(t, rec, ray, hypoboloid));
	return (0);
}

void	hypoboloid_set(double (*abc)[3], t_vec *oc, \
					t_ray *ray, t_hypoboloid *hypoboloid)
{
	*oc = vec_sub(ray->origin, hypoboloid->center);
	(*abc)[0] = ray->direction.y * ray->direction.y - \
	ray->direction.x * ray->direction.x - ray->direction.z * ray->direction.z;
	(*abc)[1] = 2.0 * (oc->y * ray->direction.y - oc->x * ray->direction.x \
	- oc->z * ray->direction.z);
	(*abc)[2] = oc->y * oc->y + hypoboloid->k - oc->x * oc->x \
	- oc->z * oc->z;
}

int	hit_hypoboloid(t_ray *ray, t_hypoboloid *hypoboloid, \
				t_interval _t, t_hit_record *rec)
{
	double	abc[3];
	double	discriminant;
	t_vec	oc;

	if (hit_cap2(ray, hypoboloid, _t, rec))
		return (1);
	hypoboloid_set(&abc, &oc, ray, hypoboloid);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0 || discriminant < 0.0000001)
		return (0);
	discriminant = sqrt(discriminant);
	abc[2] = (-abc[1] - discriminant) / (2 * abc[0]);
	abc[1] = (-abc[1] + discriminant) / (2 * abc[0]);
	abc[0] = fmin(abc[1], abc[2]);
	rec->t = abc[0];
	if (rec->t < _t.min || rec->t > _t.max)
		return (0);
	rec->p = ray_at(ray, rec->t);
	if (rec->p.y < hypoboloid->center.y - hypoboloid->height / 2 || \
		rec->p.y > hypoboloid->center.y + hypoboloid->height / 2)
		return (0);
	rec->normal = vec_unit(vec(-2 * rec->p.x, 2 * rec->p.y, -2 * rec->p.z));
	rec->material = hypoboloid->material;
	return (1);
}

t_hypoboloid	*hypoboloid(t_point center, double diameter, \
						double height, t_material material)
{
	t_hypoboloid	*hypoboloid;

	hypoboloid = (t_hypoboloid *)ft_malloc(sizeof(t_hypoboloid));
	hypoboloid->center = center;
	hypoboloid->diameter = diameter;
	hypoboloid->height = height;
	hypoboloid->material = material;
	hypoboloid->k = -200;
	hypoboloid->bounding_box = aabb(vec_sub(center, \
	vec(diameter, height / 2 + hypoboloid->k, diameter)), \
	vec_add(center, vec(diameter, height / 2 + hypoboloid->k, diameter)));
	return (hypoboloid);
}
