/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:25:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/17 08:01:28 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void make_book_cover(t_minirt *minirt)
{
	for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double(0.0, 1.0);
		    t_point center = vec(a + 0.9*random_double(0.0, 1.0), \
			 0.2, b + 0.9*random_double(0.0, 1.0));
			 t_point tmp = vec(4, 0.2, 0);
	         if (vec_length(vec_sub(center, tmp)) > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    t_color albedo = vec_mul(random_vec(0, 1.0), random_vec(0, 1.0));
                    t_material sphere_material = material(LAMBERTIAN, albedo, 0, 0);
                    object_add_back(minirt->objects, object(SPHERE, \
					sphere(center, 0.2, sphere_material)));	
                } else if (choose_mat < 0.95) {
                    // metal
					t_color albedo = random_vec(0.5, 1.0);
					double fuzz = random_double(0.0, 0.5);
					t_material sphere_material = material(METAL, albedo, fuzz, 0);
					object_add_back(minirt->objects, object(SPHERE, \
					sphere(center, 0.2, sphere_material)));
                } else {
                    // glass
					t_material sphere_material = material(DIELECTRIC, color(1, 1, 1), 0, 1.5);
					object_add_back(minirt->objects, object(SPHERE, \
					sphere(center, 0.2, sphere_material)));
                }
            }
        }
    }
}

void	minirt_init_screen(t_minirt *minirt)
{
	set_camera(minirt);
	minirt->img_width = 800;
	minirt->img_height = minirt->img_width / minirt->camera.aspect_ratio;
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
	t_material ground = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	t_material material1 = material(DIELECTRIC, color(0, 0, 0), 0, 1.5);
	t_material material2 = material(LAMBERTIAN, color(0.4, 0.2, 0.1), 0, 0);
	t_material material3 = material(METAL, color(0.7, 0.6, 0.5), 0, 0);
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(0,-1000,0), 1000, ground)));
	make_book_cover(minirt);
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(0,1,0), 1.0, material1)));
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(-4,1,0), 1.0, material2)));
	object_add_back(minirt->objects, object(SPHERE, \
	sphere(vec(4,1,0), 1.0, material3)));
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
