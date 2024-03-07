/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:04:31 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_bvh	*create_inner_node(t_bvh *left, t_bvh *right)
{
	t_bvh	*node;

	node = (t_bvh *)ft_malloc(sizeof(t_bvh));
	node->left = left;
	node->right = right;
	node->object = NULL;
	node->bbox = aabb_b(left->bbox, right->bbox);
	node->is_leaf = 0;
	return (node);
}

t_bvh	*create_leaf(t_object *object)
{
	t_bvh	*leaf;

	leaf = (t_bvh *)ft_malloc(sizeof(t_bvh));
	leaf->object = object;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->bbox = object->bbox;
	leaf->is_leaf = 1;
	return (leaf);
}

t_bvh	*bvh_node(t_object **objects, int start, int end)
{
	int			axis;
	int			(*comparator)(t_object *, t_object *);
	t_object	**tmp;
	t_bvh		*ret[2];

	axis = (int)random_double(0, 2);
	tmp = object_vector(objects, start, end);
	if (axis == 0)
		comparator = &box_compare_x;
	else if (axis == 1)
		comparator = &box_compare_y;
	else
		comparator = &box_compare_z;
	if (end - start == 1)
	{
		free(tmp);
		return (create_leaf(tmp[0]));
	}
	sort_bvh(tmp, start, end, comparator);
	ret[0] = bvh_node(tmp, 0, (end - start) / 2);
	ret[1] = bvh_node(tmp, (end - start) / 2, end - start);
	free(tmp);
	return (create_inner_node(ret[0], ret[1]));
}

int	bvh_hit(t_bvh *node, t_ray *ray, t_interval *closest, t_hit_record *rec)
{
	int	left_hit;
	int	right_hit;

	if (!node)
		return (0);
	if (!aabb_hit(node->bbox, ray, ray->t))
		return (0);
	if (node->is_leaf)
	{
		if (node->object->volume.density)
			return (hit_volume(node->object, ray, closest, rec));
		if (node->object->transform.is_transformed)
			return (hit_transformed(node->object, ray, closest, rec));
		return (hit_object(node->object, ray, closest, rec));
	}
	left_hit = bvh_hit(node->left, ray, closest, rec);
	if (left_hit)
	{
		ray->t.max = rec->t;
		right_hit = bvh_hit(node->right, ray, closest, rec);
	}
	else
		right_hit = bvh_hit(node->right, ray, closest, rec);
	return (left_hit || right_hit);
}
