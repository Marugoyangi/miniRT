/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 03:40:48 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/27 01:13:13 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"

typedef struct s_basis
{
	t_vec		w;
	t_vec		u;
	t_vec		v;
	t_point		lower_left_corner;
	t_vec		viewport_u;
	t_vec		viewport_v;
	t_vec		dof_u;
	t_vec		dof_v;
}				t_basis;

typedef struct s_camera
{
	double		viewport_height;
	double		viewport_width;
	t_point		origin;
	t_point		look_at;
	int			samples_per_pixel;
	int			max_depth;
	double		fov;
	double		dof_angle;
	double		focus_distance;
	t_vec		vertical_up;
	t_basis		basis;
	int			k;
	t_color		background;
}				t_camera;
#endif