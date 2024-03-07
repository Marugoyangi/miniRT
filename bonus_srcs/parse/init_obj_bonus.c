/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:22:56 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_hyperboloid(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[2];

	color[0] = random_vec(0, 1);
	color[1] = random_vec(0, 1);
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	if (node->etc[0] == LAMBERTIAN)
		set_texture(minirt, &material, node->etc[1]);
	obj = object(HYPERBOLOID, hyperboloid(node->coord, \
	node->geometric[0], node->geometric[1], \
	material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->transform[1], \
		node->transform[2]);
	else
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	object_add_back(minirt, obj);
	if (node->etc[0] == DIFFUSE)
		light_add_back(minirt, object(HYPERBOLOID, hyperboloid(node->coord, \
		node->geometric[0], node->geometric[1], material)));
}

void	set_cylinder(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[2];

	color[0] = random_vec(0, 1);
	color[1] = random_vec(0, 1);
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	if (node->etc[0] == LAMBERTIAN)
		set_texture(minirt, &material, node->etc[1]);
	obj = object(CYLINDER, cylinder(node->coord, node->geometric[0], \
	node->geometric[1], material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->transform[1], \
	node->transform[2]);
	else
		transform(obj, node->transform[0], node->transform[1], \
		node->transform[2]);
	object_add_back(minirt, obj);
	if (node->etc[0] == DIFFUSE)
		light_add_back(minirt, object(CYLINDER, cylinder(node->coord, \
		node->geometric[0], node->geometric[1], material)));
}

void	set_plane(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		quv[3];

	quv[1] = vec_mul_const(vec(1, 0, 0), 1000);
	quv[2] = vec_mul_const(vec(0, 1, 0), 1000);
	quv[0] = vec(-500, -500, 0);
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	if (node->etc[0] == LAMBERTIAN)
		set_texture(minirt, &material, node->etc[1]);
	obj = object(QUAD, quad(quv[0], quv[1], quv[2], material));
	if (!node->is_transformed)
		transform_by_normal(obj, node->normal, node->coord, \
		node->transform[2]);
	else
		transform(obj, node->transform[0], vec_add(node->coord, \
		node->transform[1]), node->transform[2]);
	object_add_back(minirt, obj);
	if (node->etc[0] == DIFFUSE)
		light_add_back(minirt, object(QUAD, quad(quv[0], quv[1], quv[2], \
		material)));
}

void	set_sphere(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		_color;

	_color = vec(0, 0, 0);
	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	if (node->etc[0] == LAMBERTIAN)
		set_texture(minirt, &material, node->etc[1]);
	if (node->etc[0] == MOVING)
		_color = vec_add(node->coord, random_vec(-node->geometric[0] * 2, \
		node->geometric[0] * 2));
	obj = object(SPHERE, sphere(node->coord, node->geometric[0], \
	material, _color));
	transform(obj, node->transform[0], node->transform[1], node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.001;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
	if (node->etc[0] == DIFFUSE)
		light_add_back(minirt, object(SPHERE, sphere(node->coord, \
		node->geometric[0], material, _color)));
}

void	set_box(t_minirt *minirt, t_p_node *node)
{
	t_material	material;
	t_object	*obj;
	t_vec		color[3];

	set_material(&material, node->etc[0], vec(node->color[0], \
	node->color[1], node->color[2]));
	if (node->etc[0] == LAMBERTIAN)
		set_texture(minirt, &material, node->etc[1]);
	color[2] = vec_div_const(vec_sub(node->normal, node->coord), 2);
	obj = object(BOX, box(vec_mul_const(color[2], -1), color[2], material));
	color[2] = vec_add(node->coord, color[2]);
	transform(obj, node->transform[0], vec_add(color[2], node->transform[1]), \
	node->transform[2]);
	if (node->etc[0] == PHASE)
	{
		obj->volume.density = 0.001;
		obj->volume.color = vec(node->color[0], node->color[1], \
		node->color[2]);
	}
	object_add_back(minirt, obj);
	if (node->etc[0] == DIFFUSE)
		light_add_back(minirt, object(BOX, box(node->coord, node->normal, \
		material)));
}
