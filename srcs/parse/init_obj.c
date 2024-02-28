/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:22:56 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/29 04:10:29 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_hyperboloid(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[2];

	color[0] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	color[1] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	set_texture(minirt, &material, node->etc[1], color);
	obj = object(HYPERBOLOID, hyperboloid(node->coord, \
	node->geometric[0], node->geometric[1], \
	material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->transform[1], \
		node->transform[2]);
	else
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.1;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
}

void	set_cylinder(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[2];

	color[0] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	color[1] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	set_texture(minirt, &material, node->etc[1], color);
	obj = object(CYLINDER, cylinder(node->coord, node->geometric[0], \
	node->geometric[1], material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->transform[1], \
	node->transform[2]);
	else
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.1;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
}

void	set_plane(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[2];
	t_vec		quv[3];

	color[0] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	color[1] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	quv[1] = vec_mul_const(vec(1, 0, 0), 1000);
	quv[2] = vec_mul_const(vec(0, 1, 0), 1000);
	quv[0] = vec_sub(node->coord, vec_div_const(quv[1], 2));
	quv[0] = vec_sub(quv[0], vec_div_const(quv[2], 2));
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	set_texture(minirt, &material, node->etc[1], color);
	obj = object(QUAD, quad(quv[0], quv[1], quv[2], material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->transform[1], \
		node->transform[2]);
	else
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.1;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
}

void	set_sphere(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		_color[2];

	_color[0] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	_color[1] = vec(random_double(0, 1), random_double(0, 1), \
	random_double(0, 1));
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	set_texture(minirt, &material, node->etc[1], _color);
	obj = object(SPHERE, sphere(node->coord, node->geometric[0], \
	material, vec(0, 0, 0)));
	if (!node->is_transformed)
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.1;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
}
