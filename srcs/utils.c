/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:56 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 16:44:01 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	exit(1);
}

int	ft_close(t_minirt *minirt, char *error, int flag)
{
	if (minirt->mlx && minirt->img && minirt->img->img_ptr)
		mlx_destroy_image(minirt->mlx, minirt->img->img_ptr);
	if (minirt->mlx && minirt->win)
		mlx_destroy_window(minirt->mlx, minirt->win);
	if (minirt->img)
		free(minirt->img);
	if (minirt)
		free(minirt);
	if (error && flag == 1)
		ft_error(error);
	exit(1);
}
