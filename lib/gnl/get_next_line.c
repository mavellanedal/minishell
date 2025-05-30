/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:45:12 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 18:09:29 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

char	*newline(char *box)
{
	int		i;
	char	*line;

	i = 0;
	if (!box[i])
		return (NULL);
	while (box[i] && box[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (box[i] && box[i] != '\n')
	{
		line[i] = box[i];
		i++;
	}
	if (box[i] == '\n')
	{
		line[i] = box[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_box(char *box)
{
	int		i;
	int		j;
	char	*newbox;

	i = 0;
	if (!box)
		return (NULL);
	while (box[i] != '\0' && box[i] != '\n')
		i++;
	if (!box[i])
	{
		free(box);
		box = NULL;
		return (NULL);
	}
	newbox = (char *)malloc((ft_strlen(box) - i + 1) * sizeof(char));
	if (!newbox)
		return (NULL);
	i++;
	j = 0;
	while (box[i])
		newbox[j++] = box[i++];
	newbox[j] = '\0';
	free(box);
	return (newbox);
}

char	*read_file(int fd, char *box)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(box, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(box);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		box = ft_strjoin_gnl(box, buffer);
	}
	free(buffer);
	return (box);
}

char	*get_next_line(int fd)
{
	static char	*box[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	box[fd] = read_file(fd, box[fd]);
	if (!box[fd])
		return (NULL);
	line = newline(box[fd]);
	box[fd] = update_box(box[fd]);
	return (line);
}
/*
int main()
{
    int fd1 = open("moltes_lineas", O_RDONLY);
    int fd2 = open("42_with_nl", O_RDONLY);
    int fd3 = open("bigline", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        printf("Error al abrir uno o más archivos\n");
        return (1);
    }

    char *line1 = NULL;
    char *line2 = NULL;
    char *line3 = NULL;

    int reading = 1;
    while (reading)
    {
        reading = 0;
        line1 = get_next_line(fd1);
        if (line1)
        {
            printf("Línea de file1: %s", line1);
            free(line1);
            reading = 1;
        }
        line2 = get_next_line(fd2);
        if (line2)
        {
            printf("Línea de file2: %s", line2);
            free(line2);
            reading = 1;
        }
        line3 = get_next_line(fd3);
        if (line3)
        {
            printf("Línea de file3: %s", line3);
            free(line3);
            reading = 1;
        }
    }

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
*/
