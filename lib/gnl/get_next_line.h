/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <ebalana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:59:59 by ebalana-          #+#    #+#             */
/*   Updated: 2025/05/29 18:10:33 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>   // Para open
# include <unistd.h>  // Para read, close
# include <stdio.h>   // Para printf
# include <stdlib.h>  // Para malloc

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_file(int fd, char *box);
char	*newline(char *box);
char	*update_box(char *box);

char	*ft_strjoin_gnl(char *box, char *buffer);

#endif
