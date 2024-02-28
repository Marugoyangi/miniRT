/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:18:00 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/29 06:33:34 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera(int key, t_minirt *minirt)
{
	if (key == ARROW_U)
	{
		minirt->camera.origin = vec_add(minirt->camera.origin, \
		minirt->camera.basis.v);
	}
	else if (key == ARROW_D)
	{
		minirt->camera.origin = vec_sub(minirt->camera.origin, \
		minirt->camera.basis.v);
	}
	else if (key == ARROW_L)
	{
		minirt->camera.origin = vec_sub(minirt->camera.origin, \
		minirt->camera.basis.u);
	}
	else if (key == ARROW_R)
	{
		minirt->camera.origin = vec_add(minirt->camera.origin, \
		minirt->camera.basis.u);
	}
	set_camera_basis(minirt);
	multi_thread(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}

void	zoom_camera(int key, t_minirt *minirt)
{
	if (key == KW)
	{
		minirt->camera.origin = vec_add(minirt->camera.origin, \
		minirt->camera.basis.v);
		minirt->camera.look_at = vec_add(minirt->camera.look_at, \
		minirt->camera.basis.v);
	}
	else if (key == KS)
	{
		minirt->camera.origin = vec_sub(minirt->camera.origin, \
		minirt->camera.basis.v);
		minirt->camera.look_at = vec_sub(minirt->camera.look_at, \
		minirt->camera.basis.v);
	}
	else if (key == KA)
	{
		minirt->camera.origin = vec_sub(minirt->camera.origin, \
		minirt->camera.basis.u);
		minirt->camera.look_at = vec_sub(minirt->camera.look_at, \
		minirt->camera.basis.u);
	}
	else if (key == KD)
	{
		minirt->camera.origin = vec_add(minirt->camera.origin, \
		minirt->camera.basis.u);
		minirt->camera.look_at = vec_add(minirt->camera.look_at, \
		minirt->camera.basis.u);
	}
	set_camera_basis(minirt);
	multi_thread(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}

void	move_up_down(int key, t_minirt *minirt)
{
	if (key == PGDN)
	{
		minirt->camera.origin = vec_add(minirt->camera.origin, \
		minirt->camera.basis.w);
		minirt->camera.look_at = vec_add(minirt->camera.look_at, \
		minirt->camera.basis.w);
	}
	else if (key == PGUP)
	{
		minirt->camera.origin = vec_sub(minirt->camera.origin, \
		minirt->camera.basis.w);
		minirt->camera.look_at = vec_sub(minirt->camera.look_at, \
		minirt->camera.basis.w);
	}
	set_camera_basis(minirt);
	multi_thread(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}

int	key_input(int key, t_minirt *minirt)
{
	if (key == ESC)
		free_all(minirt);
	else if (minirt->camera.k == 1 && key == SPACE)
		minirt->camera.k = 10;
	else if (minirt->camera.k == 10 && key == SPACE)
	{
		minirt->camera.k = 1;
		multi_thread(minirt);
		mlx_put_image_to_window(minirt->mlx, minirt->win, \
		minirt->img->img_ptr, 0, 0);
	}
	else if (minirt->camera.k == 10)
	{
		if (key == ARROW_U || key == ARROW_D || key == ARROW_L \
		|| key == ARROW_R)
			move_camera(key, minirt);
		if (key == KW || key == KS || key == KA || key == KD)
			zoom_camera(key, minirt);
		if (key == PGUP || key == PGDN)
			move_up_down(key, minirt);
	}
	return (0);
}
