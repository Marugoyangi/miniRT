/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:25:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/12 02:49:32 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_init_screen(t_minirt *minirt)
{
	double	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	minirt->img_width = 800;
	minirt->img_height = (int)(minirt->img_width / aspect_ratio);
	minirt->viewpoint_height = 2.0;
	minirt->viewpoint_width = minirt->viewpoint_height * aspect_ratio;
	minirt->focal_length = 1.0;
}

t_minirt	*minirt_init(void)
{
	t_minirt	*minirt;

	minirt = ft_malloc(sizeof(t_minirt));
	minirt->mlx = mlx_init();
	minirt_init_screen(minirt);
	if (!minirt->mlx)
		ft_close(minirt, "Error: mlx initialization failed\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, minirt->img_width, \
	minirt->img_height, "minirt");
	if (!minirt->win)
		ft_close(minirt, "Error: window initialization failed\n", 1);
	minirt->img = ft_malloc(sizeof(t_data));
	minirt->img->img_ptr = mlx_new_image(minirt->mlx, minirt->img_width, \
	minirt->img_height);
	if (!minirt->img->img_ptr)
		ft_close(minirt, "Error: image initialization failed\n", 1);
	minirt->img->addr = mlx_get_data_addr(minirt->img->img_ptr, \
	&(minirt->img->bits_per_pixel), &(minirt->img->size_line), \
	&minirt->img->endian);
	minirt->objects = NULL;
	return (minirt);
}

void	minirt_parse(t_minirt *minirt)
{
	minirt->objects = ft_malloc(sizeof(t_object *));
	*(minirt->objects) = NULL;
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(0, -100.5, -1), 100)));
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(0, 0, -1), 0.5)));
}

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	if (argc == 2 && argv)
	{
		minirt = minirt_init();
		minirt_parse(minirt);
		print_color(minirt);
		// minirt_free(&minirt);
		mlx_hook(minirt->win, 17, 0, ft_close, minirt);
		mlx_loop(minirt->mlx);
	}
	else
		printf("Error\n");
	return (0);
}
