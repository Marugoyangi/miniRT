/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 07:52:30 by jeongbpa         ###   ########.fr       */
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
		+ ((minirt->img_height - 1 - y) * minirt->img->size_line);
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
	int		i;
	t_ray	tmp;

	i = 0;
	while (i < minirt->camera.samples_per_pixel)
	{
		tmp = get_ray(minirt->camera, \
		((x + random_double(0, 1)) / (minirt->img_width - 1)), \
		((y + random_double(0, 1)) / (minirt->img_height - 1)));
		*pixel_color = vec_add(*pixel_color, ray_color(&tmp, minirt->objects, \
		minirt->camera.max_depth));
		i++;
	}
}

void	print_color(t_minirt *minirt)
{
	int				x;
	int				y;
	t_color			pixel_color;

	y = 0;
	while (y < minirt->img_height)
	{
		x = 0;
		while (x < minirt->img_width)
		{
			pixel_color = color(0, 0, 0);
			anti_aliasing(minirt, x, y, &pixel_color);
			set_pixel(minirt, x, y, set_color(pixel_color, \
			minirt->camera.samples_per_pixel));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}
