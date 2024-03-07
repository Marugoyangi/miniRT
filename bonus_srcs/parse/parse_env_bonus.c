/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:28:24 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:57:16 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	test_light(t_p_node *node)
{
	if (node->geometric[0] < 0 || node->geometric[0] > 1)
		ft_error("Error\n");
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
}

void	get_light(t_p_node *node, char **split, int (*tmp)[5])
{
	char	**coord;

	(*tmp)[4] = 1;
	ft_memset(node, 0, sizeof(t_p_node));
	node->id = L;
	if (split_size(split) != 4)
		ft_error("Error\n");
	coord = ft_split(split[1], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->coord.x = ft_atof(coord[0]);
	node->coord.y = ft_atof(coord[1]);
	node->coord.z = ft_atof(coord[2]);
	free_split(coord);
	node->geometric[0] = ft_atof(split[2]);
	coord = ft_split(split[3], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->color[0] = ft_atoi(coord[0]);
	node->color[1] = ft_atoi(coord[1]);
	node->color[2] = ft_atoi(coord[2]);
	free_split(coord);
	test_light(node);
}

void	test_camera(t_p_node *node, char **split)
{
	int	fov;

	if (node->normal.x == 0 && node->normal.y == 0 && node->normal.z == 0)
		ft_error("Error\n");
	if (node->normal.x < -1 || node->normal.x > 1 || \
		node->normal.y < -1 || node->normal.y > 1 || \
		node->normal.z < -1 || node->normal.z > 1)
		ft_error("Error\n");
	fov = ft_atoi(split[3]);
	if (fov < 0 || fov > 180)
		ft_error("Error\n");
	node->etc[0] = fov;
}

void	get_camera(t_p_node *node, char **split, int (*tmp)[5])
{
	char	**coord;

	if ((*tmp)[3] == 1)
		ft_error("Error\n");
	(*tmp)[3] = 1;
	ft_memset(node, 0, sizeof(t_p_node));
	node->id = C;
	if (split_size(split) != 4)
		ft_error("Error\n");
	coord = ft_split(split[1], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->coord.x = ft_atof(coord[0]);
	node->coord.y = ft_atof(coord[1]);
	node->coord.z = ft_atof(coord[2]);
	free_split(coord);
	coord = ft_split(split[2], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->normal.x = ft_atof(coord[0]);
	node->normal.y = ft_atof(coord[1]);
	node->normal.z = ft_atof(coord[2]);
	free_split(coord);
	test_camera(node, split);
}

void	get_ambient(t_p_node *node, char **split, int (*tmp)[5])
{
	char	**color;

	if ((*tmp)[2] == 1)
		ft_error("Error\n");
	(*tmp)[2] = 1;
	ft_memset(node, 0, sizeof(t_p_node));
	node->id = A;
	if (split_size(split) != 3)
		ft_error("Error\n");
	node->geometric[0] = ft_atof(split[1]);
	if (node->etc[0] < 0 || node->etc[0] > 1)
		ft_error("Error\n");
	color = ft_split(split[2], ',');
	if (split_size(color) != 3)
		ft_error("Error\n");
	node->color[0] = ft_atoi(color[0]);
	node->color[1] = ft_atoi(color[1]);
	node->color[2] = ft_atoi(color[2]);
	if (node->color[0] < 0 || node->color[0] > 255 || \
		node->color[1] < 0 || node->color[1] > 255 || \
		node->color[2] < 0 || node->color[2] > 255)
		ft_error("Error\n");
	free_split(color);
}
