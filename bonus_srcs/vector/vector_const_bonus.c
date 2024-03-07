/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_const_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:46:20 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	vec_mul_const(t_vec vec, double c)
{
	t_vec	ret;

	ret.x = vec.x * c;
	ret.y = vec.y * c;
	ret.z = vec.z * c;
	return (ret);
}

t_vec	vec_div_const(t_vec vec, double c)
{
	t_vec	ret;

	ret.x = vec.x / c;
	ret.y = vec.y / c;
	ret.z = vec.z / c;
	return (ret);
}

t_vec	vec_add_const(t_vec vec, double c)
{
	t_vec	ret;

	ret.x = vec.x + c;
	ret.y = vec.y + c;
	ret.z = vec.z + c;
	return (ret);
}

t_vec	vec_sub_const(t_vec vec, double c)
{
	t_vec	ret;

	ret.x = vec.x - c;
	ret.y = vec.y - c;
	ret.z = vec.z - c;
	return (ret);
}

t_vec	vec_dot_const(t_vec vec, double c)
{
	t_vec	ret;

	ret.x = vec.x * c;
	ret.y = vec.y * c;
	ret.z = vec.z * c;
	return (ret);
}
