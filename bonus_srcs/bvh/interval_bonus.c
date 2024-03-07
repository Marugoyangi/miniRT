/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 08:06:59 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	interval_size(t_interval interval)
{
	return (interval.max - interval.min);
}

t_interval	interval_padding(t_interval interval, double padding)
{
	interval.min -= padding;
	interval.max += padding;
	return (interval);
}

int	interval_is_overlap(t_interval a, t_interval b)
{
	if (a.min > b.max || b.min > a.max)
		return (0);
	return (1);
}

t_interval	interval_union(t_interval a, t_interval b)
{
	t_interval	ret;

	ret.min = fmin(a.min, b.min);
	ret.max = fmax(a.max, b.max);
	return (ret);
}

t_interval	interval(double min, double max)
{
	t_interval	ret;

	ret.min = min;
	ret.max = max;
	return (ret);
}
