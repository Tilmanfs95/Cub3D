/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:50:10 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/31 18:38:31 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_space(char c)
{
	if (c == ' '
		|| c == '\n'
		|| c == '\t')
		return (1);
	return (0);
}

int	get_no_space_length(char *str)
{
	int	cursor;
	int	length;

	cursor = 0;
	length = 0;
	while (str[cursor])
	{
		if (!check_space(str[cursor]))
			length++;
		cursor++;
	}
	return (length);
}

int	remove_spaces(char **str)
{
	size_t	cursor;
	size_t	buff_cursor;
	char	*buff;

	cursor = -1;
	buff_cursor = get_no_space_length(*str);
	if (buff_cursor == ft_strlen(*str))
		return (1);
	if (buff_cursor < 1)
		return (0);
	buff = (char *)ft_calloc(buff_cursor + 1, 1);
	if (!buff)
		return (0);
	buff_cursor = 0;
	while (str[0][++cursor])
	{
		if (!check_space(str[0][cursor]))
			buff[buff_cursor++] = str[0][cursor];
	}
	free(*str);
	*str = buff;
	return (1);
}

bool	has_file_type(char *str, char *type)
{
	if (ft_strlen(str) < ft_strlen(type) + 1)
		return (false);
	str += ft_strlen(str) - ft_strlen(type);
	if (!ft_strncmp(str, type, ft_strlen(type)))
		return (true);
	return (false);
}
