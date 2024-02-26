/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:32:31 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 22:13:59 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_cap_record(double t, t_hit_record *rec, \
					t_ray *ray, t_cylinder *cylinder)
{
	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	if (rec->p.y < cylinder->center.y)
		rec->normal = vec(0, -1, 0);
	else
		rec->normal = vec(0, 1, 0);
	rec->material = cylinder->material;
	return (1);
}

int	hit_cap(t_ray *ray, t_cylinder *cylinder, t_interval _t, t_hit_record *rec)
{
	t_vec	oc;
	double	t;
	t_point	tmp;

	oc = vec_sub(ray->origin, cylinder->center);
	if (oc.x * oc.x + oc.z * oc.z <= pow(cylinder->diameter / 2, 2) && \
		oc.y >= -cylinder->height / 2 && oc.y <= cylinder->height / 2)
		return (0);
	if (oc.y < -cylinder->height / 2 || oc.y > cylinder->height / 2)
		if (oc.y * ray->direction.y > 0)
			return (0);
	t = -(oc.y) / ray->direction.y;
	if (oc.y > 0)
		t = -(oc.y - cylinder->height / 2) / ray->direction.y;
	else if (oc.y < 0)
		t = -(oc.y + cylinder->height / 2) / ray->direction.y;
	if (t < _t.min || t > _t.max)
		return (0);
	tmp = vec(oc.x + t * ray->direction.x, oc.y + t * ray->direction.y, \
	oc.z + t * ray->direction.z);
	if (tmp.x * tmp.x + tmp.z * tmp.z <= pow(cylinder->diameter / 2, 2))
		return (hit_cap_record(t, rec, ray, cylinder));
	return (0);
}

int	hit_cylinder_record(double t, t_hit_record *rec, \
						t_ray *ray, t_cylinder *cylinder)
{
	double	phi;
	double	theta;

	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vec((rec->p.x - cylinder->center.x) / \
	(cylinder->diameter / 2), 0, \
	(rec->p.z - cylinder->center.z) / (cylinder->diameter / 2));
	rec->normal = vec_unit(rec->normal);
	set_face_normal(ray, rec->normal, rec);
	rec->material = cylinder->material;
	phi = atan2(rec->normal.z, rec->normal.x);
	theta = asin(rec->normal.y);
	rec->u = 1 - (phi + M_PI) / (2 * M_PI);
	rec->v = (theta + M_PI / 2) / M_PI;
	return (1);
}

int	hit_cylinder(t_ray *ray, t_cylinder *cylinder, \
				t_interval _t, t_hit_record *rec)
{
	t_vec		oc;
	double		abc[3];
	double		discriminant;

	oc = vec_sub(ray->origin, cylinder->center);
	if (hit_cap(ray, cylinder, _t, rec))
		return (1);
	abc[0] = pow(ray->direction.x, 2) + pow(ray->direction.z, 2);
	abc[1] = 2 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
	abc[2] = pow(oc.x, 2) + pow(oc.z, 2) - pow(cylinder->diameter / 2, 2);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0 || discriminant < 0.0000001)
		return (0);
	abc[2] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	abc[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	abc[0] = fmin(abc[1], abc[2]);
	if (abc[0] < _t.min || abc[0] > _t.max)
		return (0);
	if (ray_at(ray, abc[0]).y < cylinder->center.y - cylinder->height / 2 || \
		ray_at(ray, abc[0]).y > cylinder->center.y + cylinder->height / 2)
		return (0);
	return (hit_cylinder_record(abc[0], rec, ray, cylinder));
}

t_cylinder	*cylinder(t_vec center, double diameter, \
				double height, t_material material)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	cylinder->center = center;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->material = material;
	cylinder->bounding_box = aabb_pad(aabb(vec(center.x - \
	diameter / 2, center.y - height / 2, center.z \
	- diameter / 2), vec(center.x + diameter / 2, center.y + \
	height / 2, center.z + diameter / 2)));
	return (cylinder);
}
