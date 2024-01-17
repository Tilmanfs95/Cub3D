/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:29:22 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/17 17:15:55 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <stdio.h>
#include <limits.h>
#define BUFFER_SIZE 1

char	*extend_buffer(char *buffer, int *size)
{
	char	*newbuff;
	int		c;

	c = -1;
	newbuff = (char *)malloc(((*size) + BUFFER_SIZE + 1));
	if (!newbuff)
		return (NULL);
	while (++c < ((*size) + BUFFER_SIZE + 1))
		newbuff[c] = 0;
	if (buffer)
	{
		ft_memcpy(newbuff, buffer, (size_t)((*size) + 1));
		free(buffer);
	}
	*size = (*size) + BUFFER_SIZE;
	return (newbuff);
}

int	get_line(char **str, char **line, int *size)
{
	char	*ret;
	int		cursor;

	cursor = 0;
	while (*str && *(*str + cursor))
	{
		if (*(*str + cursor) == '\n')
		{
			ret = ft_substr(*str, 0, cursor + 1);
			*size = cursor + 1;
			*line = ret;
			while (*(*str + cursor))
				cursor++;
			ret = ft_substr(*str, *size, cursor - *size);
			free(*str);
			*str = ret;
			return (1);
		}
		cursor++;
	}
	*size = cursor;
	return (0);
}

int	read_file(int fd, char **buffer, int *size)
{
	int	size_read;

	size_read = 0;
	*buffer = extend_buffer(*buffer, size);
	if (!*buffer)
		return (0);
	size_read = read(fd, *buffer + ((*size) - BUFFER_SIZE), BUFFER_SIZE);
	if (size_read < 1 && !**buffer)
	{
		free(*buffer);
		*buffer = 0;
		return (0);
	}
	if (size_read < 1)
		return (0);
	*((*buffer) + ((*size) - BUFFER_SIZE) + size_read) = 0;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*sbuff;
	char		*next_line;
	int			size;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (0);
	size = 0;
	next_line = 0;
	if (get_line(&sbuff, &next_line, &size))
		return (next_line);
	while (!next_line)
	{
		if (!read_file(fd, &sbuff, &size))
		{
			next_line = sbuff;
			sbuff = 0;
			break ;
		}
		get_line(&sbuff, &next_line, &size);
	}
	return (next_line);
}
