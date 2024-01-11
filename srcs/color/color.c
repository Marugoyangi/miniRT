/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:50:28 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 16:49:22 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	set_argb(int t, int r, int g, int b)
{
	return ((t << 24 | r << 16 | g << 8 | b));
}

unsigned int	set_color(t_color color)
{
	int		rgb[3];

	rgb[0] = (int)(255.999 * color.x);
	rgb[1] = (int)(255.999 * color.y);
	rgb[2] = (int)(255.999 * color.z);
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

