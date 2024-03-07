/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_iter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:10:46 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_p_node(t_p_node *node)
{
	t_p_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
}

void	parse_node_iter(char *line, t_p_node *nodes[2], \
					int (*tmp)[5], char **split)
{
	while (line)
	{
		split = ft_split(line, ' ');
		if (split[0] == NULL)
		{
			free_split(split);
			free(line);
			line = get_next_line((*tmp)[0]);
			continue ;
		}
		nodes[1] = ft_malloc(sizeof(t_p_node));
		if (!nodes[0])
			nodes[0] = nodes[1];
		get_id(nodes[1], split, tmp);
		free_split(split);
		if (nodes[0] != nodes[1])
			p_node_add_back(&nodes[0], nodes[1]);
		free(line);
		line = get_next_line((*tmp)[0]);
	}
}
