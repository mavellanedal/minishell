/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:59:26 by ebalana-          #+#    #+#             */
/*   Updated: 2025/04/30 17:13:32 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char)c)
// 		{
// 			return ((char *)&s[i]);
// 		}
// 		i++;
// 	}
// 	if ((unsigned char)c == '\0')
// 	{
// 		return ((char *)&s[i]);
// 	}
// 	return (NULL);
// }

char	*ft_strjoin_gnl(char *box, char *buffer)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	if (!box)
	{
		box = (char *)malloc(1 * sizeof(char));
		box[0] = '\0';
	}
	if (!box || !buffer)
		return (NULL);
	sizetotal = ft_strlen(box) + ft_strlen(buffer);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (box[++i] != 0)
		res[i] = box[i];
	j = 0;
	while (buffer[j] != 0)
		res[i++] = buffer[j++];
	res[sizetotal] = 0;
	free(box);
	return (res);
}
