/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:25:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 07:23:40 by jeongbpa         ###   ########.fr       */
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
	if ((tmp)->type == SPHERE && hit_sphere(ray, \
		(t_sphere *)tmp->element, closest->max, &tmp_rec))
	{
		tmp_rec.img_height = rec->img_height;
		tmp_rec.img_width = rec->img_width;
		*rec = tmp_rec;
		rec->hit_anything = 1;
		rec->material = ((t_sphere *)tmp->element)->material;
		closest->max = tmp_rec.t;
	}
	else if ((tmp)->type == QUAD && hit_quad(ray, \
		(t_quad *)tmp->element, closest->max, &tmp_rec))
	{
		tmp_rec.img_height = rec->img_height;
		tmp_rec.img_width = rec->img_width;
		*rec = tmp_rec;
		rec->hit_anything = 1;
		rec->material = ((t_quad *)tmp->element)->material;
		closest->max = tmp_rec.t;
	}
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
	object->next = NULL;
	return (object);
}

void	object_add_back(t_minirt *minirt, t_object *new)
{
	t_object	*last;

	if (new->type == SPHERE)
		minirt->box = aabb_b(minirt->box, (((t_sphere *)new->element)->bounding_box));
	else if (new->type == QUAD)
		minirt->box = aabb_b(minirt->box, (((t_quad *)new->element)->bounding_box));
	else if (new->type == CYLINDER)
		minirt->box = aabb_b(minirt->box, (((t_cylinder *)new->element)->bounding_box));
	else if (new->type == CONE)
		minirt->box = aabb_b(minirt->box, (((t_cone *)new->element)->bounding_box));
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
