/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:38:03 by abernita          #+#    #+#             */
/*   Updated: 2022/07/07 18:45:08 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 800
# define HEIGHT 600

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minilibx/mlx.h"

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_show
{
	char			*data;
	int				bpp;
	int				endian;
	int				size_line;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlx_img;
}	t_mlx_show;

typedef struct s_objs
{
	char			type;
	int				*color;
	t_v3			or;
	t_v3			coord;
	t_v3			params;
	t_v3			normal;
	struct s_objs	*next;
}	t_objs;

typedef struct scene
{
	int				width;
	int				height;
	int				*a_color;
	double			a_lum;
	t_v3			up_v;
	t_objs			*camera;
	t_objs			*f_light;
	t_objs			*obj_list;
	t_mlx_show		*the_show;
}	t_scene;

void			check_all(t_scene *sc);
void			check_parse(t_scene *sc);
void			initialize_v3(t_v3 *this);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t nmemb, size_t size);

char			*ft_read(int fd);
char			*advance_through(char *this);
char			**ft_split(char const *s, char c);
char			*concat_here(char *str1, char *str2, int read);
char			*get_some_i(int *things, int how_many, char *where_from);
char			*get_some_d(t_v3 *things, int how_many, char *where_from);

double			vcos(t_v3 a, t_v3 b);
double			ft_atof(const char *str);
double			dot_p(t_v3 one, t_v3 other);
double			distance3(t_v3 one, t_v3 other);
double			inter_plane(t_v3 origin, t_v3 ray, t_objs *object);
double			inter_sphere(t_v3 origin, t_v3 ray, t_objs *object);
double			inter_cylinder(t_v3 origin, t_v3 ray, t_objs *object);
double			compute_plane(t_v3 origin, t_v3 ray, t_objs *obj, int proc);

t_v3			v_dup(t_v3 this);
t_v3			normalize(t_v3 these3);
t_v3			scale_v(t_v3 v, double n);
t_v3			sub(t_v3 one, t_v3 other);
t_v3			add_v(t_v3 one, t_v3 other);
t_v3			cross_product(t_v3 one, t_v3 other);
t_v3			rotate_cam(t_v3 origin, t_v3 trans, t_v3 up_v);
t_objs			*push_new_object(t_objs **begin_list);

int				ft_isspace(char c);
int				color_error(int *col);
int				put_image(t_scene *sc);
int				exit_program(char *str);
int				object_error(t_objs *this);
int				file_error(int argc, char **argv);
int				parse_light(t_scene *sc, char *begin);
int				parse_camera(t_scene *sc, char *begin);
int				parse_object(t_scene *sc, char *begin);
int				key_hook(int key, t_scene *sc);
int				parsing(char *all, t_scene	*this_scene);
int				parse_ambiance(t_scene *sc, char *begin);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				*get_color(t_v3 origin, t_v3 ray, t_objs *inter, t_scene *sc);
size_t			ft_strlen(const char *s);

#endif
