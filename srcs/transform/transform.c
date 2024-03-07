/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:21:37 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 15:11:33 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_rotate_z(double angle)
{
	t_matrix	mat;

	mat = matrix_new();
	mat.m1[0] = cos(angle);
	mat.m1[1] = -sin(angle);
	mat.m2[0] = sin(angle);
	mat.m2[1] = cos(angle);
	mat.m3[2] = 1.0f;
	mat.m4[3] = 1.0f;
	return (mat);
}

t_matrix	matrix_rotate_y(double angle)
{
	t_matrix	mat;

	mat = matrix_new();
	mat.m1[0] = cos(angle);
	mat.m1[2] = sin(angle);
	mat.m3[0] = -sin(angle);
	mat.m3[2] = cos(angle);
	mat.m2[1] = 1.0f;
	mat.m4[3] = 1.0f;
	return (mat);
}

t_matrix	matrix_rotate_x(double angle)
{
	t_matrix	mat;

	mat = matrix_new();
	mat.m1[0] = 1.0f;
	mat.m2[1] = cos(angle);
	mat.m2[2] = -sin(angle);
	mat.m3[1] = sin(angle);
	mat.m3[2] = cos(angle);
	mat.m4[3] = 1.0f;
	return (mat);
}

void	set_center_aabb(t_aabb *bbox, t_object *obj)
{
	t_interval	xyz[3];

	xyz[0] = obj->bbox.x;
	xyz[1] = obj->bbox.y;
	xyz[2] = obj->bbox.z;
	xyz[0].min = (xyz[0].min - obj->center.x);
	xyz[0].max = (xyz[0].max - obj->center.x);
	xyz[1].min = (xyz[1].min - obj->center.y);
	xyz[1].max = (xyz[1].max - obj->center.y);
	xyz[2].min = (xyz[2].min - obj->center.z);
	xyz[2].max = (xyz[2].max - obj->center.z);
	bbox->x = interval(xyz[0].min, xyz[0].max);
	bbox->y = interval(xyz[1].min, xyz[1].max);
	bbox->z = interval(xyz[2].min, xyz[2].max);
}

void	transform(t_object *obj, t_vec rotation, t_vec translation, t_vec scale)
{
	t_matrix		tmp;

	if (rotation.x == 0 && rotation.y == 0 && rotation.z == 0 && \
		translation.x == 0 && translation.y == 0 && translation.z == 0 && \
		scale.x == 1 && scale.y == 1 && scale.z == 1)
		return ;
	tmp = matrix_new();
	obj->transform.is_transformed = 1;
	obj->transform.translation = translation;
	obj->transform.rotation = vec(degree_to_rad(rotation.x), \
	degree_to_rad(rotation.y), degree_to_rad(rotation.z));
	obj->transform.scale = scale;
	tmp = matrix_mul(matrix_translate(translation), matrix_scale(scale));
	tmp = matrix_mul(tmp, matrix_rotate_x(obj->transform.rotation.x));
	tmp = matrix_mul(tmp, matrix_rotate_y(obj->transform.rotation.y));
	tmp = matrix_mul(tmp, matrix_rotate_z(obj->transform.rotation.z));
	obj->transform.matrix = tmp;
	transform_aabb(&obj->bbox, obj->transform.matrix);
	obj->transform.inverse = matrix_inverse(obj->transform.matrix);
}
