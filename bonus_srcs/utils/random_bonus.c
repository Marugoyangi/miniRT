/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:55:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	random_to_sphere(double radius, double distance_squared)
{
	double	r1;
	double	r2;
	double	z;
	double	phi;

	r1 = random_double(0, 1);
	r2 = random_double(0, 1);
	z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);
	phi = 2 * PI * r1;
	return (vec(cos(phi) * sqrt(1 - z * z), sin(phi) * sqrt(1 - z * z), z));
}

t_vec	random_cosine_direction(void)
{
	double	r1;
	double	r2;
	double	xyz[3];
	double	pi;

	r1 = random_double(0, 1);
	r2 = random_double(0, 1);
	pi = 2 * M_PI * r1;
	xyz[0] = cos(pi) * sqrt(r2);
	xyz[1] = sin(pi) * sqrt(r2);
	xyz[2] = sqrt(1 - r2);
	return (vec(xyz[0], xyz[1], xyz[2]));
}

t_vec	random_vec(double min, double max)
{
	t_vec	vec;

	vec.x = random_double(min, max);
	vec.y = random_double(min, max);
	vec.z = random_double(min, max);
	return (vec);
}

double	random_clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
