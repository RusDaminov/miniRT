/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:21 by abernita          #+#    #+#             */
/*   Updated: 2022/07/06 20:24:23 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*ft_read(int fd)
{
	int		i_read;
	char	*buf;
	char	*result;

	buf = malloc(128 + 1);
	if (!buf)
		return (NULL);
	result = malloc(128 + 1);
	if (!result)
		return (NULL);
	buf[128] = '\0';
	result[0] = '\0';
	i_read = read(fd, buf, 128);
	while (i_read)
	{
		result = concat_here(result, buf, i_read);
		i_read = read(fd, buf, 128);
	}
	free(buf);
	if (i_read < 0)
		return (NULL);
	return (result);
}

int	parse_element(t_scene *sc, char *begin)
{
	if (begin[0] == 'A')
	{
		if (sc->a_lum >= 0)
			return ((sc->a_lum = -1));
		else
			return (parse_ambiance(sc, begin));
	}
	if (begin[0] == 'C' && !sc->camera)
		return (parse_camera(sc, begin));
	else if (begin[0] == 'C' && sc->camera)
		exit_program("Multiple cameras in sight\n");
	if (begin[0] == 'L')
		return (parse_light(sc, begin));
	return (parse_object(sc, begin));
}

int	parsing(char *all, t_scene *this_scene)
{
	int		i;
	char	**all_elements;

	i = -1;
	all_elements = ft_split(all, '\n');
	while (all_elements[++i])
	{
		if (all_elements[i][0])
			if (parse_element(this_scene, all_elements[i]) < 0)
				exit_program("Incorrect formatting\n");
		free(all_elements[i]);
	}
	return (free(all_elements[i]), free(all_elements), free(all), 0);
}
