/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:36:47 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/23 15:36:56 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	get_box(t_object *object)
{
	if (object->type == SPHERE)
		return (((t_sphere *)object->element)->bounding_box);
	else if (object->type == PLANE)
		return (((t_plane *)object->element)->bounding_box);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->element)->bounding_box);
	else
		return (((t_cone *)object->element)->bounding_box);
}

void	ft_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
