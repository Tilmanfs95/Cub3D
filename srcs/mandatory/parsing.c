/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:52:10 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/31 16:51:15 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	get_player_dir(char c)
{
	if (c == 'N')
		return (-90.f);
	if (c == 'W')
		return (180.f);
	if (c == 'S')
		return (90.f);
	if (c == 'E')
		return (0.f);
	return (-420);
}

bool	parse_player_info(t_map_container *world_map)
{
	int		cursor_y;
	int		cursor_x;

	cursor_y = -1;
	while (++cursor_y < world_map->map_height)
	{
		cursor_x = -1;
		while (++cursor_x < world_map->map_width)
		{
			if (get_player_dir(world_map->map_array[cursor_y][cursor_x])
				!= -420)
			{
				world_map->header.player.pos = (t_point){cursor_x, cursor_y};
				world_map->header.player.dir
					= get_player_dir(world_map->map_array[cursor_y][cursor_x]);
				world_map->map_array[cursor_y][cursor_x] = 0;
				return (true);
			}
		}
	}
	return (false);
}

void	clean_map(t_map_container *world_map)
{
	int	cursor_y;
	int	cursor_x;

	cursor_y = -1;
	while (++cursor_y < world_map->map_height)
	{
		cursor_x = -1;
		while (++cursor_x < world_map->map_width)
		{
			if (world_map->map_array[cursor_y][cursor_x] == MCTNUM)
				world_map->map_array[cursor_y][cursor_x] = 1;
		}
	}
}

bool	load_map(t_map_container *world_map, int fd)
{
	t_list	*map_data;

	map_data = NULL;
	if (!world_map)
		return (false);
	if (!parse_map_header(&world_map->header, fd))
		return (printf("Error\nInvalid Map Header\n"), false);
	read_map(world_map, &map_data, fd);
	if (!parse_map(world_map, &map_data))
		return (false);
	if (!parse_player_info(world_map))
	{
		printf("Error\nNo player postion\n");
		return (free_ptr_array((void **)world_map->map_array), false);
	}
	if (!validate_map_border(world_map))
		return (printf("Error\nMap invalid\n"), \
free_ptr_array((void **)world_map->map_array), false);
	clean_map(world_map);
	if (!validate_map(world_map))
		return (printf("Error\nMap invalid\n"), \
free_ptr_array((void **)world_map->map_array), false);
	return (true);
}
