/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:10:43 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 16:23:56 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	transform_by_normal(t_object *obj, t_vec normal, t_vec trans, \
					t_vec scale)
{
	double	d[3];

	d[0] = atan2(normal.y, normal.z) * 180 / M_PI;
	d[1] = atan2(-normal.x, sqrt(normal.y * normal.y + \
	normal.z * normal.z)) * 180 / M_PI;
	d[2] = atan2(normal.x, normal.y) * 180 / M_PI;
	transform(obj, vec(d[0], d[1], d[2]), trans, scale);
}

void	check_transform(t_p_node *node, char **coord)
{
	free_split(coord);
	if (node->transform[0].x < -180 || node->transform[0].x > 180 || \
		node->transform[0].y < -180 || node->transform[0].y > 180 || \
		node->transform[0].z < -180 || node->transform[0].z > 180)
		ft_error("Error\n");
	if (node->transform[2].x == 0 || node->transform[2].y == 0 || \
		node->transform[2].z == 0)
		ft_error("Error\n");
	if (node->transform[0].x || node->transform[0].y || node->transform[0].z || \
		node->transform[1].x || node->transform[1].y || node->transform[1].z || \
		(node->transform[2].x != 1 || node->transform[2].y != 1 || \
		node->transform[2].z != 1))
	{
		node->is_transformed = 1;
	}
}

void	get_transform(t_p_node *node, char **split)
{
	char	**coord;
	int		size;

	size = split_size(split);
	coord = ft_split(split[size - 3], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->transform[0].x = ft_atof(coord[0]);
	node->transform[0].y = ft_atof(coord[1]);
	node->transform[0].z = ft_atof(coord[2]);
	free_split(coord);
	coord = ft_split(split[size - 2], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->transform[1].x = ft_atof(coord[0]);
	node->transform[1].y = ft_atof(coord[1]);
	node->transform[1].z = ft_atof(coord[2]);
	free_split(coord);
	coord = ft_split(split[size - 1], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->transform[2].x = ft_atof(coord[0]);
	node->transform[2].y = ft_atof(coord[1]);
	node->transform[2].z = ft_atof(coord[2]);
	check_transform(node, coord);
}

void	get_texture(t_p_node *node, char **split)
{
	int	size;

	size = split_size(split);
	if (!ft_strcmp(split[size - 4], "checker"))
		node->etc[1] = CHECKER;
	else if (!ft_strcmp(split[size - 4], "noise"))
		node->etc[1] = NOISE;
	else if (!ft_strcmp(split[size - 4], "earth"))
		node->etc[1] = IMAGE;
	else
		node->etc[1] = SOLID;
	get_transform(node, split);
}

void	get_material(t_p_node *node, char **split)
{
	int	size;

	size = split_size(split);
	if (!ft_strcmp(split[size - 5], "metal"))
		node->etc[0] = METAL;
	else if (!ft_strcmp(split[size - 5], "solid"))
		node->etc[0] = LAMBERTIAN;
	else if (!ft_strcmp(split[size - 5], "glass"))
		node->etc[0] = DIELECTRIC;
	else if (!ft_strcmp(split[size - 5], "light"))
		node->etc[0] = DIFFUSE;
	else if (!ft_strcmp(split[size - 5], "volume"))
		node->etc[0] = PHASE;
	else if (!ft_strcmp(split[size - 5], "moving"))
		node->etc[0] = MOVING;
	else
		node->etc[0] = LAMBERTIAN;
	get_texture(node, split);
}
