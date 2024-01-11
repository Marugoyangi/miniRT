/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:13:43 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 22:24:23 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "minirt.h"

typedef struct s_sphere
{
	t_point	center;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_point	center;
	t_vec	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point	center;
	t_vec	normal;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

typedef struct s_cone
{
	t_point	center;
	t_vec	normal;
	double	angle;
	t_color	color;
}	t_cone;

typedef struct s_object
{
	int				type;
	void			*element;
	struct s_object	*next;
}	t_object;

#endif