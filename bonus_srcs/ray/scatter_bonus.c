/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:26:05 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	reflectance(double cosine, double ratio)
{
	double	r0;

	r0 = (1 - ratio) / (1 + ratio);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

t_vec	refract(t_vec vec, t_vec normal, double ratio, double cos_theta)
{
	t_vec	r_out_perp;
	t_vec	r_out_parallel;

	r_out_perp = vec_mul_const(vec_add(vec, vec_mul_const(normal, \
	cos_theta)), ratio);
	r_out_parallel = vec_mul_const(normal, -sqrt(fabs(1.0 - \
	vec_length_squared(r_out_perp))));
	return (vec_add(r_out_perp, r_out_parallel));
}

t_vec	reflect(t_vec vec, t_vec normal)
{
	t_vec	ret;

	ret = vec_sub(vec, vec_mul_const(normal, 2 * vec_dot(vec, normal)));
	return (ret);
}

int	scatter(t_ray *_ray, t_hit_record *rec, \
			t_ray *scattered, t_scatter_record *srec)
{
	if (rec->material.type == METAL)
		return (metal_scatter(_ray, rec, srec));
	else if (rec->material.type == LAMBERTIAN)
		return (lambertian_scatter(_ray, rec, scattered, srec));
	else if (rec->material.type == DIELECTRIC)
		return (dielectric_scatter(_ray, rec, srec));
	else if (rec->material.type == DIFFUSE)
	{
		if (!rec->front_face)
			rec->material.emitted = color(0, 0, 0);
		return (0);
	}
	else if (rec->material.type == PHASE)
		return (phase_scatter(_ray, rec, scattered, srec));
	else
		return (0);
}
