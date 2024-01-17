/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:04:58 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/29 18:58:09 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	copy_line(char *str, int *arr)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '\n')
	{
		if (ft_isdigit(str[index]))
			arr[index] = str[index] - '0';
		else
			arr[index] = str[index];
		index++;
	}
}

bool	validate_map_border(t_map_container *world_map)
{
	int	cursor_y;
	int	cursor_x;

	cursor_y = -1;
	while (++cursor_y < world_map->map_height)
	{
		cursor_x = -1;
		while (++cursor_x < world_map->map_width)
		{
			if (cursor_x && cursor_x < world_map->map_width - 1
				&& cursor_y && cursor_y < world_map->map_height - 1)
			{
				if (world_map->map_array[cursor_y][cursor_x] != 0)
					continue ;
				if (world_map->map_array[cursor_y][cursor_x - 1] == MCTNUM
					|| world_map->map_array[cursor_y][cursor_x + 1] == MCTNUM
					|| world_map->map_array[cursor_y - 1][cursor_x] == MCTNUM
					|| world_map->map_array[cursor_y + 1][cursor_x] == MCTNUM)
					return (false);
			}
		}
	}
	return (true);
}

bool	valid_num(int i)
{
	if (i == 0
		|| i == 1)
		return (true);
	return (false);
}

bool	validate_map(t_map_container *world_map)
{
	int	cursor_y;
	int	cursor_x;

	cursor_y = -1;
	while (++cursor_y < world_map->map_height)
	{
		cursor_x = -1;
		while (++cursor_x < world_map->map_width)
		{
			if (!valid_num(world_map->map_array[cursor_y][cursor_x]))
				return (false);
		}
	}
	return (true);
}

void	free_ptr_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
