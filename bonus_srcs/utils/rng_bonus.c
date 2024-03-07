/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:16:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	static unsigned int		seed = 0x2f6e2b1;
	float					tmp;

	tmp = random_from_memory(&seed);
	return ((double)(min + (max - min) * tmp));
}

int	random_int(int min, int max)
{
	return ((int)random_double(min, max + 1));
}
