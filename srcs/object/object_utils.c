/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:00:24 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/23 18:00:30 by jeongbpa         ###   ########.fr       */
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

t_plane	*plane_copy(t_plane *plane)
{
	t_plane	*new_plane;

	new_plane = (t_plane *)ft_malloc(sizeof(t_plane));
	new_plane->center = plane->center;
	new_plane->normal = plane->normal;
	new_plane->color = plane->color;
	new_plane->material = plane->material;
	new_plane->bounding_box = plane->bounding_box;
	return (new_plane);
}

t_sphere	*sphere_copy(t_sphere *sphere)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *)ft_malloc(sizeof(t_sphere));
	new_sphere->center = sphere->center;
	new_sphere->radius = sphere->radius;
	new_sphere->color = sphere->color;
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
	else if (tmp->type == PLANE)
		new_object->element = plane_copy((t_plane *)tmp->element);
	else if (tmp->type == CYLINDER)
		new_object->element = cylinder_copy((t_cylinder *)tmp->element);
	else if (tmp->type == CONE)
		new_object->element = cone_copy((t_cone *)tmp->element);
	new_object->next = NULL;
	return (new_object);
}
