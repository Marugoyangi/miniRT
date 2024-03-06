/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:28:24 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/04 07:00:35 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_texture(t_minirt *minirt, t_material *mat, \
					int type, t_vec color[2])
{
	mat->texture.type = type;
	if (type == CHECKER)
	{
		mat->texture.checker.color1 = color[0];
		mat->texture.checker.color2 = vec(0, 0, 0);
		mat->texture.checker.scale = 0.06;
	}
	else if (type == NOISE)
		perlin_generate(&mat->texture.perlin, 0.4);
	else if (type == IMAGE)
	{
		mat->texture.image = image_init(minirt->mlx, "./img/earthmap.xpm");
		mat->texture.normal_map = image_init(minirt->mlx, \
		"./img/earthmap_normal.xpm");
		mat->texture.is_bumped = 1;
	}
	else if (type == MOVING)
		mat->texture.type = SOLID;
	else
		mat->texture.type = SOLID;
}

void	set_material(t_material *mat, int type, t_vec color)
{
	t_vec		tmp;

	tmp = vec_div_const(color, 255);
	if (type == LAMBERTIAN)
		*mat = material(LAMBERTIAN, tmp, 0, 0);
	else if (type == METAL)
		*mat = material(METAL, vec(0.7, 0.6, 0.5), 0, 0);
	else if (type == DIELECTRIC)
		*mat = material(DIELECTRIC, vec(1, 1, 1), 1.5, 0);
	else if (type == DIFFUSE)
		*mat = material(DIFFUSE, tmp, 0, 0);
	else
		*mat = material(LAMBERTIAN, tmp, 0, 0);
}
