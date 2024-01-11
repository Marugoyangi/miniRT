/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:25:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/11 17:10:34 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_minirt	*minirt_init(void)
{
	t_minirt	*minirt;

	minirt = malloc(sizeof(t_minirt));
	if (!minirt)
		ft_close(NULL, "Error: minirt initialization failed\n", 1);
	minirt->mlx = mlx_init();
	minirt->img_width = 800;
	minirt->img_height = 600;
	minirt->viewpoint_width = 2;
	minirt->viewpoint_height = 2;
	minirt->focal_length = 1;
	if (!minirt->mlx)
		ft_close(minirt, "Error: mlx initialization failed\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, minirt->img_width, \
	minirt->img_height, "minirt");
	if (!minirt->win)
		ft_close(minirt, "Error: window initialization failed\n", 1);
	minirt->img = malloc(sizeof(t_data));
	minirt->img->img_ptr = mlx_new_image(minirt->mlx, minirt->img_width, \
	minirt->img_height);
	if (!minirt->img->img_ptr)
		ft_close(minirt, "Error: image initialization failed\n", 1);
	minirt->img->addr = mlx_get_data_addr(minirt->img->img_ptr, \
	&(minirt->img->bits_per_pixel), &(minirt->img->size_line), \
	&minirt->img->endian);
	return (minirt);
}

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	if (argc == 2 && argv)
	{
		minirt = minirt_init();
		// minirt_parse(&minirt, argv[1]);
		print_color(minirt);
		// minirt_free(&minirt);
		mlx_hook(minirt->win, 17, 0, ft_close, minirt);
		mlx_loop(minirt->mlx);
	}
	else
		printf("Error\n");
	return (0);
}