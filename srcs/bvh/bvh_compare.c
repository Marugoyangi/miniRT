/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:37:57 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/21 17:44:43 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	box_compare_x(t_object *a, t_object *b)
{
	t_aabb	box_a;
	t_aabb	box_b;

	box_a = a->bbox;
	box_b = b->bbox;
	if (box_a.x.min - box_b.x.min < 0.0)
		return (1);
	return (0);
}

int	box_compare_y(t_object *a, t_object *b)
{
	t_aabb	box_a;
	t_aabb	box_b;

	box_a = a->bbox;
	box_b = b->bbox;
	if (box_a.y.min - box_b.y.min < 0.0)
		return (1);
	return (0);
}

int	box_compare_z(t_object *a, t_object *b)
{
	t_aabb	box_a;
	t_aabb	box_b;

	box_a = a->bbox;
	box_b = b->bbox;
	if (box_a.z.min - box_b.z.min < 0.0)
		return (1);
	return (0);
}
