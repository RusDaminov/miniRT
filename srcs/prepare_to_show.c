/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:04 by abernita          #+#    #+#             */
/*   Updated: 2022/07/06 20:24:42 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	fill_pixel(t_mlx_show *the_show, int x, int y, int *color)
{
	int	i;

	i = (x * 4)
		+ (y * the_show->size_line);
	the_show->data[i] = color[2];
	the_show->data[++i] = color[1];
	the_show->data[++i] = color[0];
	the_show->data[++i] = color[3];
	free(color);
}

int	*find_pixel(t_v3 origin, t_v3 ray, t_scene *sc)
{
	double	dist;
	double	closest;
	t_objs	*iter;
	t_objs	*intersected;

	closest = 2147483647;
	iter = sc->obj_list;
	intersected = NULL;
	while (iter)
	{
		if (iter->type == 's')
			dist = inter_sphere(origin, ray, iter);
		else if (iter->type == 'p')
			dist = inter_plane(origin, ray, iter);
		else if (iter->type == 'c')
			dist = inter_cylinder(origin, ray, iter);
		if (dist > 0.0001 && dist < closest)
		{
			closest = dist;
			intersected = iter;
		}
		iter = iter->next;
	}
	return (get_color(origin, scale_v(ray, closest), intersected, sc));
}

int	fill_the_image(t_scene *sc, t_mlx_show *the_show)
{
	int		x_i;
	int		y_i;
	double	fov;
	t_v3	ray_i;

	x_i = -1;
	fov = sc->camera->params.x;
	while (++x_i < sc->width)
	{
		y_i = -1;
		while (++y_i < sc->height)
		{
			ray_i.x = sc->width / 2 - x_i;
			ray_i.y = y_i - sc->height / 2;
			ray_i.z = sc->width / 2 / tan(fov);
			ray_i = rotate_cam(normalize(ray_i), sc->camera->or, sc->up_v);
			fill_pixel(the_show, x_i, y_i,
				find_pixel(sc->camera->coord, ray_i, sc));
		}
	}
	return (1);
}

int	put_image(t_scene *sc)
{
	if (!sc)
		return (1);
	if (!sc->the_show)
		return (1);
	if (!fill_the_image(sc, sc->the_show))
		return (1);
	mlx_clear_window(sc->the_show->mlx_ptr, sc->the_show->win_ptr);
	mlx_put_image_to_window(sc->the_show->mlx_ptr, sc->the_show->win_ptr,
		sc->the_show->mlx_img, 0, 0);
	return (0);
}

void	check_all(t_scene *sc)
{
	t_objs		*it;
	t_v3		aux;

	check_parse(sc);
	if (color_error(sc->a_color) || color_error(sc->f_light->color))
		exit_program("Wrong color formatting\n");
	if (sc->a_lum < 0 || sc->a_lum > 1)
		exit_program("Ambiance light error\n");
	initialize_v3(&aux);
	if (distance3(sc->camera->or, aux) > 1
		|| distance3(sc->camera->or, aux) < -1
		|| distance3(sc->camera->or, aux) == 0
		|| sc->camera->params.x < 0 || sc->camera->params.x > M_PI)
		exit_program("Camera error\n");
	if (sc->f_light->params.x < 0 || sc->f_light->params.x > 1
		|| color_error(sc->f_light->color))
		exit_program("Wrong focused light parmeters\n");
	it = sc->obj_list;
	while (it)
	{
		if (object_error(it))
			exit_program("Object formatting error\n");
		it = it->next;
	}
}
