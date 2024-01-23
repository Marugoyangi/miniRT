/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:07:34 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/23 15:19:06 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

typedef struct s_object t_object;

typedef struct s_interval
{
	double		min;
	double		max;
}				t_interval;

typedef struct s_aabb
{
	t_interval	x;
	t_interval	y;
	t_interval	z;
}				t_aabb;

typedef struct s_bvh
{
	t_aabb			bbox;
	t_object		*object;
	int				is_leaf;
	struct s_bvh 	*left;
	struct s_bvh 	*right;
}				t_bvh;

#endif