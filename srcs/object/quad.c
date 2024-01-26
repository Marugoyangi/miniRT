/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 06:23:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 10:24:15 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_interior(t_hit_record *rec, double alpha, double beta)
{
	if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1)
		return (0);
	rec->u = alpha;
	rec->v = beta;
	return (1);
}

int	hit_quad(t_ray *ray, t_quad *quad, double max, t_hit_record *rec)
{
	double	tmp;
	t_vec	hit_point;
	double	alpha;
	double	beta;

	tmp = vec_dot(quad->normal, ray->direction);
	if (fabs(tmp) < 0.0001)
		return (0);
	tmp = (quad->d - vec_dot(quad->normal, ray->origin)) / tmp;
	if (tmp > max)
		return (0);
	rec->p = ray_at(ray, tmp);
	hit_point = vec_sub(rec->p, quad->q);
	alpha = vec_dot(quad->w, vec_cross(hit_point, quad->v));
	beta = vec_dot(quad->w, vec_cross(quad->u, hit_point));
	if (!is_interior(rec, alpha, beta))
		return (0);
	rec->t = tmp;
	rec->material = quad->material;
	set_face_normal(ray, quad->normal, rec);
	return (1);
}

t_quad	*quad(t_point _q, t_vec u, t_vec v, t_material material)
{
	t_quad	*ret;
	t_vec	tmp;

	ret = (t_quad *)malloc(sizeof(t_quad));
	ret->q = _q;
	ret->u = u;
	ret->v = v;
	ret->material = material;
	tmp = vec_add(_q, vec_add(u, v));
	ret->bounding_box = aabb_pad(aabb(_q, tmp));
	tmp = vec_cross(u, v);
	ret->normal = vec_unit(tmp);
	ret->d = vec_dot(ret->normal, _q);
	ret->w = vec_div_const(tmp, vec_dot(tmp, tmp));
	return (ret);
}
