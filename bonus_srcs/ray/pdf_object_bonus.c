/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdf_object_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:16:22 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_pdf	pdf_quad(t_object *object, t_vec origin, \
				t_ray *tmp_ray, t_vec *direction)
{
	t_hit_record	rec;
	double			tmp[2];
	t_quad			*quad;
	t_pdf			pdf;

	quad = (t_quad *)object->element;
	pdf.generated = vec_add(vec_add(quad->q, \
	vec_mul_const(quad->u, random_double(0, 1))), \
	vec_mul_const(quad->v, random_double(0, 1)));
	pdf.generated = vec_sub(pdf.generated, origin);
	if (direction)
		pdf.generated = *direction;
	pdf.object = object;
	pdf.origin = origin;
	*tmp_ray = ray(origin, pdf.generated, random_double(0, 1));
	if (!hit_quad(tmp_ray, quad, interval(0.001, INFINITY), &rec))
	{
		pdf.value = 0;
		return (pdf);
	}
	tmp[0] = rec.t * rec.t * vec_length_squared(pdf.generated);
	tmp[1] = fabs(vec_dot(pdf.generated, rec.normal) / \
	vec_length(pdf.generated));
	pdf.value = tmp[0] / (tmp[1] * quad->area);
	return (pdf);
}

t_pdf	pdf_sphere(t_object *object, t_vec origin, \
				t_ray *tmp_ray, t_vec *direction)
{
	t_vec			dir;
	t_hit_record	rec;
	t_pdf			pdf;
	t_onb			uvw;

	dir = vec_sub(((t_sphere *)object->element)->center, origin);
	uvw = onb(dir);
	pdf.generated = onb_local(uvw, random_to_sphere(\
	((t_sphere *)object->element)->radius, vec_length_squared(dir)));
	if (direction)
		pdf.generated = *direction;
	*tmp_ray = ray(origin, pdf.generated, random_double(0, 1));
	if (!hit_sphere(tmp_ray, (t_sphere *)object->element, \
	interval(0.0001, INFINITY), &rec))
	{
		pdf.value = 0;
		return (pdf);
	}
	pdf.value = 1 / (2 * PI * (1 - sqrt(1 - \
	((t_sphere *)object->element)->radius * \
	((t_sphere *)object->element)->radius / vec_length_squared(dir))));
	pdf.origin = origin;
	pdf.object = object;
	return (pdf);
}

t_pdf	pdf_light(t_object *light, t_hit_record *rec, \
				t_ray *tmp_ray, t_vec *direction)
{
	t_pdf	pdf;

	if (light == NULL)
	{
		pdf.value = 0;
		return (pdf);
	}
	if (light->type == QUAD)
		return (pdf_quad(light, rec->p, tmp_ray, direction));
	else if (light->type == SPHERE)
		return (pdf_sphere(light, rec->p, tmp_ray, direction));
	return (pdf_cosine(tmp_ray, rec, tmp_ray, direction));
}
