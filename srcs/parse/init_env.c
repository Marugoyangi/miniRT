/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:46:12 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:25:27 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_light(t_minirt *minirt, t_p_node *node)
{
	t_material	light;
	t_object	*obj;
	t_object	*_light;
	t_vec		color;

	color = vec_mul_const(vec(node->color[0], node->color[1], node->color[2]), \
	node->geometric[0] * 1000);
	light = material(DIFFUSE, color, 0, 0);
	obj = object(SPHERE, sphere(node->coord, 0.1, light, vec(0, 0, 0)));
	_light = object(SPHERE, sphere(node->coord, 0.1, light, vec(0, 0, 0)));
	object_add_back(minirt, obj);
	light_add_back(minirt, _light);
}

void	set_cam(t_minirt *minirt, t_p_node *node)
{
	t_vec	vecs[3];

	vecs[0] = node->coord;
	vecs[1] = vec_add(node->normal, node->coord);
	if (node->normal.x == 0 && node->normal.y == 0 && node->normal.z == 0)
		ft_error("Error\n");
	vecs[2] = vec(0, 1, 0);
	printf("vecs[1] %f", vecs[1].x);
	printf("vecs[1] %f", vecs[1].y);
	printf("vecs[1] %f", vecs[1].z);
	set_camera(minirt, node->etc[0], vecs, 0.0);
	minirt->camera.background = color(0.01, 0.01, 0.01);
}

void	set_ambient(t_minirt *minirt, t_p_node *node)
{
	t_vec	color;
	double	ratio;

	color = vec(node->color[0], node->color[1], node->color[2]);
	ratio = node->geometric[0] * 0.0002;
	color = vec_mul_const(color, ratio);
	minirt->ambient = color;
}
