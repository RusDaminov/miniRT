/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:40:31 by abernita          #+#    #+#             */
/*   Updated: 2022/07/06 20:23:59 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

double	ft_atof(const char *str)
{
	int		i;
	int		aux;
	int		sign;
	double	number;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return ((double)number * sign);
	aux = 10;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		number = number + (double)(str[i] - '0') / aux;
		aux = aux * 10;
	}
	return ((double)number * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	while (*(s + size))
		size++;
	write(fd, s, size);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if ((!s1 && !s2) || n == 0)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (p1[i] != '\0' && p2[i] != '\0' && i < n - 1
		&& p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}
