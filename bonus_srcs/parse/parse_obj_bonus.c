/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:30:11 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_hyperboloid(t_p_node *node, char **split)
{
	get_cylinder(node, split);
	node->id = HY;
}

void	get_cylinder(t_p_node *node, char **split)
{
	char	**coord;

	ft_memset(node, 0, sizeof(t_p_node));
	if (split_size(split) != 6 && split_size(split) != 11)
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
	node->geometric[0] = ft_atof(split[3]);
	node->geometric[1] = ft_atof(split[4]);
	coord = ft_split(split[5], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	get_cylinder_util(node, split, coord);
}

void	get_plane(t_p_node *node, char **split)
{
	char	**coord;

	ft_memset(node, 0, sizeof(t_p_node));
	node->id = PL;
	if (split_size(split) != 4 && split_size(split) != 9)
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
	coord = ft_split(split[3], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	get_plane_util(node, split, coord);
}

void	get_sphere(t_p_node *node, char **split)
{
	char	**coord;
	double	diameter;

	ft_memset(node, 0, sizeof(t_p_node));
	node->id = SP;
	if (split_size(split) != 4 && split_size(split) != 9)
		ft_error("Error\n");
	coord = ft_split(split[1], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	node->coord.x = ft_atof(coord[0]);
	node->coord.y = ft_atof(coord[1]);
	node->coord.z = ft_atof(coord[2]);
	free_split(coord);
	diameter = ft_atof(split[2]);
	if (diameter <= 0)
		ft_error("Error\n");
	node->geometric[0] = diameter / 2.0;
	coord = ft_split(split[3], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	get_sphere_util(node, split, coord);
}

void	get_box(t_p_node *node, char **split)
{
	char	**coord;

	ft_memset(node, 0, sizeof(t_p_node));
	node->id = BO;
	if (split_size(split) != 4 && split_size(split) != 9)
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
	coord = ft_split(split[3], ',');
	if (split_size(coord) != 3)
		ft_error("Error\n");
	get_box_util(node, split, coord);
}
