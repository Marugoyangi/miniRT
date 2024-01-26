/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:00:24 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 10:23:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone	*cone_copy(t_cone *cone)
{
	t_cone	*new_cone;

	new_cone = (t_cone *)ft_malloc(sizeof(t_cone));
	new_cone->center = cone->center;
	new_cone->normal = cone->normal;
	new_cone->color = cone->color;
	new_cone->material = cone->material;
	new_cone->bounding_box = cone->bounding_box;
	return (new_cone);
}

t_cylinder	*cylinder_copy(t_cylinder *cylinder)
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	new_cylinder->center = cylinder->center;
	new_cylinder->normal = cylinder->normal;
	new_cylinder->height = cylinder->height;
	new_cylinder->color = cylinder->color;
	new_cylinder->material = cylinder->material;
	new_cylinder->bounding_box = cylinder->bounding_box;
	return (new_cylinder);
}

t_quad	*quad_copy(t_quad *quad)
{
	t_quad	*new_quad;

	new_quad = (t_quad *)ft_malloc(sizeof(t_quad));
	new_quad->q = quad->q;
	new_quad->u = quad->u;
	new_quad->v = quad->v;
	new_quad->normal = quad->normal;
	new_quad->w = quad->w;
	new_quad->d = quad->d;
	new_quad->material = quad->material;
	new_quad->bounding_box = quad->bounding_box;
	return (new_quad);
}

t_sphere	*sphere_copy(t_sphere *sphere)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *)ft_malloc(sizeof(t_sphere));
	new_sphere->center = sphere->center;
	new_sphere->radius = sphere->radius;
	new_sphere->is_moving = sphere->is_moving;
	new_sphere->velocity = sphere->velocity;
	new_sphere->material = sphere->material;
	new_sphere->bounding_box = sphere->bounding_box;
	return (new_sphere);
}

t_object	*object_copy(t_object **object, int idx)
{
	t_object	*new_object;
	t_object	*tmp;

	tmp = object[idx];
	if (tmp == NULL)
		return (NULL);
	new_object = (t_object *)ft_malloc(sizeof(t_object));
	new_object->type = tmp->type;
	new_object->bbox = tmp->bbox;
	if (tmp->type == SPHERE)
		new_object->element = sphere_copy((t_sphere *)tmp->element);
	else if (tmp->type == QUAD)
		new_object->element = quad_copy((t_quad *)tmp->element);
	else if (tmp->type == CYLINDER)
		new_object->element = cylinder_copy((t_cylinder *)tmp->element);
	else if (tmp->type == CONE)
		new_object->element = cone_copy((t_cone *)tmp->element);
	new_object->next = NULL;
	return (new_object);
}
