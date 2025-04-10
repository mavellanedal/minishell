/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:31:48 by ebalana-          #+#    #+#             */
/*   Updated: 2024/09/25 16:53:46 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_malloc(char **split, int position, size_t buffer)
{
	int		i;

	i = 0;
	split[position] = malloc(buffer);
	if (NULL == split[position])
	{
		while (i < position)
			free(split[i++]);
		free(split);
		return (1);
	}
	return (0);
}

int	fill(char **split, char const *s, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s != '\0')
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			++len;
			++s;
		}
		if (len > 0)
		{
			if (safe_malloc(split, i, len + 1))
				return (1);
			ft_strlcpy(split[i], s - len, len + 1);
		}
		++i;
	}
	return (0);
}

size_t	count_words(char const *s, char delimeter)
{
	size_t	word;
	int		word_count_inside;

	word = 0;
	while (*s != '\0')
	{
		word_count_inside = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (word_count_inside == 0)
			{
				++word;
				word_count_inside = 1;
			}
			++s;
		}
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**split;

	if (NULL == s)
		return (NULL);
	words = 0;
	words = count_words(s, c);
	split = malloc((words + 1) * sizeof(char *));
	if (NULL == split)
		return (NULL);
	split[words] = NULL;
	if (fill(split, s, c))
		return (NULL);
	return (split);
}
/*
#include <stdio.h>

int	main()
{
	char	*s = "Hola, mundo! Bienvenido a la programación.";
	char	**v;

	v = ft_split(s, ' ');
	while (*v != NULL)
	{
		printf("%s\n", *v);
		v++;
	}
}
*/
