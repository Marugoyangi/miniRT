/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:25:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/02/29 06:34:55 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_init(t_minirt *minirt, int width, double aspect_ratio)
{
	minirt->mlx = mlx_init();
	minirt->img_width = width;
	minirt->aspect_ratio = aspect_ratio;
	minirt->img_height = (int)(minirt->img_width / minirt->aspect_ratio);
	if (!minirt->mlx)
		ft_error("Error: mlx initialization failed\n");
	minirt->win = mlx_new_window(minirt->mlx, minirt->img_width, \
	minirt->img_height, "minirt");
	if (!minirt->win)
		ft_error("Error: window initialization failed\n");
	minirt->img = ft_malloc(sizeof(t_data));
	minirt->img->img_ptr = mlx_new_image(minirt->mlx, minirt->img_width, \
	minirt->img_height);
	if (!minirt->img->img_ptr)
		ft_error("Error: image initialization failed\n");
	minirt->img->addr = mlx_get_data_addr(minirt->img->img_ptr, \
	&(minirt->img->bits_per_pixel), &(minirt->img->size_line), \
	&minirt->img->endian);
	minirt->object = NULL;
	minirt->light = NULL;
	minirt->box = aabb(vec(INFINITY, INFINITY, INFINITY), vec(-INFINITY, \
	-INFINITY, -INFINITY));
}

int	main(int argc, char **argv)
{
	t_minirt	minirt;
	t_p_node	*node;
	t_object	**tmp;

	if (argc == 2 && argv)
	{
		node = parse_create_node(argv[1]);
		parse_read_node(&minirt, node, 800, 16.0 / 9.0);
		tmp = object_vector_init(minirt.object, 0, ft_lstsize(minirt.object));
		minirt.bvh = bvh_node(tmp, 0, ft_lstsize(minirt.object));
		free(tmp);
		// if (!strcmp(argv[1], "1"))
		// 	minirt_random_spheres(&minirt);
		// else if (!strcmp(argv[1], "2"))
		// 	two_spheres(&minirt);
		// else if (!strcmp(argv[1], "3"))
		// 	earth(&minirt);
		// else if (!strcmp(argv[1], "4"))
		// 	two_perlin_spheres(&minirt);
		// else if (!strcmp(argv[1], "5"))
		// 	quads(&minirt);
		// else if (!strcmp(argv[1], "6"))
		// 	simple_light(&minirt);
		// else if (!strcmp(argv[1], "7"))
		// 	cornell_box(&minirt);
		// else if (!strcmp(argv[1], "8"))
		// 	cornell_box_volume(&minirt);
		// else if (!strcmp(argv[1], "9"))
		// 	final_scene(&minirt);
		// else if (!strcmp(argv[1], "10"))
		// 	bump_test(&minirt);
		// else if (!strcmp(argv[1], "11"))
		// 	cylinder_test(&minirt);
		// else
		// 	exit(1);
		multi_thread(&minirt);
		mlx_put_image_to_window(minirt.mlx, minirt.win, \
								minirt.img->img_ptr, 0, 0);
		mlx_hook(minirt.win, 2, 0, key_input, &minirt);
		mlx_hook(minirt.win, 17, 0, ft_close, &minirt);
		mlx_loop(minirt.mlx);
	}
}
