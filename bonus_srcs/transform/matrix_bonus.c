/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:46:49 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_matrix	matrix_mul(t_matrix a, t_matrix b)
{
	t_matrix	mat;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 0)
				mat.m1[i] = a.m1[0] * b.m1[i] + a.m1[1] * b.m2[i] + \
				a.m1[2] * b.m3[i] + a.m1[3] * b.m4[i];
			else if (j == 1)
				mat.m2[i] = a.m2[0] * b.m1[i] + a.m2[1] * b.m2[i] + \
				a.m2[2] * b.m3[i] + a.m2[3] * b.m4[i];
			else if (j == 2)
				mat.m3[i] = a.m3[0] * b.m1[i] + a.m3[1] * b.m2[i] + \
				a.m3[2] * b.m3[i] + a.m3[3] * b.m4[i];
			else
				mat.m4[i] = a.m4[0] * b.m1[i] + a.m4[1] * b.m2[i] + \
				a.m4[2] * b.m3[i] + a.m4[3] * b.m4[i];
		}
	}
	return (mat);
}

t_matrix	matrix_translate(t_vec translation)
{
	t_matrix	mat;

	mat = matrix_new();
	mat.m1[0] = 1.0f;
	mat.m2[1] = 1.0f;
	mat.m3[2] = 1.0f;
	mat.m4[3] = 1.0f;
	mat.m1[3] = translation.x;
	mat.m2[3] = translation.y;
	mat.m3[3] = translation.z;
	return (mat);
}

t_matrix	matrix_scale(t_vec scale)
{
	t_matrix	mat;

	mat = matrix_new();
	mat.m1[0] = scale.x;
	mat.m2[1] = scale.y;
	mat.m3[2] = scale.z;
	mat.m4[3] = 1.0f;
	return (mat);
}

double	matrix_determinant(t_matrix m)
{
	return (m.m1[0] * (m.m2[1] * (m.m3[2] * m.m4[3] - m.m3[3] * m.m4[2]) - \
	m.m2[2] * (m.m3[1] * m.m4[3] - m.m3[3] * m.m4[1]) + \
	m.m2[3] * (m.m3[1] * m.m4[2] - m.m3[2] * m.m4[1])) - \
	m.m1[1] * (m.m2[0] * (m.m3[2] * m.m4[3] - m.m3[3] * m.m4[2]) - \
	m.m2[2] * (m.m3[0] * m.m4[3] - m.m3[3] * m.m4[0]) + \
	m.m2[3] * (m.m3[0] * m.m4[2] - m.m3[2] * m.m4[0])) + \
	m.m1[2] * (m.m2[0] * (m.m3[1] * m.m4[3] - m.m3[3] * m.m4[1]) - \
	m.m2[1] * (m.m3[0] * m.m4[3] - m.m3[3] * m.m4[0]) + \
	m.m2[3] * (m.m3[0] * m.m4[1] - m.m3[1] * m.m4[0])) - \
	m.m1[3] * (m.m2[0] * (m.m3[1] * m.m4[2] - m.m3[2] * m.m4[1]) - \
	m.m2[1] * (m.m3[0] * m.m4[2] - m.m3[2] * m.m4[0]) + \
	m.m2[2] * (m.m3[0] * m.m4[1] - m.m3[1] * m.m4[0])));
}

t_matrix	matrix_new(void)
{
	int			i;
	t_matrix	m;

	i = -1;
	while (++i < 4)
	{
		m.m1[i] = 0.0f;
		m.m2[i] = 0.0f;
		m.m3[i] = 0.0f;
		m.m4[i] = 0.0f;
	}
	return (m);
}
