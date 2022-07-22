/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:38 by abernita          #+#    #+#             */
/*   Updated: 2022/07/05 17:44:53 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_v3	v_dup(t_v3 this)
{
	t_v3	result;

	result.x = this.x;
	result.y = this.y;
	result.z = this.z;
	return (result);
}

void	initialize_v3(t_v3 *this)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

t_objs	*push_new_object(t_objs **begin_list)
{
	t_objs	*new_one;

	new_one = malloc(sizeof(t_objs));
	if (!new_one)
		return (NULL);
	new_one->color = ft_calloc(4, sizeof(int));
	new_one->next = *begin_list;
	initialize_v3(&new_one->params);
	initialize_v3(&new_one->coord);
	initialize_v3(&new_one->or);
	*begin_list = new_one;
	return (new_one);
}

char	*get_some_i(int *things, int how_many, char *where_from)
{
	int		i;

	i = 0;
	while (i < how_many)
	{
		things[i] = (int) ft_atof(where_from);
		where_from = advance_through(where_from);
		i++;
	}
	if (ft_isspace(*where_from) || *where_from == '\n' || *where_from == '\0')
		return (where_from);
	return (NULL);
}

char	*get_some_d(t_v3 *things, int how_many, char *where_from)
{
	if (how_many)
	{
		things->x = ft_atof(where_from);
		where_from = advance_through(where_from);
	}
	if (how_many > 1)
	{
		things->y = ft_atof(where_from);
		where_from = advance_through(where_from);
	}
	if (how_many > 2)
	{
		things->z = ft_atof(where_from);
		where_from = advance_through(where_from);
	}
	if (ft_isspace(*where_from) || *where_from == '\n' || *where_from == '\0')
	{
		return (where_from);
	}
	return (NULL);
}
