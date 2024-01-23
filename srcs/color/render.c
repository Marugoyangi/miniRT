/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 02:36:03 by jeongbpa         ###   ########.fr       */
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
		+ ((minirt->img_height - 3 - y) * minirt->img->size_line);
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
		minirt->camera.max_depth));
		i++;
	}
}

#include <pthread.h>
#define THREAD_NUM 7
void multi_thread(t_minirt *minirt)
{
	pthread_t	t_id[THREAD_NUM];
	int			i;

	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_create(&t_id[i], NULL, (void *)print_color, minirt);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		pthread_join(t_id[i], NULL);
		i++;
	}
}

void	print_color(t_minirt *minirt)
{
	int				x;
	int				y;
	t_color			pixel_color;
	int				idx;

	idx = minirt->thread_num++;
	y = minirt->img_height / THREAD_NUM * (idx);
	while (y < minirt->img_height / THREAD_NUM * (idx + 1))
	{
		x = 0;
		if (idx == 0)
		{
			fflush(stdout);
			printf("\rRendering %d / %d ", y + 1, minirt->img_height / THREAD_NUM );
		}
		while (x < minirt->img_width)
		{
			pixel_color = color(0, 0, 0);
			anti_aliasing(minirt, x, y, &pixel_color);
			set_pixel(minirt, x, y, set_color(pixel_color, \
			minirt->camera.samples_per_pixel));
			x += minirt->camera.k;
		}
		y += minirt->camera.k;
	}
}
