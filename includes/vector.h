/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:02:15 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 17:43:25 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct s_vec	t_color;
typedef struct s_vec	t_point;

#endif