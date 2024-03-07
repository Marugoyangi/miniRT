/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:42:54 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:02:33 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_dot(t_vec vec1, t_vec vec2)
{
	double	dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

t_vec	vec_cross(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec);
}

double	vec_length(t_vec vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

t_vec	vec_unit(t_vec vec)
{
	t_vec	unit_vec;

	if (vec_length(vec) == 0)
		return (vec);
	unit_vec = vec_div_const(vec, vec_length(vec));
	return (unit_vec);
}

double	vec_length_squared(t_vec vec)
{
	double	len;

	len = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (len);
}
