/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 03:45:00 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/17 08:01:16 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	get_ray(t_minirt *minirt, double u, double v)
{
	t_camera	camera;
	t_vec		dof_org;
	t_vec		dof_sample;

	camera = minirt->camera;
	if (camera.dof_angle > 0)
	{
		dof_sample = random_in_unit_disk();
		dof_org = vec_add(camera.origin, \
		vec_add(vec_mul_const(camera.basis.dof_u, dof_sample.x), \
		vec_mul_const(camera.basis.dof_v, dof_sample.y)));
	}
	else
		dof_org = camera.origin;
	return (ray(dof_org, vec_sub(vec_add(\
			camera.basis.lower_left_corner, \
			vec_add(vec_mul_const(camera.basis.viewport_u, u), \
			vec_mul_const(camera.basis.viewport_v, v))), \
			dof_org)));
}

void	set_camera_basis(t_minirt *minirt)
{
	t_basis	*basis;
	double	dof_rad;

	basis = &(minirt->camera.basis);
	basis->w = vec_unit(vec_sub(minirt->camera.origin, \
	minirt->camera.look_at));
	basis->u = vec_unit(vec_cross(minirt->camera.vertical_up, \
	basis->w));
	basis->v = vec_cross(basis->w, basis->u);
	basis->viewport_u = vec_mul_const(basis->u, minirt->camera.viewport_width);
	basis->viewport_v = vec_mul_const(basis->v, minirt->camera.viewport_height);
	basis->lower_left_corner = vec_sub(minirt->camera.origin, \
	vec_add(vec_add(vec_div_const(basis->viewport_u, 2), \
	vec_div_const(basis->viewport_v, 2)), vec_mul_const(basis->w, \
	minirt->camera.focus_distance)));
	dof_rad = minirt->camera.focus_distance * \
	tan(degree_to_rad(minirt->camera.dof_angle / 2));
	basis->dof_u = vec_mul_const(basis->u, dof_rad);
	basis->dof_v = vec_mul_const(basis->v, dof_rad);
}

void	set_camera(t_minirt *minirt)
{
	double		height;
	t_camera	*camera;

	camera = &minirt->camera;
	minirt->camera.max_depth = 50;
	minirt->camera.aspect_ratio = 16.0 / 9.0;
	minirt->camera.fov = 20;
	minirt->camera.origin = vec(13, 2, 3);
	minirt->camera.look_at = vec(0, 0, 0);
	minirt->camera.vertical_up = vec(0, 1, 0);
	minirt->camera.dof_angle = 0.6;
	minirt->camera.focus_distance = 10.0;
	minirt->camera.samples_per_pixel = 10;
	height = tan(degree_to_rad(camera->fov) / 2);
	camera->viewport_height = 2.0 * height * camera->focus_distance;
	camera->viewport_width = camera->aspect_ratio * \
	camera->viewport_height;
	set_camera_basis(minirt);
}
