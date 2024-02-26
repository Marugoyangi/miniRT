/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:39:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 22:37:51 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_sphere_uv(t_hit_record *rec, t_vec p)
{
	double	phi;
	double	theta;

	phi = atan2(-p.z, p.x) + PI;
	theta = acos(-p.y);
	rec->u = phi / (2 * PI);
	rec->v = theta / PI;
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
	get_sphere_uv(rec, outward_normal);
}

int	hit_sphere(t_ray *ray, t_sphere *sphere, t_interval t, t_hit_record *rec)
{
	t_vec	oc;
	double	abc[3];
	double	discriminant;
	t_point	center;

	center = sphere->center;
	if (sphere->is_moving)
		center = vec_add(sphere->center, vec_mul_const (\
		sphere->velocity, ray->time));
	oc = vec_sub(ray->origin, center);
	abc[0] = vec_length_squared(ray->direction);
	abc[1] = vec_dot(oc, ray->direction);
	abc[2] = vec_length_squared(oc) - sphere->radius * sphere->radius;
	discriminant = abc[1] * abc[1] - abc[0] * abc[2];
	if (discriminant < 0 || discriminant < 0.000001)
		return (0);
	abc[2] = (-abc[1] - sqrt(discriminant)) / abc[0];
	if (abc[2] <= t.min || abc[2] >= t.max)
	{
		abc[2] = (-abc[1] + sqrt(discriminant)) / abc[0];
		if (abc[2] <= t.min || abc[2] >= t.max)
			return (0);
	}
	hit_sphere_record(abc[2], sphere, rec, ray);
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
