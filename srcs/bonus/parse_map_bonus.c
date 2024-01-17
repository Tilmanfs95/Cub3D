/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:17:48 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/31 15:34:30 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	**new_map(int width, int height, int def)
{
	int	cursor;
	int	**tmp_map;

	cursor = -1;
	tmp_map = ft_calloc(height + 1, sizeof(void *));
	if (!tmp_map)
		return (NULL);
	tmp_map[0] = ft_calloc(width + 1, sizeof(int));
	if (!tmp_map[0])
		return (free_ptr_array((void **)tmp_map), NULL);
	while (cursor++ < width)
		tmp_map[0][cursor] = def;
	cursor = 0;
	while (++cursor < height)
	{
		tmp_map[cursor] = ft_calloc(width + 1, sizeof(int));
		if (!tmp_map[cursor])
			return (free_ptr_array((void **)tmp_map), NULL);
		ft_memcpy(tmp_map[cursor], tmp_map[0], width * sizeof(int));
	}
	return (tmp_map);
}

bool	parse_map(t_map_container *world_map, t_list **list)
{
	int		**tmp_map;
	t_list	*node;
	int		cursor;

	cursor = -1;
	node = *list;
	world_map->map_width += 2;
	world_map->map_height += 2;
	tmp_map = new_map(world_map->map_width, world_map->map_height, MCTNUM);
	if (!tmp_map)
		return (ft_lstclear(list, free), false);
	cursor = 1;
	while (node)
	{
		copy_line((char *)node->content, &tmp_map[cursor][1]);
		node = node->next;
		cursor++;
	}
	world_map->map_array = tmp_map;
	ft_lstclear(list, free);
	return (true);
}

void	add_map_line(t_map_container *world_map, t_list	**list, char **line)
{
	replace_all(line, "\t", "    ");
	replace_all(line, " ", "1");
	replace_all(line, "\n", "\0");
	if ((int)ft_strlen(*line) > world_map->map_width)
		world_map->map_width = ft_strlen(*line);
	ft_lstadd_back(list, ft_lstnew((void *)*line));
	world_map->map_height++;
}

void	read_map(t_map_container *world_map, t_list	**list, int fd)
{
	char	*line;
	bool	go;

	go = false;
	world_map->map_height = 0;
	world_map->map_width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
		{
			if (!go)
			{
				free(line);
				continue ;
			}
			else
				return (free(line));
		}
		go = true;
		add_map_line(world_map, list, &line);
	}
}
