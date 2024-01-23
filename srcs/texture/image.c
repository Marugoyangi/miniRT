/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:05:46 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/01/24 05:04:52 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	image_color(t_texture *texture, t_image *image, t_hit_record *rec)
{
	t_color	color;
	char	*dst;
	int		i;
	int		j;

	if (texture)
	{
		rec->u = random_clamp(rec->u, 0, 1);
		rec->v = random_clamp(rec->v, 0, 1);
	}
	i = (int)(rec->u * image->width);
	j = (int)(rec->v * image->height);
	dst = image->img->addr + (j * image->img->size_line + i * \
	(image->img->bits_per_pixel / 8));
	color.x = (unsigned char)dst[2] * 1.0 / 255;
	color.y = (unsigned char)dst[1] * 1.0 / 255;
	color.z = (unsigned char)dst[0] * 1.0 / 255;
	if (texture && texture->is_bumped == 1)
	{
		rec->normal = vec_add(vec_add_const(vec_mul_const(\
		image_color(NULL, texture->normal_map, rec), 2.0), 1.0),
		rec->normal);
		rec->normal = vec_unit(rec->normal);
	}
	return (color);
}

t_image	*image_init(void *mlx, char *path)
{
	t_image	*image;

	image = ft_malloc(sizeof(t_image));
	image->width = 1024;
	image->height = 512;
	image->img = mlx_xpm_file_to_image(mlx, path, &image->width, &image->height);
	image->img->addr = mlx_get_data_addr(image->img, &image->img->bits_per_pixel, \
	&image->img->size_line, &image->img->endian);
	return (image);
}
