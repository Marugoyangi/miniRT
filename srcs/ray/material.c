/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:58:27 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/12 07:36:12 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	phase_scatter(t_ray *_ray, t_hit_record *rec, t_color *attenuation, \
				t_ray *scattered)
{
	t_vec	random;

	random = random_on_hemisphere(rec->normal);
	*scattered = ray(rec->p, random, _ray->time);
	*attenuation = rec->material.albedo;
	return (1);
}

int	dielectric_scatter(t_ray *_ray, t_hit_record *rec, t_color *attenuation, \
				t_ray *scattered)
{
	double	refraction_ratio;
	t_vec	unit_direction;
	t_vec	result;
	double	cos_theta;

	if (rec->front_face)
		refraction_ratio = 1.0 / rec->material.ref_idx;
	else
		refraction_ratio = rec->material.ref_idx;
	unit_direction = vec_unit(_ray->direction);
	cos_theta = fmin(vec_dot(rec->normal, vec_mul_const(unit_direction, \
					-1.0)), 1.0);
	if (refraction_ratio * (sqrt(1.0 - cos_theta * cos_theta)) > 1.0 \
		|| reflectance(cos_theta, refraction_ratio) > random_double(0.0, 1.0))
		result = reflect(unit_direction, rec->normal);
	else
		result = refract(unit_direction, rec->normal, refraction_ratio, \
			cos_theta);
	*scattered = ray(rec->p, result, _ray->time);
	*attenuation = color(1.0, 1.0, 1.0);
	return (1);
}

int	lambertian_scatter(t_ray *_ray, t_hit_record *rec, t_color *attenuation, \
				t_ray *scattered)
{
	t_vec		scattered_direction;
	t_vec		random_vec;
	t_vec		tmp;

	random_vec = random_in_sphere();
	random_vec = vec_unit(random_vec);
	scattered_direction = vec_add(rec->normal, random_vec);
	if (is_near_zero(scattered_direction))
		scattered_direction = rec->normal;
	*scattered = ray(rec->p, scattered_direction, _ray->time);
	if (rec->material.texture.type == CHECKER)
		*attenuation = checker(&rec->material.texture.checker, rec);
	else if (rec->material.texture.type == IMAGE)
	{
		*attenuation = image_color(rec->material.texture.image, rec);
		if (rec->material.texture.is_bumped)
		{
			scattered_direction = image_color(rec->material.texture.normal_map, rec);
			scattered_direction = vec_add(random_vec, scattered_direction);
			*scattered = ray(rec->p, vec_unit(scattered_direction), _ray->time);
		}
	}
	else if (rec->material.texture.type == NOISE)
	{
		tmp = vec_mul_const(rec->p, rec->material.texture.perlin.scale);
		*attenuation = vec_mul_const(color(0.5, 0.5, 0.5), 1 + sin(tmp.y + 10 * noise_turb(&rec->material.texture.perlin, tmp)));
	}
	else
		*attenuation = rec->material.albedo;
	return (1);
}

int	metal_scatter(t_ray *_ray, t_hit_record *rec, t_color *attenuation, \
				t_ray *scattered)
{
	t_vec	scattered_direction;
	t_vec	random_vec;

	random_vec = random_in_sphere();
	random_vec = vec_unit(random_vec);
	scattered_direction = reflect(vec_unit(_ray->direction), rec->normal);
	scattered_direction = vec_add(scattered_direction, \
	vec_mul_const(random_vec, rec->material.fuzz));
	*scattered = ray(rec->p, scattered_direction, _ray->time);
	*attenuation = rec->material.albedo;
	return (vec_dot(scattered->direction, rec->normal) > 0);
}

t_material	material(int type, t_color albedo, double fuzz, double ref_idx)
{
	t_material	material;

	material.type = type;
	material.albedo = albedo;
	if (fuzz >= 1)
		material.fuzz = 1;
	else
		material.fuzz = fuzz;
	material.ref_idx = ref_idx;
	if (type == DIFFUSE)
		material.emitted = albedo;
	else
		material.emitted = color(0, 0, 0);
	return (material);
}