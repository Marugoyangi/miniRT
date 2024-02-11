/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:55:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/08 03:27:51 by jeongbpa         ###   ########.fr       */
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

unsigned int	xorshift32(unsigned int seed)
{
	seed = (seed ^ 61) ^ (seed >> 16);
	seed *= 9;
	seed = seed ^ (seed >> 4);
	seed *= 0x27d4eb2d;
	seed = seed ^ (seed >> 15);
	return (seed);
}

float	random_from_memory(unsigned int *seed)
{
	*seed = xorshift32(*seed);
	return ((float)*seed / (float)4294967296);
}

double	random_double(double min, double max)
{
	static unsigned int		seed = 0x12345678;
	float					tmp;

	tmp = random_from_memory(&seed);
	return ((double)(min + (max - min) * tmp));
}

int	random_int(int min, int max)
{
	return ((int)random_double(min, max + 1));
}
