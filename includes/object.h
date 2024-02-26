/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:13:43 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 13:29:10 by jeongbpa         ###   ########.fr       */
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
	t_color		emitted;
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
	double		area;
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
	double		diameter;
	double		height;
	t_material	material;
	t_aabb		bounding_box;
}	t_cylinder;

typedef struct s_hypoboloid
{
	t_point		center;
	double		diameter;
	double		height;
	double		k;
	t_material	material;
	t_aabb		bounding_box;
}	t_hypoboloid;

typedef struct s_box
{
	t_point		min;
	t_point		max;
	t_object	*list;
	t_material	material;
	t_aabb		bounding_box;
}	t_box;

typedef struct s_transform
{
	int			is_transformed;
	t_vec		translation;
	t_vec		rotation;
	t_vec		scale;
	t_matrix	matrix;
	t_matrix	inverse;
}	t_transform;

typedef struct s_volume
{
	double		density;
	t_color		color;
}	t_volume;

typedef struct s_object
{
	int					type;
	t_aabb				bbox;
	void				*element;
	struct s_object		*next;
	struct s_transform	transform;
	struct s_volume		volume;
}				t_object;

typedef struct s_pdf
{
	t_object	*object;
	t_point		origin;
	double		value;
	t_vec		generated;
}	t_pdf;

#endif