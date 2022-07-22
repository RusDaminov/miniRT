/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:44 by abernita          #+#    #+#             */
/*   Updated: 2022/07/05 14:40:47 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_v3	cross_product(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.y * other.z - one.z * other.y;
	result.y = one.z * other.x - one.x * other.z;
	result.z = one.x * other.y - one.y * other.x;
	return (result);
}

t_v3	scale_v(t_v3 v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

double	dot_p(t_v3 one, t_v3 other)
{
	return (one.x * other.x + one.y * other.y + one.z * other.z);
}

t_v3	sub(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.x - other.x;
	result.y = one.y - other.y;
	result.z = one.z - other.z;
	return (result);
}

t_v3	add_v(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.x + other.x;
	result.y = one.y + other.y;
	result.z = one.z + other.z;
	return (result);
}
