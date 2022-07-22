/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:46 by abernita          #+#    #+#             */
/*   Updated: 2022/07/05 18:04:35 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	compute_color(int *light_color, int *obj_color)
{
	light_color[0] = (obj_color[0] * light_color[0]) / 255;
	light_color[1] = (obj_color[1] * light_color[1]) / 255;
	light_color[2] = (obj_color[2] * light_color[2]) / 255;
	if (light_color[0] > 255)
		light_color[0] = 255;
	if (light_color[1] > 255)
		light_color[1] = 255;
	if (light_color[2] > 255)
		light_color[2] = 255;
}

int	*combine_lights(double l1_c, int *l1_color, double l2_c, int *l2_color)
{
	int	*result;

	result = ft_calloc(4, sizeof(int));
	result[0] = l1_color[0] * l1_c + l2_color[0] * l2_c;
	result[1] = l1_color[1] * l1_c + l2_color[1] * l2_c;
	result[2] = l1_color[2] * l1_c + l2_color[2] * l2_c;
	if (result[0] > 255)
		result[0] = 255;
	if (result[1] > 255)
		result[1] = 255;
	if (result[2] > 255)
		result[2] = 255;
	return (result);
}

int	check_objects(t_v3 point, t_v3 light, t_objs *iter)
{
	double	dist;
	double	d_intersect;
	t_v3	to_light;

	dist = distance3(light, point);
	to_light = normalize(sub(light, point));
	d_intersect = -1;
	if (iter->type == 'p')
		d_intersect = inter_plane(point, to_light, iter);
	else if (iter->type == 's')
		d_intersect = inter_sphere(point, to_light, iter);
	else if (iter->type == 'c')
		d_intersect = inter_cylinder(point, to_light, iter);
	if (d_intersect > 0.001 && d_intersect < dist)
		return (0);
	return (1);
}

int	*resolve_color(double check, t_v3 to_light, t_scene *sc, t_objs *itsd)
{
	int	*result;

	if (check && dot_p(itsd->normal, to_light) >= 0)
		check = vcos(itsd->normal, to_light);
	else if (dot_p(itsd->normal, to_light) < 0)
		check = 0;
	result = combine_lights(sc->a_lum, sc->a_color,
			sc->f_light->params.x * check, sc->f_light->color);
	compute_color(result, itsd->color);
	return (result);
}

int	*get_color(t_v3 origin, t_v3 ray, t_objs *itsd, t_scene *sc)
{
	double	check;
	t_objs	*iter;
	t_v3	point;
	t_v3	to_light;

	if (!itsd)
		return (ft_calloc(4, sizeof(int)));
	check = 1;
	point = add_v(origin, ray);
	if (dot_p(itsd->normal, normalize(ray)) > 0)
		itsd->normal = scale_v(itsd->normal, -1);
	point = add_v(point, scale_v(normalize(itsd->normal), 0.0001));
	to_light = normalize(sub(sc->f_light->coord, point));
	iter = sc->obj_list;
	while (iter && check)
	{
		check = check_objects(point, sc->f_light->coord, iter);
		if (check != 0)
			iter = iter->next;
	}
	return (resolve_color(check, to_light, sc, itsd));
}
