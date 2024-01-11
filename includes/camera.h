/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 03:40:48 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 07:51:47 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"

typedef struct s_camera
{
	double		aspect_ratio;
	double		viewport_height;
	double		viewport_width;
	double		focal_length;
	t_point		origin;
	t_point		lower_left_corner;
	int			samples_per_pixel;
	int			max_depth;
}				t_camera;

#endif