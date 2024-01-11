/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 03:45:00 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 07:09:09 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	get_ray(t_camera camera, double u, double v)
{
	return (ray(camera.origin, vec_sub(vec_add(camera.lower_left_corner, \
			vec(u * camera.viewport_width, v * camera.viewport_height, 0)), \
			camera.origin)));
}

void	set_camera(t_minirt *minirt)
{
	minirt->camera.aspect_ratio = 16.0 / 9.0;
	minirt->camera.viewport_height = 2.0;
	minirt->camera.viewport_width = minirt->camera.viewport_height \
	* minirt->camera.aspect_ratio;
	minirt->camera.focal_length = 1.0;
	minirt->camera.origin = vec(0, 0, 0);
	minirt->camera.lower_left_corner = vec_sub(minirt->camera.origin, \
	vec(minirt->camera.viewport_width / 2, minirt->camera.viewport_height / 2, \
	minirt->camera.focal_length));
	minirt->camera.samples_per_pixel = 10;
}
