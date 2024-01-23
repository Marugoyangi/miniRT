/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:37 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 02:32:51 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	checker(t_checker *checker, t_hit_record *rec)
{
	int		ret[3];
	double	factor;

	factor = 1 / checker->scale;
	ret[0] = (int)(rec->u * rec->p.x * factor) % 2;
	ret[1] = (int)(rec->v * rec->p.y * factor) % 2;
	ret[2] = (int)(rec->p.z * factor) % 2;
	if ((ret[0] + ret[1] + ret[2]) % 2 == 0)
		return (checker->color1);
	else
		return (checker->color2);
}
