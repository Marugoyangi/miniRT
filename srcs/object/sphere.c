/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:39:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 03:25:33 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_sphere_uv(t_hit_record *rec, t_vec p)
{
	double	phi;
	double	theta;

	phi = atan2(-p.z, p.x) + M_PI;
	theta = acos(-p.y);
	rec->u = phi / (2 * M_PI);
	rec->v = 1 - theta / M_PI;
}

void	hit_sphere_record(double c, t_sphere *sphere, t_hit_record *rec, \
						t_ray *ray)
{
	t_vec	outward_normal;

	rec->t = c;
	rec->p = ray_at(ray, c);
	outward_normal = vec_div_const(vec_sub(rec->p, sphere->center), \
	sphere->radius);
	set_face_normal(ray, outward_normal, rec);
	if (sphere->material.texture.type == CHECKER)
		get_sphere_uv(rec, vec_sub(rec->p, sphere->center));
	else
		get_sphere_uv(rec, outward_normal);
}

int	hit_sphere(t_ray *ray, t_sphere *sphere, double t, t_hit_record *rec)
{
	t_vec	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_point	center;

	if (sphere->is_moving)
		center = vec_add(sphere->center, vec_mul_const (\
		sphere->velocity, ray->time));
	else
		center = sphere->center;
	oc = vec_sub(ray->origin, center);
	a = vec_length_squared(ray->direction);
	half_b = vec_dot(oc, ray->direction);
	c = vec_length_squared(oc) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	discriminant = sqrt(discriminant);
	c = (-half_b - discriminant) / a;
	if (c <= ray->t.min || c >= t)
	{
		c = (-half_b + discriminant) / a;
		if (c <= ray->t.min || c >= t)
			return (0);
	}
	hit_sphere_record(c, sphere, rec, ray);
	return (1);
}

t_sphere	*sphere(t_point center, double radius, t_material material, \
					t_point moved)
{
	t_sphere	*ret;

	ret = (t_sphere *)ft_malloc(sizeof(t_sphere));
	ret->center = center;
	ret->radius = radius;
	ret->material = material;
	if (moved.x != 0 || moved.y != 0 || moved.z != 0)
		ret->is_moving = 1;
	else
		ret->is_moving = 0;
	ret->velocity = vec_sub(moved, center);
	if (!ret->is_moving)
		ret->bounding_box = aabb(vec_sub(center, vec(radius, radius, radius)), \
							vec_add(center, vec(radius, radius, radius)));
	else
		ret->bounding_box = aabb_b(aabb(vec_sub(center, vec(radius, radius, \
							radius)), vec_add(center, vec(radius, radius, \
							radius))), aabb(vec_sub(moved, vec(radius, \
							radius, radius)), vec_add(moved, vec(radius, \
							radius, radius))));
	return (ret);
}
