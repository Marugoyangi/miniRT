/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_aabb_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:55:58 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_corners(t_aabb *bbox, t_vec *corners)
{
	corners[0] = vec(bbox->x.min, bbox->y.min, bbox->z.min);
	corners[1] = vec(bbox->x.min, bbox->y.min, bbox->z.max);
	corners[2] = vec(bbox->x.min, bbox->y.max, bbox->z.min);
	corners[3] = vec(bbox->x.min, bbox->y.max, bbox->z.max);
	corners[4] = vec(bbox->x.max, bbox->y.min, bbox->z.min);
	corners[5] = vec(bbox->x.max, bbox->y.min, bbox->z.max);
	corners[6] = vec(bbox->x.max, bbox->y.max, bbox->z.min);
	corners[7] = vec(bbox->x.max, bbox->y.max, bbox->z.max);
}

void	transform_aabb(t_aabb *bbox, t_matrix m)
{
	t_vec		corners[8];
	int			i;
	t_aabb		new_bbox;

	get_corners(bbox, corners);
	i = 0;
	while (i < 8)
	{
		corners[i] = matrix_apply(m, corners[i], 1);
		i++;
	}
	i = -1;
	new_bbox.x = interval(+INFINITY, -INFINITY);
	new_bbox.y = interval(+INFINITY, -INFINITY);
	new_bbox.z = interval(+INFINITY, -INFINITY);
	while (++i < 8)
	{
		new_bbox.x.min = fmin(new_bbox.x.min, corners[i].x);
		new_bbox.y.min = fmin(new_bbox.y.min, corners[i].y);
		new_bbox.z.min = fmin(new_bbox.z.min, corners[i].z);
		new_bbox.x.max = fmax(new_bbox.x.max, corners[i].x);
		new_bbox.y.max = fmax(new_bbox.y.max, corners[i].y);
		new_bbox.z.max = fmax(new_bbox.z.max, corners[i].z);
	}
	*bbox = new_bbox;
}
