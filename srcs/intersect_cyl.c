/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:35 by abernita          #+#    #+#             */
/*   Updated: 2022/07/07 13:29:31 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	cy_calculs(t_v3 origin, t_v3 ray, t_objs *obj, double x[2])
{
	t_v3	v;
	t_v3	u;
	double	a;
	double	b;
	double	c;

	v = scale_v(obj->or, dot_p(ray, obj->or));
	v = sub(ray, v);
	a = dot_p(sub(origin, obj->coord), obj->or);
	u = scale_v(obj->or, a);
	u = sub(sub(origin, obj->coord), u);
	a = dot_p(v, v);
	b = 2 * dot_p(v, u);
	c = dot_p(u, u) - pow(obj->params.x / 2, 2);
	x[0] = (sqrt(pow(b, 2) - 4 * a * c) - b) / (2 * a);
	x[1] = (-sqrt(pow(b, 2) - 4 * a * c) - b) / (2 * a);
	return (1);
}

double	best_body(double dist[2], double x[2], t_objs *obj)
{
	if (!((dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001)
			|| (dist[1] >= 0 && dist[1] <= obj->params.y && x[1] > 0.001)))
		return (-1);
	if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001
		&& dist[1] >= 0 && dist[1] <= obj->params.y && x[1] > 0.001)
	{
		if (x[0] < x[1])
			return (x[0]);
		else
			return (x[1]);
	}
	else if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001)
		return (x[0]);
	else if (dist[1] >= 0 && dist[1] <= obj->params.y && x[1] > 0.001)
		return (x[1]);
	else
		return (-1);
}

double	check_caps(t_v3 origin, t_v3 ray, t_objs *obj, t_v3 ccc)
{
	double	dd;
	t_v3	aux;

	if (ccc.x == obj->coord.x && ccc.y == obj->coord.y)
		dd = compute_plane(origin, ray, obj, 0);
	else
		dd = compute_plane(origin, ray, obj, 1);
	if (dd < 0.001)
		return (-1);
	aux = add_v(origin, scale_v(ray, dd));
	if (dd > 0.001 && distance3(aux, ccc) <= obj->params.x / 2)
		return (dd);
	else
		return (-1);
}

double	best_with_caps(t_v3 origin, t_v3 ray, t_objs *obj, double it_b)
{
	double	caps;
	double	dd[2];
	t_v3	ccc;

	dd[0] = check_caps(origin, ray, obj, obj->coord);
	ccc = add_v(obj->coord, (scale_v(obj->or, obj->params.y)));
	dd[1] = check_caps(origin, ray, obj, ccc);
	caps = -1;
	if (dd[0] > 0.001 && (dd[0] < dd[1] || dd[1] < 0.001))
		caps = dd[0];
	else if (dd[1] > 0.001 && (dd[1] < dd[0] || dd[0] < 0.001))
		caps = dd[1];
	if (caps < 0.001 && it_b < 0.001)
		return (-1);
	if (caps > 0.001 && (caps < it_b || it_b < 0.001))
	{
		obj->normal = v_dup(obj->or);
		return (caps);
	}
	return (it_b);
}

double	inter_cylinder(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	x[2];
	double	dist[2];
	double	body_it;

	cy_calculs(origin, ray, obj, x);
	dist[0] = dot_p(obj->or, sub(scale_v(ray, x[0]), sub(obj->coord, origin)));
	dist[1] = dot_p(obj->or, sub(scale_v(ray, x[1]), sub(obj->coord, origin)));
	body_it = best_body(dist, x, obj);
	if (body_it == x[0])
		obj->normal = normalize(sub(add_v(origin, scale_v(ray, x[0])),
					add_v(obj->coord, scale_v(obj->or, dist[0]))));
	else if (body_it == x[1])
		obj->normal = normalize(sub(add_v(origin, scale_v(ray, x[1])),
					add_v(obj->coord, scale_v(obj->or, dist[1]))));
	return (body_it);
}
