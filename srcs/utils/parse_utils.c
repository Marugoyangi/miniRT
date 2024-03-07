/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:50:57 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 15:10:27 by jeongbpa         ###   ########.fr       */
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
	double	d[4];

	d[0] = 0;
	d[1] = 1;
	d[2] = 0;
	d[3] = 0;
	if (str[(int)d[3]] == '-')
	{
		d[1] = -1;
		d[3] += 1;
	}
	d[3] -= 1;
	while (ft_isdigit(str[(int)++d[3]]))
		d[0] = d[0] * 10 + str[(int)d[3]] - '0';
	if (str[(int)d[3]] == '.')
		d[3] += 1;
	while (ft_isdigit(str[(int)d[3]]))
	{
		d[0] = d[0] * 10 + str[(int)d[3]] - '0';
		d[2]++;
		d[3] += 1;
	}
	while (d[2]--)
		d[0] /= 10;
	return (d[0] * d[1]);
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
