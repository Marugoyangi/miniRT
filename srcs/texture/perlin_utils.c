/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:33:42 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 20:33:47 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	noise_turb(t_perlin *perlin, t_point p)
{
	double	accum;
	t_vec	tmp;
	double	weight;
	int		i;

	i = 0;
	tmp = p;
	accum = 0.0;
	weight = 1.0;
	while (i < 7)
	{
		accum += weight * noise(perlin, tmp);
		weight *= 0.5;
		tmp = vec_mul_const(tmp, 2);
		i++;
	}
	return (fabs(accum));
}
