/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:13:42 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 06:22:05 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	aabb_hit(t_aabb aabb, t_ray *ray, t_interval ray_t)
{
	int			i;
	t_interval	t;
	double		inv_d;
	double		origin;

	i = 0;
	t = interval(0, 0);
	while (i < 3)
	{
		inv_d = 1 / ((double *)&ray->direction)[i];
		origin = ((double *)&ray->origin)[i];
		t.min = (axis(aabb, i).min - origin) * inv_d;
		t.max = (axis(aabb, i).max - origin) * inv_d;
		if (inv_d < 0)
			ft_swap(&t.min, &t.max);
		if (t.min > ray_t.min)
			ray_t.min = t.min;
		if (t.max < ray_t.max)
			ray_t.max = t.max;
		if (ray_t.max <= ray_t.min)
			return (0);
		i++;
	}
	return (1);
}

t_interval	axis(t_aabb aabb, int n)
{
	if (n == 0)
		return (aabb.x);
	else if (n == 1)
		return (aabb.y);
	else
		return (aabb.z);
}

t_aabb	aabb(t_point a, t_point b)
{
	t_aabb	aabb;

	aabb.x.min = fmin(a.x, b.x);
	aabb.x.max = fmax(a.x, b.x);
	aabb.y.min = fmin(a.y, b.y);
	aabb.y.max = fmax(a.y, b.y);
	aabb.z.min = fmin(a.z, b.z);
	aabb.z.max = fmax(a.z, b.z);
	return (aabb);
}

t_aabb	aabb_b(t_aabb a, t_aabb b)
{
	t_aabb	aabb;

	aabb.x = interval_union(a.x, b.x);
	aabb.y = interval_union(a.y, b.y);
	aabb.z = interval_union(a.z, b.z);
	return (aabb);
}

t_aabb	aabb_pad(t_aabb aabb)
{
	double	padding;

	padding = 0.0001;
	if (interval_size(aabb.x) < padding)
		aabb.x = interval_padding(aabb.x, padding);
	if (interval_size(aabb.y) < padding)
		aabb.y = interval_padding(aabb.y, padding);
	if (interval_size(aabb.z) < padding)
		aabb.z = interval_padding(aabb.z, padding);
	return (aabb);
}
