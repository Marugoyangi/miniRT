/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:21:30 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/27 02:32:46 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	permute(int *perm, int n)
{
	int		i;
	int		tmp;
	int		random;

	i = n - 1;
	while (i-- > 0)
	{
		random = random_int(0, i);
		tmp = perm[i];
		perm[i] = perm[random];
		perm[random] = tmp;
	}
}

void	generate_perm(int *perm)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		perm[i] = i;
		i++;
	}
	permute(perm, 256);
}

void	perlin_generate(t_perlin *perlin, double n)
{
	int		i;

	i = 0;
	while (i < 256)
	{
		perlin->random_vec[i] = vec_unit(random_vec(-1.0, 1.0));
		i++;
	}
	perlin->scale = n;
	generate_perm(perlin->perm_x);
	generate_perm(perlin->perm_y);
	generate_perm(perlin->perm_z);
}

double	trilinear_interp(t_vec c[2][2][2], double u, double v, double w)
{
	double		accum;
	double		i[3];
	int			j[3];

	accum = 0.0;
	i[0] = u * u * (3 - 2 * u);
	i[1] = v * v * (3 - 2 * v);
	i[2] = w * w * (3 - 2 * w);
	j[0] = -1;
	while (++j[0] < 2)
	{
		j[1] = -1;
		while (++j[1] < 2)
		{
			j[2] = -1;
			while (++j[2] < 2)
				accum += (j[0] * i[0] + (1 - j[0]) * (1 - i[0])) * \
				(j[1] * i[1] + (1 - j[1]) * (1 - i[1])) * \
				(j[2] * i[2] + (1 - j[2]) * (1 - i[2])) * \
				vec_dot(c[j[0]][j[1]][j[2]], \
				vec(u - j[0], v - j[1], w - j[2]));
		}
	}
	return (accum);
}

double	noise(t_perlin *perlin, t_point p)
{
	double	i[3];
	int		j[3];
	t_vec	c[2][2][2];

	i[0] = p.x - floor(p.x);
	i[1] = p.y - floor(p.y);
	i[2] = p.z - floor(p.z);
	j[0] = -1;
	while (++j[0] < 2)
	{
		j[1] = -1;
		while (++j[1] < 2)
		{
			j[2] = -1;
			while (++j[2] < 2)
			{
				c[j[0]][j[1]][j[2]] = perlin->random_vec[\
				perlin->perm_x[((int)(floor(p.x)) + j[0]) & 255] ^ \
				perlin->perm_y[((int)(floor(p.y)) + j[1]) & 255] ^ \
				perlin->perm_z[((int)(floor(p.z)) + j[2]) & 255]];
			}
		}
	}
	return (trilinear_interp(c, i[0], i[1], i[2]));
}

double	noise_turb (t_perlin *perlin, t_point p)
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
