/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:50:57 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/29 00:10:49 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

double	ft_atof(char *str)
{
	double		d[3];
	int			i;

	i = 0;
	d[0] = 0;
	d[1] = 0;
	d[2] = 1;
	if (str[i] == '-')
	{
		d[2] = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		d[0] = d[0] * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		d[1] = d[1] * 10 + str[i] - '0';
		i++;
	}
	return (d[2] * (d[0] + d[1] / pow(10, i)));
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
