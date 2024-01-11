/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:34:39 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 16:48:10 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec	vec_add(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.x + vec2.x;
	vec.y = vec1.y + vec2.y;
	vec.z = vec1.z + vec2.z;
	return (vec);
}

t_vec	vec_sub(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.x - vec2.x;
	vec.y = vec1.y - vec2.y;
	vec.z = vec1.z - vec2.z;
	return (vec);
}

t_vec	vec_mul(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.x * vec2.x;
	vec.y = vec1.y * vec2.y;
	vec.z = vec1.z * vec2.z;
	return (vec);
}

t_vec	vec_div(t_vec vec1, t_vec vec2)
{
	t_vec	vec;

	vec.x = vec1.x / vec2.x;
	vec.y = vec1.y / vec2.y;
	vec.z = vec1.z / vec2.z;
	return (vec);
}
