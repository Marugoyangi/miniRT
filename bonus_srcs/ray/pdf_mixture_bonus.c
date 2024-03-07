/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdf_mixture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:19:37 by jeongbpa          #+#    #+#             */
/*   Updated: 2024/03/07 17:50:40 by jeongbpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	pdf_mix_set(int (*i)[3], double (*n)[2], \
				t_object *object, t_object **tmp)
{
	(*i)[0] = 0;
	(*i)[1] = ft_lstsize(object);
	(*i)[2] = random_int(0, (*i)[1] - 1);
	(*n)[0] = 1.0 / (*i)[1];
	(*n)[1] = 0;
	*tmp = object;
}

t_pdf	pdf_mix_light(t_object *object, t_hit_record *rec, \
					t_ray *tmp_ray, t_vec *direction)
{
	t_pdf		pdf[2];
	int			i[3];
	double		n[2];
	t_object	*tmp;

	pdf_mix_set(&i, &n, object, &tmp);
	while (i[0] < i[1])
	{
		if (i[0] == i[2])
			pdf[0] = pdf_light(tmp, rec, tmp_ray, direction);
		tmp = tmp->next;
		i[0]++;
	}
	if (direction)
		pdf[0].generated = *direction;
	tmp = object;
	while (tmp)
	{
		pdf[1] = pdf_light(tmp, rec, tmp_ray, &pdf[0].generated);
		n[1] += n[0] * pdf[1].value;
		tmp = tmp->next;
	}
	pdf[0].value = n[1];
	pdf[0].object = object;
	return (pdf[0]);
}

t_pdf	pdf_mixture(t_pdf object, t_pdf light, \
				t_ray *tmp_ray, t_hit_record *rec)
{
	t_pdf	new;

	if (light.value == 0)
		return (object);
	if (random_double(0, 1) < 0.5)
		new.generated = object.generated;
	else
		new.generated = light.generated;
	object = pdf_cosine(tmp_ray, rec, tmp_ray, &new.generated);
	light = pdf_mix_light(light.object, rec, tmp_ray, &new.generated);
	new.value = 0.5 * object.value + 0.5 * light.value;
	*tmp_ray = ray(rec->p, new.generated, random_double(0, 1));
	return (new);
}
