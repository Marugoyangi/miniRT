/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:33:52 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 18:20:57 by jeongbpa         ###   ########.fr       */
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
		+ (y * minirt->img->size_line);
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

t_vec	lower_left_corner(t_minirt *minirt, t_ray ray)
{
	t_point	lower_left_corner;

	lower_left_corner = vec_sub(ray.origin, vec(minirt->viewpoint_width / 2, \
	minirt->viewpoint_height / 2, minirt->focal_length));
	return (lower_left_corner);
}


void	print_color(t_minirt *minirt)
{
	int				x;
	int				y;
	t_ray			ray;

	y = minirt->img_height;
	ray.origin = vec(0, 0, 0);
	while (y >= 0)
	{
		x = 0;
		while (x < minirt->img_width)
		{
			ray.direction = vec_add(lower_left_corner(minirt, ray), \
			vec((double)x / (minirt->img_width - 1) * minirt->viewpoint_width, \
			(double)y / (minirt->img_height - 1) * minirt->viewpoint_height, 0));
			ray.direction = vec_sub(ray.direction, ray.origin);
			set_pixel(minirt, x, y, set_color(ray_color(ray)));
			x++;
		}
		y--;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}
