/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:40:22 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 03:13:41 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_data t_data;

typedef struct s_image
{
	t_data		*img;
	int			width;
	int			height;
}				t_image;

typedef struct	s_checker
{
	double		scale;
	t_color		color1;
	t_color		color2;
}				t_checker;

typedef struct	s_texture
{
	int			type;
	t_checker	checker;
	t_image		*image;
	t_image		*normal_map;
	int			is_bumped;
}				t_texture;

#endif