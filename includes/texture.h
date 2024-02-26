/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:40:22 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 18:54:32 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_data	t_data;

typedef struct s_perlin
{
	t_vec		random_vec[256];
	int			perm_x[256];
	int			perm_y[256];
	int			perm_z[256];
	double		scale;
}				t_perlin;

typedef struct s_image
{
	t_data		*img;
	int			width;
	int			height;
}				t_image;

typedef struct s_checker
{
	double		scale;
	t_color		color1;
	t_color		color2;
}				t_checker;

typedef struct s_texture
{
	int			type;
	t_checker	checker;
	t_image		*image;
	t_image		*normal_map;
	t_perlin	perlin;
	int			is_bumped;
}				t_texture;

#endif