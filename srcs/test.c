/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:01:03 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 16:47:11 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//testcase
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

void	minirt_random_spheres(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(13, 2, 3), vec(0, 0, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0.6);
	minirt->camera.background = color(0.7, 0.8, 1.0);
	t_material ground = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	ground.texture.checker.color1 = color(0.2, 0.3, 0.1);
	ground.texture.checker.color2 = color(0.9, 0.9, 0.9);
	ground.texture.checker.scale = 0.6;
	ground.texture.type = CHECKER;
	ground.texture.is_bumped = 0;
	t_material material1 = material(DIELECTRIC, color(0, 0, 0), 0, 1.5);
	t_material material2 = material(LAMBERTIAN, color(0.4, 0.2, 0.1), 0, 0);
	material2.texture.type = SOLID;
	material2.texture.is_bumped = 0;
	t_material material3 = material(METAL, color(0.7, 0.6, 0.5), 0, 0);
	object_add_back(minirt, object(QUAD, \
	quad(vec(-15, 0, -10), vec(200, 0, 0), vec(0, 0, 200), ground)));
	make_book_cover(minirt);
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,1,0), 1.0, material1, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(-4,1,0), 1.0, material2, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(4,1,0), 1.0, material3, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	two_spheres(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(13, 2, 3), vec(0, 0, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0);
	minirt->camera.background = color(0.7, 0.8, 1.0);
	t_material material1 = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	t_checker checker = {0.4, color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9)};
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
	free(tmp);
}

void	earth(t_minirt *minirt)
{
	t_image	*earth;
	t_image	*earth_normal;
	t_vec	cam[3] = {vec(13, 2, 3), vec(0, 0, 0), vec(0, 1, 0)};

	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0);
	minirt->camera.background = color(0.7, 0.8, 1.0);
	earth = image_init(minirt->mlx, "./img/earthmap.xpm");
	earth_normal = image_init(minirt->mlx, "./img/earthmap_normal.xpm");
	t_material material1 = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	material1.texture.type = IMAGE;
	material1.texture.image = earth;
	material1.texture.is_bumped = 1;
	material1.texture.normal_map = earth_normal;
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0, 0, 0), 2, material1, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	two_perlin_spheres(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(13, 2, 3), vec(0, 0, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0);
	minirt->camera.background = color(0.7, 0.8, 1.0);
	t_material material1 = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	material1.texture.type = NOISE;
	material1.texture.is_bumped = 0;
	perlin_generate(&material1.texture.perlin, 0.4);
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,-1000,0), 1000, material1, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,2,0), 2, material1, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	quads(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(0, 0, 9), vec(0, 0, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 1.0);
	set_camera(minirt, 80, cam, 0);
	minirt->camera.background = color(0.7, 0.8, 1.0);
	t_material left_red = material(LAMBERTIAN, color(1.0, 0.2, 0.2), 0, 0);
	t_material back_green = material(LAMBERTIAN, color(0.2, 1.0, 0.2), 0, 0);
	t_material right_blue = material(LAMBERTIAN, color(0.2, 0.2, 1.0), 0, 0);
	t_material upper_orange = material(LAMBERTIAN, color(1.0, 0.5, 0.0), 0, 0);
	t_material lower_teal = material(LAMBERTIAN, color(0.2, 0.8, 0.8), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(-3, -2, 5), vec(0, 0, -4), \
	vec(0, 4, 0), left_red)));
	object_add_back(minirt, object(QUAD, quad(vec(-2, -2, 0), vec(4, 0, 0), \
	vec(0, 4, 0), back_green)));
	object_add_back(minirt, object(QUAD, quad(vec(3, -2, 1), vec(0, 0, 4), \
	vec(0, 4, 0), right_blue)));
	object_add_back(minirt, object(QUAD, quad(vec(-2, 3, 1), vec(4, 0, 0), \
	vec(0, 0, 4), upper_orange)));
	object_add_back(minirt, object(QUAD, quad(vec(-2, -3, 5), vec(4, 0, 0), \
	vec(0, 0, -4), lower_teal)));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	simple_light(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(26, 3, 6), vec(0, 2, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0);
	minirt->camera.samples_per_pixel = 20;
	minirt->camera.background = color(0, 0, 0);
	t_material noise = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	noise.texture.type = NOISE;
	noise.texture.is_bumped = 0;
	perlin_generate(&noise.texture.perlin, 4);
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,-1000,0), 1000, noise, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, \
	sphere(vec(0,2,0), 2, noise, vec(0, 0, 0))));
	t_material light = material(DIFFUSE, color(10000000, 10000000, 10000000), 0, 0);
	t_material light2 = material(DIFFUSE, color(24670000, 10000000, 10000000), 0, 0);
	// object_add_back(minirt, object(QUAD, quad(vec(3, 1, -2), vec(2, 0, 0), \
	// vec(0, 2, 0), light)));
	// light_add_back(minirt, object(QUAD, quad(vec(3, 1, -2), vec(2, 0, 0), \
	// vec(0, 2, 0), light)));
	object_add_back(minirt, object(SPHERE, sphere(vec(15, 25, 0), 0.005, \
	light, vec(0, 0, 0))));
	light_add_back(minirt, object(SPHERE, sphere(vec(15, 25, 0), 0.005, \
	light, vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, sphere(vec(0, 25, 15), 0.005, \
	light2, vec(0, 0, 0))));
	light_add_back(minirt, object(SPHERE, sphere(vec(0, 25, 15), 0.005, \
	light2, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	cornell_box(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(278, 278, -800), vec(278, 278, 0), vec(0, 1, 0)};
	minirt_init(minirt, 600, 1.0);
	set_camera(minirt, 40, cam, 0);
	minirt->camera.background = color(0, 0, 0);
	minirt->camera.samples_per_pixel = 20;
	t_material red = material(LAMBERTIAN, color(0.65, 0.05, 0.05), 0, 0);
	t_material white = material(LAMBERTIAN, color(0.73, 0.73, 0.73), 0, 0);
	t_material green = material(LAMBERTIAN, color(0.12, 0.45, 0.15), 0, 0);
	t_material light = material(DIFFUSE, color(7, 7, 7), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(555, 0, 0), vec(0, 0, 555), \
	vec(0, 555, 0), green)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(0, 555, 0), \
	vec(0, 0, 555), red)));
	object_add_back(minirt, object(QUAD, quad(vec(343, 554, 332), vec(-130, 0, 0), \
	vec(0, 0, -105), light)));
	light_add_back(minirt, object(QUAD, quad(vec(343, 554, 332), vec(-130, 0, 0), \
	vec(0, 0, -105), light)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(555, 0, 0), \
	vec(0, 0, 555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(555, 555, 555), vec(-555, 0, 0), \
	vec(0, 0, -555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 555), vec(555, 0, 0), \
	vec(0, 555, 0), white)));
	// t_material aluminium = material(METAL, color(0.8, 0.85, 0.88), 0, 0);
	t_object *box1 = object(BOX, box(vec(0, 0, 0), vec(165, 330, 165), \
	white));
	transform(box1, vec(0, 15, 0), vec(265, 0, 295), vec(1, 1, 1));
	object_add_back(minirt, box1);
	// t_object *box2 = object(BOX, box(vec(0, 0, 0), vec(165, 165, 165), \
	// white));
	// transform(box2, vec(15, 10, 15), vec(130, 200, 0), vec(1, 1, 1));
	// object_add_back(minirt, box2);
	t_material glass = material(DIELECTRIC, color(1, 1, 1), 0, 1.5);
	object_add_back(minirt, object(SPHERE, sphere(vec(190, 90, 190), 90, \
	glass, vec(0, 0, 0))));
	light_add_back(minirt, object(SPHERE, sphere(vec(190, 90, 190), 90, \
	glass, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	cornell_box_volume(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(278, 278, -800), vec(278, 278, 0), vec(0, 1, 0)};
	minirt_init(minirt, 600, 1.0);
	set_camera(minirt, 40, cam, 0);
	minirt->camera.background = color(0, 0, 0);
	minirt->camera.samples_per_pixel = 20;
	t_material red = material(LAMBERTIAN, color(0.65, 0.05, 0.05), 0, 0);
	t_material white = material(LAMBERTIAN, color(0.73, 0.73, 0.73), 0, 0);
	t_material green = material(LAMBERTIAN, color(0.12, 0.45, 0.15), 0, 0);
	t_material light = material(DIFFUSE, color(7, 7, 7), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(555, 0, 0), vec(0, 0, 555), \
	vec(0, 555, 0), green)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(0, 555, 0), \
	vec(0, 0, 555), red)));
	object_add_back(minirt, object(QUAD, quad(vec(113, 554, 127), vec(330, 0, 0), \
	vec(0, 0, 305), light)));
	light_add_back(minirt, object(QUAD, quad(vec(113, 554, 127), vec(330, 0, 0), \
	vec(0, 0, 305), light)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(555, 0, 0), \
	vec(0, 0, 555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(555, 555, 555), vec(-555, 0, 0), \
	vec(0, 0, -555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 555), vec(555, 0, 0), \
	vec(0, 555, 0), white)));
	t_object *box1 = object(BOX, box(vec(0, 0, 0), vec(165, 330, 165), \
	white));
	transform(box1, vec(0, 15, 0), vec(265, 1, 295), vec(1, 1, 1));
	box1->volume.density = 0.01;
	box1->volume.color = color(0, 0, 0);
	object_add_back(minirt, box1);
	t_object *box2 = object(BOX, box(vec(0, 0, 0), vec(165, 165, 165), \
	white));
	transform(box2, vec(0, -18, 0), vec(130, 1, 65), vec(1, 1, 1));
	box2->volume.density = 0.01;
	box2->volume.color = color(1, 1, 1);
	object_add_back(minirt, box2);
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	final_scene(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(478, 278, -600), vec(278, 278, 0), vec(0, 1, 0)};
	minirt_init(minirt, 600, 1.0);
	set_camera(minirt, 40, cam, 0);
	minirt->camera.background = color(0, 0, 0);
	minirt->camera.samples_per_pixel = 20;
	t_material ground = material(LAMBERTIAN, color(0.48, 0.83, 0.53), 0, 0);
	int boxes_per_side = 20;
	t_object *boxes[boxes_per_side * boxes_per_side];
	int box_count = 0;
	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			double w = 100;
			double x0 = -1000 + i * w;
			double z0 = -1000 + j * w;
			double y0 = 0;
			double x1 = x0 + w;
			double y1 = random_double(1, 101);
			double z1 = z0 + w;
			boxes[box_count++] = object(BOX, box(vec(x0, y0, z0), vec(x1, y1, z1), ground));
			object_add_back(minirt, boxes[box_count - 1]);
		}
	}
	t_material light = material(DIFFUSE, color(20, 20, 20), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(123, 554, 147), vec(300, 0, 0), vec(0, 0, 265), light)));
	light_add_back(minirt, object(QUAD, quad(vec(123, 554, 147), vec(300, 0, 0), vec(0, 0, 265), light)));
	t_vec center = vec(400, 400, 200);
	t_vec center2 = vec_add(center, vec(30, 0, 0));
	t_material moving_sphere_material = material(LAMBERTIAN, color(0.7, 0.3, 0.1), 0, 0);
	object_add_back(minirt, object(SPHERE, sphere(center, 50, moving_sphere_material, center2)));
	object_add_back(minirt, object(SPHERE, sphere(vec(260, 150, 45), 50, material(DIELECTRIC, color(0, 0, 0), 0, 1.5), vec(0, 0, 0))));
	object_add_back(minirt, object(SPHERE, sphere(vec(0, 150, 145), 50, material(METAL, color(0.8, 0.8, 0.9), 1.0, 0), vec(0, 0, 0))));
	t_object *boundary = object(SPHERE, sphere(vec(360, 150, 144), 70, material(DIELECTRIC, color(0, 0, 0), 0, 1.5), vec(0, 0, 0)));
	boundary->volume.density = 0.02;
	boundary->volume.color = color(0.2, 0.4, 0.9);
	object_add_back(minirt, boundary);
	t_object *boundaryp = object(SPHERE, sphere(vec(360, 150, 145), 71, material(DIELECTRIC, color(0, 0, 0), 0, 1.5), vec(0, 0, 0)));
	object_add_back(minirt, boundaryp);
	t_object *boundary2 = object(SPHERE, sphere(vec(0, 0, 0), 5000, material(DIELECTRIC, color(0, 0, 0), 0, 1.5), vec(0, 0, 0)));
	boundary2->volume.density = 0.0001;
	boundary2->volume.color = color(1, 1, 1);
	object_add_back(minirt, boundary2);
	t_object *earth = object(SPHERE, sphere(vec(400, 200, 400), 100, material(LAMBERTIAN, color(0.2, 0.5, 0.2), 0, 0), vec(0, 0, 0)));
	((t_sphere *)earth->element)->material.texture.type = IMAGE;
	((t_sphere *)earth->element)->material.texture.is_bumped = 1;
	((t_sphere *)earth->element)->material.texture.image = image_init(minirt->mlx, "./img/earthmap.xpm");
	((t_sphere *)earth->element)->material.texture.normal_map = image_init(minirt->mlx, "./img/earthmap_normal.xpm");
	object_add_back(minirt, earth);
	t_object *perlin_sphere = object(SPHERE, sphere(vec(220, 280, 300), 80, material(LAMBERTIAN, color(0.2, 0.4, 0.9), 0, 0), vec(0, 0, 0)));
	((t_sphere *)perlin_sphere->element)->material.texture.type = NOISE;
	((t_sphere *)perlin_sphere->element)->material.texture.is_bumped = 0;
	perlin_generate(&((t_sphere *)perlin_sphere->element)->material.texture.perlin, 0.1);
	object_add_back(minirt, perlin_sphere);
	t_material white = material(LAMBERTIAN, color(0.73, 0.73, 0.73), 0, 0);
	t_object *sphered;
	int ns = 1000;
	for (int j = 0; j < ns; j++)
	{
		sphered = object(SPHERE, sphere(random_vec(0, 165), 10, white, vec(0, 0, 0)));
		transform(sphered, vec(0, 15, 0), vec(-100, 270, 395), vec(1, 1, 1));
		object_add_back(minirt, sphered);
	}
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	bump_test(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(13, 2, 3), vec(0, 0, 0), vec(0, 1, 0)};
	minirt_init(minirt, 800, 16.0 / 9.0);
	set_camera(minirt, 20, cam, 0);
	minirt->camera.background = color(0, 0, 0);
	minirt->camera.samples_per_pixel = 100;
	t_material light = material(DIFFUSE, color(7, 7, 7), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(5, 5, 5), vec(50, 0, 0), vec(0, 0, 265), light)));
	light_add_back(minirt, object(QUAD, quad(vec(5, 5, 5), vec(50, 0, 0), vec(0, 0, 265), light)));
	t_material earth = material(LAMBERTIAN, color(0.5, 0.5, 0.5), 0, 0);
	earth.texture.type = IMAGE;
	earth.texture.is_bumped = 1;
	earth.texture.image = image_init(minirt->mlx, "./img/earthmap.xpm");
	earth.texture.normal_map = image_init(minirt->mlx, "./img/earthmap_normal.xpm");
	object_add_back(minirt, object(SPHERE, sphere(vec(0, 0, 0), 2, earth, vec(0, 0, 0))));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}

void	cylinder_test(t_minirt *minirt)
{
	t_vec	cam[3] = {vec(278, 278, -800), vec(278, 278, 0), vec(0, 1, 0)};
	minirt_init(minirt, 600, 1.0);
	set_camera(minirt, 40, cam, 0);
	minirt->camera.background = color(0, 0, 0);
	minirt->camera.samples_per_pixel = 10;
	t_material red = material(LAMBERTIAN, color(0.65, 0.05, 0.05), 0, 0);
	t_material white = material(LAMBERTIAN, color(0.73, 0.73, 0.73), 0, 0);
	t_material green = material(LAMBERTIAN, color(0.12, 0.45, 0.15), 0, 0);
	t_material light = material(DIFFUSE, color(7, 7, 7), 0, 0);
	object_add_back(minirt, object(QUAD, quad(vec(555, 0, 0), vec(0, 0, 555), \
	vec(0, 555, 0), green)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(0, 555, 0), \
	vec(0, 0, 555), red)));
	object_add_back(minirt, object(QUAD, quad(vec(343, 554, 332), vec(-130, 0, 0), \
	vec(0, 0, -105), light)));
	light_add_back(minirt, object(QUAD, quad(vec(343, 554, 332), vec(-130, 0, 0), \
	vec(0, 0, -105), light)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 0), vec(555, 0, 0), \
	vec(0, 0, 555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(555, 555, 555), vec(-555, 0, 0), \
	vec(0, 0, -555), white)));
	object_add_back(minirt, object(QUAD, quad(vec(0, 0, 555), vec(555, 0, 0), \
	vec(0, 555, 0), white)));
	t_material metal = material(METAL, color(0.8, 0.85, 0.88), 0, 0);
	t_object *cy = object(CYLINDER, cylinder(vec(165, 200, 200), 200, 200, metal));
	transform(cy, vec(0, -20, -30), vec(0, -18, 15), vec(1, 1, 1));
	object_add_back(minirt, cy);
	t_object *hb = object(HYPERBOLOID, hyperboloid(vec(400, 200, 300), 100, 200, metal));
	object_add_back(minirt, hb);
	light_add_back(minirt, object(CYLINDER, cylinder(vec(165, 200, 200), 200, 200, metal)));
	light_add_back(minirt, object(HYPERBOLOID, hyperboloid(vec(400, 200, 300), 100, 200, metal)));
	t_object **tmp = object_vector_init(minirt->object, 0, ft_lstsize(minirt->object));
	minirt->bvh = bvh_node(tmp, 0, ft_lstsize(minirt->object));
	free(tmp);
}