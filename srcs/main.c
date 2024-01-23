/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:25:06 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 03:21:23 by jeongbpa         ###   ########.fr       */
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
                    object_add_back(minirt, object(SPHERE, \
					sphere(center, 0.2, sphere_material, vec_add(center, vec(0, \
					random_double(0, 0.5), 0)))));	
                } else if (choose_mat < 0.95) {
                    // metal
					t_color albedo = random_vec(0.5, 1.0);
					double fuzz = random_double(0.0, 0.5);
					t_material sphere_material = material(METAL, albedo, fuzz, 0);
					object_add_back(minirt, object(SPHERE, \
					sphere(center, 0.2, sphere_material, vec(0, 0, 0))));
                } else {
                    // glass
					t_material sphere_material = material(DIELECTRIC, color(1, 1, 1), 0, 1.5);
					object_add_back(minirt, object(SPHERE, \
					sphere(center, 0.2, sphere_material, vec(0, 0, 0))));
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
	minirt->object = NULL;
	minirt->box = aabb(vec(0.001, 0.001, 0.001), \
	vec(INFINITY, INFINITY, INFINITY));
	return (minirt);
}

void	minirt_random_spheres(t_minirt *minirt)
{
	t_material ground = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	ground.texture.checker.color1 = color(0.2, 0.3, 0.1);
	ground.texture.checker.color2 = color(0.9, 0.9, 0.9);
	ground.texture.checker.scale = 0.32;
	ground.texture.type = CHECKER;
	ground.texture.is_bumped = 0;
	t_material material1 = material(DIELECTRIC, color(0, 0, 0), 0, 1.5);
	t_material material2 = material(LAMBERTIAN, color(0.4, 0.2, 0.1), 0, 0);
	material2.texture.type = SOLID;
	material2.texture.is_bumped = 0;
	t_material material3 = material(METAL, color(0.7, 0.6, 0.5), 0, 0);
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,-1000,0), 1000, ground, vec(0, 0, 0))));
	make_book_cover(minirt);
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,1,0), 1.0, material1, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(-4,1,0), 1.0, material2, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(4,1,0), 1.0, material3, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
}

void	two_spheres(t_minirt *minirt)
{
	t_material material1 = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	t_checker checker = {0.32, color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9)};
	material1.texture.type = CHECKER;
	material1.texture.checker = checker;
	material1.texture.is_bumped = 0;
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,-10,0), 10, material1, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,10,0), 10, material1, vec(0, 0, 0))));
	minirt->camera.origin = vec(13, 2, 3);
	minirt->camera.look_at = vec(0, 0, 0);
	minirt->camera.vertical_up = vec(0, 1, 0);
	minirt->camera.dof_angle = 0;
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
}

void	earth(t_minirt *minirt)
{
	t_image	*earth;
	t_image	*earth_normal;

	earth = image_init(minirt->mlx, "./img/earthmap.xpm");
	earth_normal = image_init(minirt->mlx, "./img/earth_normal.xpm");
	t_material material1 = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	material1.texture.type = IMAGE;
	material1.texture.image = earth;
	material1.texture.is_bumped = 1;
	material1.texture.normal_map = earth_normal;
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0, 0, 0), 2, material1, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
}

#include <time.h> //delete

int	main(int argc, char **argv)
{
	t_minirt	*minirt;

	if (argc == 2 && argv)
	{
		clock_t start_time = clock();
		minirt = minirt_init();
		if (!strcmp(argv[1], "1"))
			minirt_random_spheres(minirt);
		else if (!strcmp(argv[1], "2"))
			two_spheres(minirt);
		else if (!strcmp(argv[1], "3"))
			earth(minirt);
		else
			ft_close(minirt, "Error: invalid argument\n", 1);
		minirt->thread_num = 0;
		multi_thread(minirt);
		mlx_put_image_to_window(minirt->mlx, minirt->win, \
								minirt->img->img_ptr, 0, 0);
		// minirt_free(&minirt);
		mlx_hook(minirt->win, 17, 0, ft_close, minirt);
		clock_t end_time = clock();
		clock_t elapsed_time = end_time - start_time;
		double elapsed_seconds = ((double)elapsed_time) / CLOCKS_PER_SEC;
		printf("elapsed time: %f\n", elapsed_seconds);
		mlx_loop(minirt->mlx);
	}
	else
		printf("Error\n");
	return (0);
}
