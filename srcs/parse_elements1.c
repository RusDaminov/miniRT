/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:09 by abernita          #+#    #+#             */
/*   Updated: 2022/07/06 20:24:54 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*parse_cylinder(char *begin, t_objs *ob)
{
	char	*it;

	it = get_some_d(&ob->or, 3, begin);
	if (!it)
		return (NULL);
	ob->or = normalize(ob->or);
	it = get_some_d(&ob->params, 2, it);
	if (!it)
		return (NULL);
	it = get_some_i(ob->color, 3, it);
	if (!it)
		return (NULL);
	ob->type = 'c';
	return (it);
}

char	*parse_plane(char *begin, t_objs *ob)
{
	char	*it;

	it = get_some_d(&ob->or, 3, begin);
	ob->or = normalize(ob->or);
	if (!it)
		return (NULL);
	it = get_some_i(ob->color, 3, it);
	if (!it)
		return (NULL);
	ob->type = 'p';
	return (it);
}

char	*parse_sphere(char *begin, t_objs *ob)
{
	char	*it;

	it = get_some_d(&ob->params, 1, begin);
	if (!it)
		return (NULL);
	it = get_some_i(ob->color, 3, it);
	if (!it)
		return (NULL);
	ob->type = 's';
	return (it);
}

int	parse_object(t_scene *sc, char *begin)
{
	char	*it;
	t_objs	*ob;

	if ((ft_strncmp(begin, "sp", 2) && ft_strncmp(begin, "pl", 2)
			&& ft_strncmp(begin, "cy", 2)) || !ft_isspace(begin[2]))
		exit_program("unknown element\n");
	ob = push_new_object(&(sc->obj_list));
	if (!ob)
		return (-1);
	it = get_some_d(&ob->coord, 3, begin + 2);
	if (!it)
		return (-1);
	if (!ft_strncmp(begin, "cy", 2))
		it = parse_cylinder(it, ob);
	else if (!ft_strncmp(begin, "pl", 2))
		it = parse_plane(it, ob);
	else if (!ft_strncmp(begin, "sp", 2))
		it = parse_sphere(it, ob);
	if (!it)
		return (-1);
	return (1);
}
