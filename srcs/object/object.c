/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:25:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 02:50:09 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_object(t_object **objects, t_ray *ray)
{
	t_object		*tmp;
	t_hit_record	tmp_rec;
	double			closest;

	ray->record.hit_anything = 0;
	tmp = *objects;
	closest = ray->t_max;
	while (tmp)
	{
		if ((tmp)->type == SPHERE && hit_sphere(ray, \
		(t_sphere *)tmp->element, closest, &tmp_rec))
		{
			ray->record.hit_anything = 1;
			ray->record = tmp_rec;
			closest = tmp_rec.t;
		}
		tmp = tmp->next;
	}
	return (ray->record.hit_anything);
}

t_object	*object(int type, void *element)
{
	t_object	*object;

	object = (t_object *)ft_malloc(sizeof(t_object));
	object->type = type;
	if (type == SPHERE)
		object->element = (t_sphere *)element;
	else if (type == PLANE)
		object->element = (t_plane *)element;
	else if (type == CYLINDER)
		object->element = (t_cylinder *)element;
	else if (type == CONE)
		object->element = (t_cone *)element;
	object->next = NULL;
	return (object);
}

void	object_add_back(t_object **objects, t_object *new)
{
	t_object	*last;

	if (!*objects)
	{
		*objects = new;
		return ;
	}
	last = *objects;
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
