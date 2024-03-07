/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:33:53 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 16:14:00 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_read_node(t_minirt *minirt, t_p_node *node, \
					int width, double ratio)
{
	t_p_node	*tmp;

	tmp = node;
	minirt_init(minirt, width, ratio);
	while (tmp)
	{
		if (tmp->id == A)
			set_ambient(minirt, tmp);
		else if (tmp->id == C)
			set_cam(minirt, tmp);
		else if (tmp->id == L)
			set_light(minirt, tmp);
		else if (tmp->id == SP)
			set_sphere(minirt, tmp);
		else if (tmp->id == PL)
			set_plane(minirt, tmp);
		else if (tmp->id == CY)
			set_cylinder(minirt, tmp);
		else if (tmp->id == HY)
			set_hyperboloid(minirt, tmp);
		else if (tmp->id == BO)
			set_box(minirt, tmp);
		tmp = tmp->next;
	}
	free_p_node(node);
}

void	get_id(t_p_node *node, char **split, int (*tmp)[5])
{
	if (!ft_strcmp(split[0], "A"))
		get_ambient(node, split, tmp);
	else if (!ft_strcmp(split[0], "C"))
		get_camera(node, split, tmp);
	else if (!ft_strcmp(split[0], "L"))
		get_light(node, split, tmp);
	else if (!ft_strcmp(split[0], "sp"))
		get_sphere(node, split);
	else if (!ft_strcmp(split[0], "pl"))
		get_plane(node, split);
	else if (!ft_strcmp(split[0], "cy"))
		get_cylinder(node, split);
	else if (!ft_strcmp(split[0], "hy"))
		get_hyperboloid(node, split);
	else if (!ft_strcmp(split[0], "bo"))
		get_box(node, split);
	else
		ft_error("Error\n");
}

void	p_node_add_back(t_p_node **node, t_p_node *new)
{
	t_p_node	*last;

	last = *node;
	if (!last)
	{
		*node = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

int	namecheck(char *path, char *ext)
{
	int		i;
	int		j;

	i = ft_strlen(path);
	j = ft_strlen(ext);
	if (i < j)
		ft_error("Error\n");
	while (j >= 0)
	{
		if (path[i] != ext[j])
			ft_error("Error\n");
		i--;
		j--;
	}
	return (1);
}

t_p_node	*parse_create_node(char *path)
{
	int			tmp[5];
	char		*line;
	t_p_node	*nodes[2];
	char		**split;

	nodes[0] = NULL;
	split = NULL;
	ft_memset(tmp, 0, sizeof(int) * 5);
	if (!namecheck(path, ".rt"))
		ft_error("Error\n");
	tmp[0] = open(path, 0, O_RDONLY);
	if (tmp[0] < 0)
		ft_error("Error\n");
	line = get_next_line(tmp[0]);
	if (!line)
		ft_error("Error\n");
	parse_node_iter(line, nodes, &tmp, split);
	close(tmp[0]);
	return (nodes[0]);
}
