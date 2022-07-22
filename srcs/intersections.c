/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:40 by abernita          #+#    #+#             */
/*   Updated: 2022/07/05 18:07:51 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	inter_sphere(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	closer;
	double	inter_p[2];
	t_v3	k;
	t_v3	aux;

	aux = sub(origin, obj->coord);
	k.x = dot_p(ray, ray);
	k.y = 2 * dot_p(ray, aux);
	k.z = dot_p(aux, aux) - ((obj->params.x / 2) * (obj->params.x / 2));
	closer = k.y * k.y - (4 * k.x * k.z);
	if (closer < 0)
		return (-1);
	inter_p[0] = (sqrt(closer) - k.y) / (2 * k.x);
	inter_p[1] = (-sqrt(closer) - k.y) / (2 * k.x);
	if (inter_p[0] > 0.0001 && (inter_p[0] < inter_p[1] || inter_p[1] < 0))
		closer = inter_p[0];
	else if (inter_p[1] > 0.0001)
		closer = inter_p[1];
	else
		return (-1);
	obj->normal = normalize(sub(add_v(origin, scale_v(ray, closer)),
				obj->coord));
	return (closer);
}

double	inter_plane(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	x;
	double	denom;
	t_v3	aux;

	denom = dot_p(obj->or, ray);
	if (denom == 0)
		return (-1);
	aux = sub(obj->coord, origin);
	x = dot_p(obj->or, aux) / denom;
	obj->normal = normalize(v_dup(obj->or));
	if (x < 0.001)
		return (-1);
	return (x);
}

double	compute_plane(t_v3 origin, t_v3 ray, t_objs *obj, int proc)
{
	double	dd;
	t_v3	aux3;

	if (proc == 1)
		aux3 = add_v(obj->coord, scale_v(obj->or, obj->params.y));
	else
		aux3 = v_dup(obj->coord);
	dd = dot_p(obj->or, ray);
	if (!dd)
		dd = -1;
	else
		dd = dot_p(obj->or, sub(aux3, origin)) / dd;
	return (dd);
}
