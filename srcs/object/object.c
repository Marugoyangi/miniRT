/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:25:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/28 17:41:16 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_object(t_object *object, t_ray *ray, \
			t_interval *closest, t_hit_record *rec)
{
	t_hit_record	tmp_rec;

	tmp_rec.img_height = rec->img_height;
	tmp_rec.img_width = rec->img_width;
	if (object->type == SPHERE && hit_sphere(ray, \
		(t_sphere *)object->element, *closest, &tmp_rec))
		tmp_rec.material = ((t_sphere *)object->element)->material;
	else if (object->type == QUAD && hit_quad(ray, \
		(t_quad *)object->element, *closest, &tmp_rec))
		tmp_rec.material = ((t_quad *)object->element)->material;
	else if (object->type == BOX && hit_box(object, ray, closest, &tmp_rec))
		tmp_rec.material = ((t_box *)object->element)->material;
	else if (object->type == CYLINDER && hit_cylinder(ray, \
		(t_cylinder *)object->element, *closest, &tmp_rec))
		tmp_rec.material = ((t_cylinder *)object->element)->material;
	else if (object->type == HYPERBOLOID && hit_hyperboloid(ray, \
		(t_hyperboloid *)object->element, *closest, &tmp_rec))
		tmp_rec.material = ((t_hyperboloid *)object->element)->material;
	else
		return (0);
	*rec = tmp_rec;
	rec->hit_anything = 1;
	closest->max = rec->t;
	rec->object = object;
	return (rec->hit_anything);
}

void	object_set(t_object *object, int type, void *element)
{
	if (type == HYPERBOLOID)
	{
		object->element = (t_hyperboloid *)element;
		object->bbox = ((t_hyperboloid *)element)->bounding_box;
	}
	else if (type == BOX)
	{
		object->element = (t_box *)element;
		object->bbox = ((t_box *)element)->bounding_box;
	}
}

t_object	*object(int type, void *element)
{
	t_object	*object;

	object = (t_object *)ft_malloc(sizeof(t_object));
	object->type = type;
	object->next = NULL;
	object->transform.is_transformed = 0;
	object->volume.density = 0;
	if (type == SPHERE)
	{
		object->element = (t_sphere *)element;
		object->bbox = ((t_sphere *)element)->bounding_box;
	}
	else if (type == QUAD)
	{
		object->element = (t_quad *)element;
		object->bbox = ((t_quad *)element)->bounding_box;
	}
	else if (type == CYLINDER)
	{
		object->element = (t_cylinder *)element;
		object->bbox = ((t_cylinder *)element)->bounding_box;
	}
	else
		object_set(object, type, element);
	return (object);
}

void	light_add_back(t_minirt *minirt, t_object *new)
{
	t_object	*last;

	last = minirt->light;
	if (!last)
	{
		minirt->light = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

void	object_add_back(t_minirt *minirt, t_object *new)
{
	t_object	*last;

	last = minirt->object;
	if (!last)
	{
		minirt->object = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}
