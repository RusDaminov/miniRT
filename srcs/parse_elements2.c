/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:17 by abernita          #+#    #+#             */
/*   Updated: 2022/07/06 10:53:29 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	parse_ambiance(t_scene *sc, char *begin)
{
	char	*it;

	it = begin + 1;
	sc->a_lum = ft_atof(it);
	it = advance_through(it);
	sc->a_color[0] = (int)ft_atof(it);
	it = advance_through(it);
	sc->a_color[1] = (int)ft_atof(it);
	it = advance_through(it);
	sc->a_color[2] = (int)ft_atof(it);
	it = advance_through(it);
	while (*it == ' ')
		it++;
	if (!*it)
		return (1);
	else
		return (-1);
}

int	parse_camera(t_scene *sc, char *begin)
{
	char	*it;
	t_objs	*this_obj;

	sc->camera = push_new_object(&(sc->camera));
	if (!sc->camera)
		return (-1);
	this_obj = sc->camera;
	this_obj->type = 'C';
	it = get_some_d(&this_obj->coord, 3, begin + 1);
	if (!it)
		return (-1);
	it = get_some_d(&this_obj->or, 3, it);
	if (!it)
		return (-1);
	it = get_some_d(&this_obj->params, 1, it);
	this_obj->params.x = this_obj->params.x * M_PI / 180 / 2;
	if (!it)
		return (-1);
	if (this_obj->or.x == 0 && this_obj->or.y == 0 && this_obj->or.z == 0)
		this_obj->or.z = 1;
	return (1);
}

int	parse_light(t_scene *sc, char *begin)
{
	char	*it;
	t_objs	*this_obj;

	this_obj = push_new_object(&(sc->f_light));
	if (!this_obj)
		return (0);
	sc->f_light = this_obj;
	this_obj->type = 'L';
	it = get_some_d(&this_obj->coord, 3, begin + 1);
	if (!it)
		return (-1);
	it = get_some_d(&this_obj->params, 1, it);
	if (!it)
		return (-1);
	it = get_some_i(this_obj->color, 3, it);
	if (!it)
		return (-41);
	if (this_obj->or.x > 255 || this_obj->or.x < 0
		|| this_obj->or.y > 255 || this_obj->or.y < 0
		|| this_obj->or.z > 255 || this_obj->or.z < 0
		|| this_obj->params.x < 0 || this_obj->params.x > 1)
		return (-1);
	return (1);
}
