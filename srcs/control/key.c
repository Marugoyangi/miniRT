/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:18:00 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 16:52:34 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	re_render(t_minirt *minirt)
{
	printf("minirt->camera.origin: %f, %f, %f\n", minirt->camera.origin.x, minirt->camera.origin.y, minirt->camera.origin.z);
	printf("minirt->camera.look_at: %f, %f, %f\n", minirt->camera.look_at.x, minirt->camera.look_at.y, minirt->camera.look_at.z);
	printf("minirt->camera.basis.w: %f, %f, %f\n", minirt->camera.basis.w.x, minirt->camera.basis.w.y, minirt->camera.basis.w.z);
	printf("minirt->camera.basis.u: %f, %f, %f\n", minirt->camera.basis.u.x, minirt->camera.basis.u.y, minirt->camera.basis.u.z);
	printf("minirt->camera.basis.v: %f, %f, %f\n", minirt->camera.basis.v.x, minirt->camera.basis.v.y, minirt->camera.basis.v.z);
	set_camera_basis(minirt);
	multi_thread(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, \
	minirt->img->img_ptr, 0, 0);
}

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
	re_render(minirt);
}

void	zoom_camera(int key, t_minirt *minirt)
{
	t_vec	*orglook[2];

	orglook[0] = &minirt->camera.origin;
	orglook[1] = &minirt->camera.look_at;
	if (key == KW)
	{
		*orglook[0] = vec_add(*orglook[0], minirt->camera.basis.v);
		*orglook[1] = vec_add(*orglook[1], minirt->camera.basis.v);
	}
	else if (key == KS)
	{
		*orglook[0] = vec_sub(*orglook[0], minirt->camera.basis.v);
		*orglook[1] = vec_sub(*orglook[1], minirt->camera.basis.v);
	}
	else if (key == KA)
	{
		*orglook[0] = vec_sub(*orglook[0], minirt->camera.basis.u);
		*orglook[1] = vec_sub(*orglook[1], minirt->camera.basis.u);
	}
	else if (key == KD)
	{
		*orglook[0] = vec_add(*orglook[0], minirt->camera.basis.u);
		*orglook[1] = vec_add(*orglook[1], minirt->camera.basis.u);
	}
	re_render(minirt);
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
	re_render(minirt);
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
