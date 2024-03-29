/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:25:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 15:13:56 by jeongbpa         ###   ########.fr       */
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

t_object	*object_set(t_object *object, int type, void *element)
{
	object->type = type;
	object->next = NULL;
	object->transform.is_transformed = 0;
	object->volume.density = 0;
	if (type == HYPERBOLOID)
	{
		object->element = (t_hyperboloid *)element;
		object->bbox = ((t_hyperboloid *)element)->bounding_box;
		object->center = ((t_hyperboloid *)element)->center;
	}
	else if (type == BOX)
	{
		object->element = (t_box *)element;
		object->bbox = ((t_box *)element)->bounding_box;
		object->center = vec_div_const(vec_add(((t_box *)element)->min, \
		((t_box *)element)->max), 2);
	}
	return (object);
}

t_object	*object(int type, void *element)
{
	t_object	*object;

	object = (t_object *)ft_malloc(sizeof(t_object));
	if (type == SPHERE)
	{
		object->element = (t_sphere *)element;
		object->bbox = ((t_sphere *)element)->bounding_box;
		object->center = ((t_sphere *)element)->center;
	}
	else if (type == QUAD)
	{
		object->element = (t_quad *)element;
		object->bbox = ((t_quad *)element)->bounding_box;
		object->center = vec_add(((t_quad *)element)->q,
				vec_div_const(((t_quad *)element)->u, 2));
		object->center = vec_add(object->center,
				vec_div_const(((t_quad *)element)->v, 2));
	}
	else if (type == CYLINDER)
	{
		object->element = (t_cylinder *)element;
		object->bbox = ((t_cylinder *)element)->bounding_box;
		object->center = ((t_cylinder *)element)->center;
	}
	return (object_set(object, type, element));
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
