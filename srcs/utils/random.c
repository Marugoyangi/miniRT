/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:55:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/16 12:11:20 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

unsigned int	xorshift32(unsigned int *seed)
{
	unsigned int	x;

	x = *seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*seed = x;
	return (x);
}

double	random_from_memory(unsigned int *seed)
{
	unsigned int		x;
	unsigned int		y;
	unsigned int		z;

	x = xorshift32(seed);
	y = xorshift32(seed);
	z = x * y;
	return ((double)z / 4294967295U);
}

double	random_double(double min, double max)
{
	static unsigned int		seed = 0x12345678;
	double					tmp;

	tmp = random_from_memory(&seed);
	return (min + (max - min) * tmp);
}
