/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 04:00:40 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	hit_box(t_object *object, t_ray *ray, t_interval \
		*closest, t_hit_record *rec)
{
	int				ret;
	t_object		*tmp;
	t_box			*box;

	box = (t_box *)object->element;
	ret = 0;
	tmp = box->list;
	while (tmp)
	{
		if (hit_quad(ray, (t_quad *)tmp->element, *closest, rec))
		{
			if (rec->t < closest->max)
				closest->max = rec->t;
			rec->material = box->material;
			ret = 1;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_object	*instance_add_back(t_object *object, t_object *new)
{
	t_object	*tmp;

	if (object == NULL)
		return (new);
	tmp = object;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (object);
}

void	box_set(t_vec ab[2], t_vec (*delta)[3], t_material material, t_box *ret)
{
	ret->min = vec(fmin(ab[0].x, ab[1].x), fmin(ab[0].y, ab[1].y), \
	fmin(ab[0].z, ab[1].z));
	ret->max = vec(fmax(ab[0].x, ab[1].x), fmax(ab[0].y, ab[1].y), \
	fmax(ab[0].z, ab[1].z));
	ret->material = material;
	(*delta)[0] = vec(ret->max.x - ret->min.x, 0, 0);
	(*delta)[1] = vec(0, ret->max.y - ret->min.y, 0);
	(*delta)[2] = vec(0, 0, ret->max.z - ret->min.z);
}

t_box	*box(t_vec a, t_vec b, t_material material)
{
	t_box		*ret;
	t_object	*tmp;
	t_vec		delta[3];
	t_vec		ab[2];

	ret = (t_box *)ft_malloc(sizeof(t_box));
	ab[0] = a;
	ab[1] = b;
	box_set(ab, &delta, material, ret);
	tmp = NULL;
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->min.x, \
	ret->min.y, ret->max.z), delta[0], delta[1], material)));
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->max.x, \
	ret->min.y, ret->max.z), vec_mul_const(delta[2], -1), delta[1], material)));
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->max.x, \
	ret->min.y, ret->min.z), vec_mul_const(delta[0], -1), delta[1], material)));
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->min.x, \
	ret->min.y, ret->min.z), delta[2], delta[1], material)));
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->min.x, \
	ret->max.y, ret->max.z), delta[0], vec_mul_const(delta[2], -1), material)));
	tmp = instance_add_back(tmp, object(QUAD, quad(vec(ret->min.x, \
	ret->min.y, ret->min.z), delta[0], delta[2], material)));
	ret->list = tmp;
	ret->bounding_box = aabb(ret->min, ret->max);
	return (ret);
}
