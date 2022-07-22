/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:53 by abernita          #+#    #+#             */
/*   Updated: 2022/07/07 12:39:14 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	key_hook2(int key, t_scene *sc)
{
	if (key == 89)
		sc->f_light->coord.y += 0.5;
	else if (key == 92)
		sc->f_light->coord.y -= 0.5;
	else if (key == 91)
		sc->f_light->coord.z -= 0.5;
	else if (key == 87)
		sc->f_light->coord.z += 0.5;
	else if (key == 86)
		sc->f_light->coord.x += 0.5;
	else if (key == 88)
		sc->f_light->coord.x -= 0.5;
	if (key > -1 && key < 3 || key > 11 && key < 15
		|| key == 53 || key > 85 && key < 93 && key != 90)
		if (put_image(sc))
			exit_program("Invalid put image\n");
}

int	key_hook(int key, t_scene *sc)
{	
	if (key == 53)
		exit(0);
	if (key == 12)
		sc->camera->coord.y += 0.5;
	else if (key == 14)
		sc->camera->coord.y -= 0.5;
	else if (key == 13)
		sc->camera->coord.z -= 0.5;
	else if (key == 1)
		sc->camera->coord.z += 0.5;
	else if (key == 0)
		sc->camera->coord.x += 0.5;
	else if (key == 2)
		sc->camera->coord.x -= 0.5;
	key_hook2(key, sc);
}

t_scene	*init_struct(void)
{
	t_scene	*new_sc;

	new_sc = malloc(sizeof(t_scene));
	if (!new_sc)
		return (NULL);
	new_sc->up_v.x = 0;
	new_sc->up_v.z = 0;
	new_sc->a_lum = -1;
	new_sc->up_v.y = -1;
	new_sc->camera = NULL;
	new_sc->f_light = NULL;
	new_sc->obj_list = NULL;
	new_sc->width = WIDTH;
	new_sc->height = HEIGHT;
	new_sc->a_color = ft_calloc(3, sizeof(int));
	return (new_sc);
}

t_mlx_show	*init_mlx(t_scene *sc)
{
	t_mlx_show		*the_show;

	the_show = malloc(sizeof(t_mlx_show));
	if (!the_show)
		exit_program("Allocation impossible\n");
	the_show->mlx_ptr = mlx_init();
	the_show->mlx_img = mlx_new_image(the_show->mlx_ptr, sc->width, sc->height);
	the_show->data = mlx_get_data_addr(the_show->mlx_img,
			&the_show->bpp, &the_show->size_line, &the_show->endian);
	the_show->win_ptr = mlx_new_window(the_show->mlx_ptr, sc->width,
			sc->height, "miniRT");
	the_show->bpp = 600;
	return (the_show);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*file_str;
	t_scene		*sc;

	if (argc < 2 || argc > 3 || file_error(argc, argv))
		exit_program("Wrong Arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_program("No read or find file\n");
	file_str = ft_read(fd);
	if (!ft_strlen(file_str))
		exit_program("Invalid arguments\n");
	sc = init_struct();
	parsing(file_str, sc);
	check_all(sc);
	sc->the_show = init_mlx(sc);
	if (put_image(sc))
		exit_program("Invalid put image\n");
	mlx_hook(sc->the_show->win_ptr, 2, 1L, key_hook, sc);
	mlx_hook(sc->the_show->win_ptr, 17, 1L, exit_program, NULL);
	mlx_loop(sc->the_show->mlx_ptr);
	return (0);
}
