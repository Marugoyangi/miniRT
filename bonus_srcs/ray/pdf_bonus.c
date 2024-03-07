/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:30:50 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	onb_local(t_onb uvw, t_vec a)
{
	return (vec_add(vec_add(vec_mul_const(uvw.u, a.x), \
	vec_mul_const(uvw.v, a.y)), vec_mul_const(uvw.w, a.z)));
}

t_onb	onb(t_vec w)
{
	t_onb	uvw;
	t_vec	tmp[3];

	tmp[0] = vec_unit(w);
	if (fabs(tmp[0].x) > 0.9)
		tmp[1] = vec(0, 1, 0);
	else
		tmp[1] = vec(1, 0, 0);
	tmp[1] = vec_unit(vec_cross(tmp[0], tmp[1]));
	tmp[2] = vec_cross(tmp[0], tmp[1]);
	uvw.u = tmp[1];
	uvw.v = tmp[2];
	uvw.w = tmp[0];
	return (uvw);
}

t_pdf	pdf_cosine(t_ray *_ray, t_hit_record *rec, \
					t_ray *scattered, t_vec *direction)
{
	t_onb	uvw;
	t_vec	tmp;
	double	cosine;
	t_pdf	pdf;

	uvw = onb(rec->normal);
	tmp = onb_local(uvw, random_cosine_direction());
	if (direction)
		tmp = *direction;
	if (rec->material.type == LAMBERTIAN || rec->material.type == PHASE)
	{
		cosine = vec_dot(uvw.w, vec_unit(tmp));
		if (cosine < 0)
			cosine = 0;
		cosine = cosine / M_PI;
	}
	else
		cosine = 1 / (4 * M_PI);
	*scattered = ray(rec->p, tmp, _ray->time);
	pdf.value = cosine;
	pdf.generated = tmp;
	return (pdf);
}

double	scatter_pdf(t_hit_record *rec, t_ray *scattered)
{
	double	cosine;

	if (rec->material.type == LAMBERTIAN || rec->material.type == PHASE)
	{
		cosine = vec_dot(rec->normal, vec_unit(scattered->direction));
		if (cosine < 0)
			cosine = 0;
		return (cosine / M_PI);
	}
	else
		return (1 / (4 * M_PI));
}
