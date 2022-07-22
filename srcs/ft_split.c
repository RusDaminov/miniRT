/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abernita <abernita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:39:28 by abernita          #+#    #+#             */
/*   Updated: 2022/07/07 12:38:24 by abernita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	words;
	int	first;

	if (!str)
		return (-1);
	i = 0;
	first = 1;
	words = 0;
	while (str[i])
	{
		if (str[i] == c)
			first = 1;
		else
		{
			if (first)
				words++;
			first = 0;
		}
		i++;
	}
	return (words);
}

static char	**first_alloc(char const *s, char c, int *w)
{
	int		words;
	char	**res;

	*w = 0;
	words = count_words((char *)s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res[words] = NULL;
	return (res);
}

static int	size_word(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i + j] != c && s[i + j])
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**res;

	res = first_alloc(s, c, &words);
	if (!s || !res)
		return (0);
	i = -1;
	while (*(s + ++i))
	{
		if (s[i] != c)
		{
			res[words] = malloc(sizeof(char) * (size_word(s, i, c) + 1));
			if (!res[words])
				return (NULL);
			j = -1;
			while (s[i + ++j] != c && s[i + j])
				res[words][j] = s[i + j];
			res[words][j] = '\0';
			words++;
			i = i + j - 1;
		}
	}
	return (res);
}
