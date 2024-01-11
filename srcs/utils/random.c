/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:55:33 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 05:21:03 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	random_from_memory(void *ptr)
{
	unsigned long	address;
	unsigned int	seed;

	address = (unsigned long)ptr;
	seed = (unsigned int)address;
	return ((double)xorshift32(&seed) / 4294967295U);
}

double	random_double(void)
{
	double	rand_num;

	rand_num = random_from_memory(&rand_num);
	return (rand_num);
}
