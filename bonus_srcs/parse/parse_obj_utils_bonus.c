/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:25:20 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_cylinder_util(t_p_node *node, char **split, char **coord)
{
	node->id = CY;
	if (node->normal.x < -1 || node->normal.x > 1 || \
		node->normal.y < -1 || node->normal.y > 1 || \
		node->normal.z < -1 || node->normal.z > 1)
		ft_error("Error\n");
	node->color[0] = ft_atoi(coord[0]);
	node->color[1] = ft_atoi(coord[1]);
	node->color[2] = ft_atoi(coord[2]);
	free_split(coord);
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
	node->transform[2] = vec(1, 1, 1);
	node->etc[0] = LAMBERTIAN;
	node->etc[1] = 1;
	if (split_size(split) == 11)
		get_material(node, split);
}

void	get_plane_util(t_p_node *node, char **split, char **coord)
{
	if (node->normal.x < -1 || node->normal.x > 1 || \
	node->normal.y < -1 || node->normal.y > 1 || \
	node->normal.z < -1 || node->normal.z > 1)
		ft_error("Error\n");
	node->color[0] = ft_atoi(coord[0]);
	node->color[1] = ft_atoi(coord[1]);
	node->color[2] = ft_atoi(coord[2]);
	free_split(coord);
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
	node->transform[2] = vec(1, 1, 1);
	node->etc[0] = LAMBERTIAN;
	node->etc[1] = 1;
	if (split_size(split) == 9)
		get_material(node, split);
}

void	get_sphere_util(t_p_node *node, char **split, char **coord)
{
	node->color[0] = ft_atoi(coord[0]);
	node->color[1] = ft_atoi(coord[1]);
	node->color[2] = ft_atoi(coord[2]);
	free_split(coord);
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
	node->transform[2] = vec(1, 1, 1);
	node->etc[0] = LAMBERTIAN;
	node->etc[1] = 1;
	if (split_size(split) == 9)
		get_material(node, split);
}

void	get_box_util(t_p_node *node, char **split, char **coord)
{
	node->color[0] = ft_atoi(coord[0]);
	node->color[1] = ft_atoi(coord[1]);
	node->color[2] = ft_atoi(coord[2]);
	free_split(coord);
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
	node->transform[2] = vec(1, 1, 1);
	node->etc[0] = LAMBERTIAN;
	node->etc[1] = 1;
	if (split_size(split) == 9)
		get_material(node, split);
}
