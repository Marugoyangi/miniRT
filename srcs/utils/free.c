/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:17:18 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/26 20:18:23 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_object(t_object *object);

void	free_list(t_object *list)
{
	t_object	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_object(tmp);
	}
}

void	free_element(void *element, int type)
{
	if (element == NULL)
		return ;
	if (type == SPHERE)
	{
		if (((t_sphere *)element)->material.texture.type == IMAGE)
		{
			if (((t_sphere *)element)->material.texture.image)
			{
				free(((t_sphere *)element)->material.texture.image->img);
				free(((t_sphere *)element)->material.texture.image);
			}
			if (((t_sphere *)element)->material.texture.normal_map)
			{
				free(((t_sphere *)element)->material.texture.normal_map->img);
				free(((t_sphere *)element)->material.texture.normal_map);
			}
		}
	}
	else if (type == BOX)
		free_list(((t_box *)element)->list);
	free(element);
}

void	free_object(t_object *object)
{
	if (object == NULL)
		return ;
	free_element(object->element, object->type);
	free(object);
}

void	free_node(t_bvh *node)
{
	if (node == NULL)
		return ;
	free_node(node->left);
	free_node(node->right);
	free_object(node->object);
	free(node);
}

void	free_all(t_minirt *minirt)
{
	free_node(minirt->bvh);
	free_list(minirt->light);
	free(minirt->img->img_ptr);
	free(minirt->img);
	free(minirt->win);
	free(minirt->mlx);
	exit(0);
}
