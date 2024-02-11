/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/12 05:43:44 by jeongbpa         ###   ########.fr       */
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
	int				i;
	t_ray			tmp;

	i = 0;
	while (i < minirt->camera.samples_per_pixel)
	{
		tmp = get_ray(minirt, \
		((x + random_double(-0.5, 0.5)) / (minirt->img_width - 1)), \
		((y + random_double(-0.5, 0.5)) / (minirt->img_height - 1)));
		*pixel_color = vec_add(*pixel_color, ray_color(minirt->bvh, &tmp, \
		minirt->camera.max_depth, minirt));
		i++;
	}
}

#include <pthread.h>
#define THREAD_NUM 8
void multi_thread(t_minirt *minirt)
{
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		minirt->thread_data[i].id = i;
		minirt->thread_data[i].minirt = minirt;
		pthread_create(minirt->thread + i, NULL, (void *)print_color, \
		&minirt->thread_data[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_join(*(minirt->thread + i), NULL);
		i++;
	}
}

void	print_color(void *thread)
{
	int				x;
	int				y;
	t_color			pixel_color;
	t_thread		*t;
	int				i;

	t = (t_thread *)thread;
	y = t->minirt->img_height / THREAD_NUM * t->id;
	while (y < t->minirt->img_height / THREAD_NUM * (t->id + 1))
	{
		x = 0;
		if (t->id == 0 && t->minirt->camera.k == 1)
		{
			printf("\rRendering %.2f%%", (double)(y + 1) / \
			(t->minirt->img_height / THREAD_NUM) * 100);
			fflush(stdout);
		}
		while (x < t->minirt->img_width)
		{
			pixel_color = color(0, 0, 0);
			anti_aliasing(t->minirt, x, y, &pixel_color);
			i = 0;
			while (i < t->minirt->camera.k && x + i < t->minirt->img_width)
			{
				set_pixel(t->minirt, x + i, y, set_color(pixel_color, \
				t->minirt->camera.samples_per_pixel));
				i++;
			}
			x += t->minirt->camera.k;
		}
		y += 1;
	}
	pthread_exit(0);
}
