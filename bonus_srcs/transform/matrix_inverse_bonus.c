/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:30:32 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_matrix	matrix_inverse_third(t_matrix inv, t_matrix m, double det)
{
	inv.m4[0] = (-m.m2[0] * m.m3[1] * m.m4[2] + m.m2[0] * m.m3[2] * m.m4[1] + \
	m.m3[0] * m.m2[1] * m.m4[2] - m.m3[0] * m.m2[2] * m.m4[1] - \
	m.m4[0] * m.m2[1] * m.m3[2] + m.m4[0] * m.m2[2] * m.m3[1]) / det;
	inv.m4[1] = (m.m1[0] * m.m3[1] * m.m4[2] - m.m1[0] * m.m3[2] * m.m4[1] - \
	m.m3[0] * m.m1[1] * m.m4[2] + m.m3[0] * m.m1[2] * m.m4[1] + \
	m.m4[0] * m.m1[1] * m.m3[2] - m.m4[0] * m.m1[2] * m.m3[1]) / det;
	inv.m4[2] = (-m.m1[0] * m.m2[1] * m.m4[2] + m.m1[0] * m.m2[2] * m.m4[1] + \
	m.m2[0] * m.m1[1] * m.m4[2] - m.m2[0] * m.m1[2] * m.m4[1] - \
	m.m4[0] * m.m1[1] * m.m2[2] + m.m4[0] * m.m1[2] * m.m2[1]) / det;
	inv.m4[3] = (m.m1[0] * m.m2[1] * m.m3[2] - m.m1[0] * m.m2[2] * m.m3[1] - \
	m.m2[0] * m.m1[1] * m.m3[2] + m.m2[0] * m.m1[2] * m.m3[1] + \
	m.m3[0] * m.m1[1] * m.m2[2] - m.m3[0] * m.m1[2] * m.m2[1]) / det;
	return (inv);
}

t_matrix	matrix_inverse_second(t_matrix inv, t_matrix m, double det)
{
	inv.m2[2] = (-m.m1[0] * m.m2[2] * m.m4[3] + m.m1[0] * m.m2[3] * m.m4[2] + \
	m.m2[0] * m.m1[2] * m.m4[3] - m.m2[0] * m.m1[3] * m.m4[2] - \
	m.m4[0] * m.m1[2] * m.m2[3] + m.m4[0] * m.m1[3] * m.m2[2]) / det;
	inv.m2[3] = (m.m1[0] * m.m2[2] * m.m3[3] - m.m1[0] * m.m2[3] * m.m3[2] - \
	m.m2[0] * m.m1[2] * m.m3[3] + m.m2[0] * m.m1[3] * m.m3[2] + \
	m.m3[0] * m.m1[2] * m.m2[3] - m.m3[0] * m.m1[3] * m.m2[2]) / det;
	inv.m3[0] = (m.m2[0] * m.m3[1] * m.m4[3] - m.m2[0] * m.m3[3] * m.m4[1] - \
	m.m3[0] * m.m2[1] * m.m4[3] + m.m3[0] * m.m2[3] * m.m4[1] + \
	m.m4[0] * m.m2[1] * m.m3[3] - m.m4[0] * m.m2[3] * m.m3[1]) / det;
	inv.m3[1] = (-m.m1[0] * m.m3[1] * m.m4[3] + m.m1[0] * m.m3[3] * m.m4[1] + \
	m.m3[0] * m.m1[1] * m.m4[3] - m.m3[0] * m.m1[3] * m.m4[1] - \
	m.m4[0] * m.m1[1] * m.m3[3] + m.m4[0] * m.m1[3] * m.m3[1]) / det;
	inv.m3[2] = (m.m1[0] * m.m2[1] * m.m4[3] - m.m1[0] * m.m2[3] * m.m4[1] - \
	m.m2[0] * m.m1[1] * m.m4[3] + m.m2[0] * m.m1[3] * m.m4[1] + \
	m.m4[0] * m.m1[1] * m.m2[3] - m.m4[0] * m.m1[3] * m.m2[1]) / det;
	inv.m3[3] = (-m.m1[0] * m.m2[1] * m.m3[3] + m.m1[0] * m.m2[3] * m.m3[1] + \
	m.m2[0] * m.m1[1] * m.m3[3] - m.m2[0] * m.m1[3] * m.m3[1] - \
	m.m3[0] * m.m1[1] * m.m2[3] + m.m3[0] * m.m1[3] * m.m2[1]) / det;
	matrix_inverse_third(inv, m, det);
	return (inv);
}

t_matrix	matrix_inverse(t_matrix m)
{
	double		det;
	t_matrix	inv;

	inv = matrix_new();
	det = matrix_determinant(m);
	inv.m1[0] = (m.m2[1] * m.m3[2] * m.m4[3] - m.m2[1] * m.m3[3] * m.m4[2] - \
	m.m3[1] * m.m2[2] * m.m4[3] + m.m3[1] * m.m2[3] * m.m4[2] + \
	m.m4[1] * m.m2[2] * m.m3[3] - m.m4[1] * m.m2[3] * m.m3[2]) / det;
	inv.m1[1] = (-m.m1[1] * m.m3[2] * m.m4[3] + m.m1[1] * m.m3[3] * m.m4[2] + \
	m.m3[1] * m.m1[2] * m.m4[3] - m.m3[1] * m.m1[3] * m.m4[2] - \
	m.m4[1] * m.m1[2] * m.m3[3] + m.m4[1] * m.m1[3] * m.m3[2]) / det;
	inv.m1[2] = (m.m1[1] * m.m2[2] * m.m4[3] - m.m1[1] * m.m2[3] * m.m4[2] - \
	m.m2[1] * m.m1[2] * m.m4[3] + m.m2[1] * m.m1[3] * m.m4[2] + \
	m.m4[1] * m.m1[2] * m.m2[3] - m.m4[1] * m.m1[3] * m.m2[2]) / det;
	inv.m1[3] = (-m.m1[1] * m.m2[2] * m.m3[3] + m.m1[1] * m.m2[3] * m.m3[2] + \
	m.m2[1] * m.m1[2] * m.m3[3] - m.m2[1] * m.m1[3] * m.m3[2] - \
	m.m3[1] * m.m1[2] * m.m2[3] + m.m3[1] * m.m1[3] * m.m2[2]) / det;
	inv.m2[0] = (-m.m2[0] * m.m3[2] * m.m4[3] + m.m2[0] * m.m3[3] * m.m4[2] + \
	m.m3[0] * m.m2[2] * m.m4[3] - m.m3[0] * m.m2[3] * m.m4[2] - \
	m.m4[0] * m.m2[2] * m.m3[3] + m.m4[0] * m.m2[3] * m.m3[2]) / det;
	inv.m2[1] = (m.m1[0] * m.m3[2] * m.m4[3] - m.m1[0] * m.m3[3] * m.m4[2] - \
	m.m3[0] * m.m1[2] * m.m4[3] + m.m3[0] * m.m1[3] * m.m4[2] + \
	m.m4[0] * m.m1[2] * m.m3[3] - m.m4[0] * m.m1[3] * m.m3[2]) / det;
	inv = matrix_inverse_second(inv, m, det);
	return (inv);
}
