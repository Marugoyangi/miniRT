/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:50:28 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/17 06:39:53 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	set_argb(int t, int r, int g, int b)
{
	return ((t << 24 | r << 16 | g << 8 | b));
}

unsigned int	set_color(t_color c, int samples_per_pixel)
{
	int		rgb[3];
	double	scale;
	t_color	tmp;

	scale = 1.0 / samples_per_pixel;
	tmp = vec_mul_const(c, scale);
	tmp = color(sqrt(tmp.x), sqrt(tmp.y), sqrt(tmp.z));
	rgb[0] = (int)(256 * random_clamp(tmp.x, 0.0, 0.999));
	rgb[1] = (int)(256 * random_clamp(tmp.y, 0.0, 0.999));
	rgb[2] = (int)(256 * random_clamp(tmp.z, 0.0, 0.999));
	return (set_argb(0, rgb[0], rgb[1], rgb[2]));
}

t_color	color(double r, double g, double b)
{
	t_color	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}
