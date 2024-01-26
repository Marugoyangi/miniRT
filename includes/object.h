/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:13:43 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 07:16:36 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "minirt.h"

typedef struct s_aabb	t_aabb;
typedef struct s_vec	t_point;

typedef struct s_material
{
	int			type;
	t_color		albedo;
	double		fuzz;
	double		ref_idx;
	t_texture	texture;
}	t_material;

typedef struct s_quad
{
	t_point		q;
	t_vec		u;
	t_vec		v;
	t_material	material;
	t_aabb		bounding_box;
	t_vec		normal;
	t_vec		w;
	double		d;
}	t_quad;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	int			is_moving;
	t_vec		velocity;
	t_material	material;
	t_aabb		bounding_box;
}	t_sphere;

typedef struct s_cylinder
{
	t_point		center;
	t_vec		normal;
	double		diameter;
	double		height;
	t_color		color;
	t_material	material;
	t_aabb		bounding_box;
}	t_cylinder;

typedef struct s_cone
{
	t_point		center;
	t_vec		normal;
	double		angle;
	t_color		color;
	t_material	material;
	t_aabb		bounding_box;
}	t_cone;

typedef struct s_object
{
	int				type;
	t_aabb			bbox;
	void			*element;
	struct s_object	*next;
}	t_object;

#endif