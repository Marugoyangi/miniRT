/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:39:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 02:47:54 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_sphere_record(double c, t_sphere *sphere, t_hit_record *rec, \
						t_ray *ray)
{
	rec->t = c;
	rec->p = ray_at(ray, c);
	set_face_normal(ray, vec_div_const(vec_sub(rec->p, sphere->center), \
	sphere->radius), rec);
}

int	hit_sphere(t_ray *ray, t_sphere *sphere, double t_max, t_hit_record *rec)
{
	t_vec	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = vec_sub(ray->origin, sphere->center);
	a = vec_length_squared(ray->direction);
	half_b = vec_dot(oc, ray->direction);
	c = vec_length_squared(oc) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	discriminant = sqrt(discriminant);
	c = (-half_b - discriminant) / a;
	if (c < ray->t_min || c > t_max)
	{
		c = (-half_b + discriminant) / a;
		if (c < ray->t_min || c > t_max)
			return (0);
	}
	hit_sphere_record(c, sphere, rec, ray);
	return (1);
}

t_sphere	*sphere(t_point center, double radius)
{
	t_sphere	*ret;

	ret = (t_sphere *)ft_malloc(sizeof(t_sphere));
	ret->center = center;
	ret->radius = radius;
	return (ret);
}
