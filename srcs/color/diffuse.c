/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 06:24:29 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 07:32:53 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	random_in_sphere(void)
{
	t_vec	p;

	while (1)
	{
		p = random_vec(-1, 1);
		if (vec_length_squared(p) < 1.0)
			return (p);
	}
}

t_vec	random_on_hemisphere(t_vec normal)
{
	t_vec	in_unit_sphere;
	t_vec	p;

	in_unit_sphere = random_in_sphere();
	in_unit_sphere = vec_unit(in_unit_sphere);
	if (vec_dot(in_unit_sphere, normal) > 0.0)
		p = in_unit_sphere;
	else
		p = vec_mul_const(in_unit_sphere, -1);
	return (p);
}
