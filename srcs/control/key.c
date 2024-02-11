/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:18:00 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/12 05:59:34 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera(int key, t_minirt *minirt)
{
	if (key == ARROW_U)
		minirt->camera.origin.y += 10;
	else if (key == ARROW_D)
		minirt->camera.origin.y -= 10;
	else if (key == ARROW_L)
		minirt->camera.origin.x -= 10;
	else if (key == ARROW_R)
		minirt->camera.origin.x += 10;
	set_camera_basis(minirt);
	multi_thread(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}	

int	key_input(int key, t_minirt *minirt)
{
	if (key == ESC)
		ft_close(minirt, NULL, 0);
	else if (minirt->camera.k == 1 && key == SPACE)
		minirt->camera.k = 10;
	else if (minirt->camera.k == 10 && key == SPACE)
	{
		minirt->camera.k = 1;
		multi_thread(minirt);
		mlx_put_image_to_window(minirt->mlx, minirt->win, \
		minirt->img->img_ptr, 0, 0);
	}
	else if (key == PLUS)
		minirt->camera.samples_per_pixel += 10;
	else if (key == MINUS)
	{
		minirt->camera.samples_per_pixel -= 10;
		if (minirt->camera.samples_per_pixel < 1)
			minirt->camera.samples_per_pixel = 1;
	}
	else if (minirt->camera.k == 10)
	{
		if (key == ARROW_U || key == ARROW_D || key == ARROW_L \
		|| key == ARROW_R)
			move_camera(key, minirt);
	}
	return (0);
}
