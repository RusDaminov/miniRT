/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calculs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:58 by abernita          #+#    #+#             */
/*   Updated: 2022/07/05 14:40:00 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	distance3(t_v3 one, t_v3 other)
{
	return (sqrt(pow(one.x - other.x, 2) + pow(one.y - other.y, 2)
			+ pow(one.z - other.z, 2)));
}

t_v3	normalize(t_v3 these3)
{
	double	max;

	max = sqrt(dot_p(these3, these3));
	these3.x = these3.x / max;
	these3.y = these3.y / max;
	these3.z = these3.z / max;
	return (these3);
}

double	mod(t_v3 v)
{
	return (sqrt(dot_p(v, v)));
}

double	vcos(t_v3 a, t_v3 b)
{
	return (dot_p(a, b) / (mod(a) * mod(b)));
}

t_v3	rotate_cam(t_v3 org, t_v3 trans, t_v3 up_v)
{
	t_v3	x_axis;
	t_v3	y_axis;
	t_v3	z_axis;
	t_v3	result;

	z_axis = trans;
	if (trans.y != 1 && trans.y != -1)
		x_axis = cross_product(up_v, z_axis);
	else
	{
		x_axis.x = trans.y;
		x_axis.y = 0;
		x_axis.z = 0;
	}
	y_axis = cross_product(z_axis, x_axis);
	result.x = org.x * x_axis.x + org.y * y_axis.x + org.z * z_axis.x;
	result.y = org.x * x_axis.y + org.y * y_axis.y + org.z * z_axis.y;
	result.z = org.x * x_axis.z + org.y * y_axis.z + org.z * z_axis.z;
	return (result);
}
