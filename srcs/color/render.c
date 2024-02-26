/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/27 02:31:56 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_pixel(t_minirt *minirt, int x, int y, unsigned int color)
{
	int		i;
	char	c_color[4];

	c_color[0] = color >> 24 & 0xFF;
	c_color[1] = color >> 16 & 0xFF;
	c_color[2] = color >> 8 & 0xFF;
	c_color[3] = color >> 0 & 0xFF;
	i = (x * minirt->img->bits_per_pixel / 8)
		+ ((minirt->img_height - 2 - y) * minirt->img->size_line);
	if (minirt->img->endian == 0)
	{
		minirt->img->addr[i] = c_color[3];
		minirt->img->addr[++i] = c_color[2];
		minirt->img->addr[++i] = c_color[1];
		minirt->img->addr[++i] = c_color[0];
	}
	else
	{
		minirt->img->addr[i] = c_color[0];
		minirt->img->addr[++i] = c_color[1];
		minirt->img->addr[++i] = c_color[2];
		minirt->img->addr[++i] = c_color[3];
	}
}

void	anti_aliasing(t_minirt *minirt, int x, int y, t_color *pixel_color)
{
	int				i[2];
	t_ray			tmp;
	int				sqrt_spp;

	i[0] = 0;
	sqrt_spp = sqrt(minirt->camera.samples_per_pixel);
	while (i[0] < sqrt_spp)
	{
		i[1] = 0;
		while (i[1] < sqrt_spp)
		{
			tmp = get_ray(minirt, \
			(double)(x + (i[1] + random_double(-0.5, 0.5)) / sqrt_spp) / \
			minirt->img_width, \
			(double)(y + (i[0] + random_double(-0.5, 0.5)) / sqrt_spp) / \
			minirt->img_height);
			*pixel_color = vec_add(*pixel_color, ray_color(minirt->bvh, &tmp, \
			minirt->camera.max_depth, minirt));
			i[1]++;
		}
		i[0]++;
	}
}

void	multi_thread(t_minirt *minirt)
{
	int			i;

	i = 0;
	while (i < THREAD_MAX)
	{
		minirt->thread_data[i].id = i;
		minirt->thread_data[i].minirt = minirt;
		pthread_create(minirt->thread + i, NULL, (void *)print_color, \
		&minirt->thread_data[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_MAX)
	{
		pthread_join(*(minirt->thread + i), NULL);
		i++;
	}
}

void	print_color(void *thread)
{
	int				xyi[3];
	t_color			pixel_color;
	t_thread		*t;

	t = (t_thread *)thread;
	xyi[1] = t->minirt->img_height / THREAD_MAX * t->id;
	while (xyi[1] < t->minirt->img_height / THREAD_MAX * (t->id + 1))
	{
		xyi[0] = 0;
		while (xyi[0] < t->minirt->img_width)
		{
			pixel_color = color(0, 0, 0);
			anti_aliasing(t->minirt, xyi[0], xyi[1], &pixel_color);
			xyi[2] = -1;
			while (++xyi[2] < t->minirt->camera.k && xyi[0] + xyi[2] \
			< t->minirt->img_width)
			{
				set_pixel(t->minirt, xyi[0] + xyi[2], xyi[1], \
				set_color(pixel_color, t->minirt->camera.samples_per_pixel));
			}
			xyi[0] += t->minirt->camera.k;
		}
		xyi[1] += 1;
	}
	pthread_exit(0);
}
