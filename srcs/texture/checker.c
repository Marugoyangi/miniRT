/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:37 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/26 10:02:28 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	checker(t_checker *checker, t_hit_record *rec)
{
	int		ret[3];

	ret[0] = (int)floor(rec->u * rec->img_width * checker->scale);
	ret[1] = (int)floor(rec->v * rec->img_height * checker->scale);
	if ((ret[0] + ret[1]) % 2 == 0)
		return (checker->color1);
	else
		return (checker->color2);
}
