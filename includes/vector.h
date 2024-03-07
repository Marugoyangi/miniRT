/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:52:46 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct s_matrix
{
	double		m1[4];
	double		m2[4];
	double		m3[4];
	double		m4[4];
}				t_matrix;

typedef struct s_onb
{
	t_vec		u;
	t_vec		v;
	t_vec		w;
}				t_onb;

typedef struct s_vec	t_color;
typedef struct s_vec	t_point;

#endif