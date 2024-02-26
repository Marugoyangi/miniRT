/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:36:47 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 12:35:19 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	get_box(t_object *object)
{
	if (object->type == SPHERE)
		return (((t_sphere *)object->element)->bounding_box);
	else if (object->type == QUAD)
		return (((t_quad *)object->element)->bounding_box);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->element)->bounding_box);
	else
		return (((t_hypoboloid *)object->element)->bounding_box);
}

void	ft_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
