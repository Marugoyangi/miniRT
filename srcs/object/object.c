/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:25:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/08 01:35:59 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_object(t_object *object, t_ray *ray, t_interval *closest, t_hit_record *rec)
{
	t_object		*tmp;
	t_hit_record	tmp_rec;

	tmp = object;
	if (tmp == NULL)
		return (0);
	tmp_rec.img_height = rec->img_height;
	tmp_rec.img_width = rec->img_width;
	if (ray->t.max < closest->min)
		return (0);
	if (tmp->type == SPHERE && hit_sphere(ray, \
		(t_sphere *)tmp->element, closest->max, &tmp_rec))
	{
		*rec = tmp_rec;
		rec->hit_anything = 1;
		rec->material = ((t_sphere *)tmp->element)->material;
		closest->max = tmp_rec.t;
	}
	else if (tmp->type == QUAD && hit_quad(ray, \
		(t_quad *)tmp->element, closest->max, &tmp_rec))
	{
		*rec = tmp_rec;
		rec->hit_anything = 1;
		rec->material = ((t_quad *)tmp->element)->material;
		closest->max = tmp_rec.t;
	}
	else if (tmp->type == BOX && hit_box(tmp, ray, closest, &tmp_rec))
	{
		*rec = tmp_rec;
		rec->hit_anything = 1;
		rec->material = ((t_box *)tmp->element)->material;
		closest->max = tmp_rec.t;
	}
	else
		return (0);
	return (rec->hit_anything);
}

t_object	*object(int type, void *element)
{
	t_object	*object;

	object = (t_object *)ft_malloc(sizeof(t_object));
	object->type = type;
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
	else if (type == CONE)
	{
		object->element = (t_cone *)element;
		object->bbox = ((t_cone *)element)->bounding_box;
	}
	else if (type == BOX)
	{
		object->element = (t_box *)element;
		object->bbox = ((t_box *)element)->bounding_box;
	}
	object->next = NULL;
	object->transform.is_transformed = 0;
	object->volume.density = 0;
	return (object);
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

void	object_clear(t_object **objects)
{
	t_object	*tmp;

	while (*objects)
	{
		tmp = (*objects)->next;
		free(*objects);
		*objects = tmp;
	}
}
