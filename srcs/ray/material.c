/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:58:27 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 22:34:46 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	dielectric_scatter(t_ray *_ray, t_hit_record *rec, t_scatter_record *srec)
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
	rec->material.albedo = color(1.0, 1.0, 1.0);
	srec->is_specular = 1;
	srec->attenuation = rec->material.albedo;
	srec->specular_ray = ray(rec->p, result, _ray->time);
	return (1);
}

int	lambertian_bumped(t_ray *_ray, t_hit_record *rec, t_ray *scattered, \
				t_scatter_record *srec)
{
	t_vec	scattered_direction;

	scattered_direction = \
	image_color(rec->material.texture.normal_map, rec);
	scattered_direction = \
	vec_add(vec_unit(random_in_sphere()), scattered_direction);
	*scattered = ray(rec->p, scattered_direction, _ray->time);
	srec->is_specular = 1;
	srec->attenuation = rec->material.albedo;
	srec->specular_ray = *scattered;
	return (1);
}

int	lambertian_scatter(t_ray *_ray, t_hit_record *rec, \
					t_ray *scattered, t_scatter_record *srec)
{
	t_vec		scattered_direction;
	t_vec		random_vec;
	t_vec		tmp;

	random_vec = random_cosine_direction();
	scattered_direction = vec_add(rec->normal, random_vec);
	*scattered = ray(rec->p, vec_unit(scattered_direction), _ray->time);
	if (rec->material.texture.type == CHECKER)
		rec->material.albedo = checker(&rec->material.texture.checker, rec);
	else if (rec->material.texture.type == IMAGE)
	{
		rec->material.albedo = image_color(rec->material.texture.image, rec);
		if (rec->material.texture.is_bumped)
			return (lambertian_bumped(_ray, rec, scattered, srec));
	}
	else if (rec->material.texture.type == NOISE)
	{
		tmp = vec_mul_const(rec->p, rec->material.texture.perlin.scale);
		rec->material.albedo = vec_mul_const(color(0.5, 0.5, 0.5), \
		1 + sin(tmp.y + 100 * noise_turb(&rec->material.texture.perlin, tmp)));
	}
	srec->is_specular = 0;
	srec->attenuation = rec->material.albedo;
	return (1);
}

int	metal_scatter(t_ray *_ray, t_hit_record *rec, t_scatter_record *srec)
{
	t_vec	scattered_direction;

	scattered_direction = reflect(vec_unit(_ray->direction), rec->normal);
	scattered_direction = vec_add(scattered_direction, \
	vec_mul_const(random_in_sphere(), rec->material.fuzz));
	srec->attenuation = rec->material.albedo;
	srec->is_specular = 1;
	srec->specular_ray = ray(rec->p, scattered_direction, _ray->time);
	return (1);
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
