/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:17:10 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/23 19:00:09 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sort_bvh(t_object **node, int start, int end,
				int (*comparator)(t_object *, t_object *))
{
	int			i;
	int			j;
	t_object	*tmp;

	i = 0;
	while (i < end - start - 1)
	{
		j = i + 1;
		while (j < end - start)
		{
			if (!comparator(node[i], node[j]))
			{
				tmp = node[i];
				node[i] = node[j];
				node[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	ft_lstsize(t_object *lst)
{
	int			i;
	t_object	*tmp;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_object	**object_vector(t_object **object, int start, int end)
{
	t_object	**node;
	int			i;

	i = 0;
	node = (t_object **)ft_malloc(sizeof(t_object *) * (end - start + 1));
	while (i < end - start)
	{
		node[i] = object_copy(object, start + i);
		i++;
	}
	node[i] = NULL;
	i = 0;
	while (i < end - start - 1)
	{
		node[i]->next = node[i + 1];
		i++;
	}
	return (node);
}

t_object	**object_vector_init(t_object *object, int start, int end)
{
	t_object	**node;
	t_object	*tmp;
	int			i;

	i = 0;
	node = (t_object **)ft_malloc(sizeof(t_object *) * (end - start + 1));
	tmp = object;
	while (i < end - start)
	{
		node[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	node[i] = NULL;
	return (node);
}
