/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:00:32 by mkneisl           #+#    #+#             */
/*   Updated: 2023/03/31 18:28:03 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	valid_num_str(char *str)
{
	int	cursor;
	int	d_count;
	int	n_count;

	d_count = 0;
	n_count = 0;
	cursor = -1;
	while (ft_isdigit(str[++cursor]))
		d_count++;
	if (!d_count || d_count > 3 || str[cursor] != ',')
		return (false);
	n_count++;
	d_count = 0;
	while (ft_isdigit(str[++cursor]))
		d_count++;
	if (!d_count || d_count > 3 || str[cursor] != ',')
		return (false);
	n_count++;
	d_count = 0;
	while (ft_isdigit(str[++cursor]))
		d_count++;
	n_count++;
	return (d_count && d_count <= 3 && str[cursor] == 0 && n_count == 3);
}

bool	parse_color(char *clr_str, int32_t *color)
{
	char	**parts;
	int		val;

	if (!valid_num_str(clr_str))
		return (false);
	parts = ft_split_str(clr_str, "\t \n,");
	if (!parts)
		return (false);
	if (!parts[0])
		return (free(parts), false);
	val = ft_atoi(parts[0]);
	if (val > 255 || val < 0 || !parts[1])
		return (free_ptr_array((void **)parts), 0);
	*((unsigned char *)color + 3) = (unsigned char)val;
	val = ft_atoi(parts[1]);
	if (val > 255 || val < 0 || !parts[2])
		return (free_ptr_array((void **)parts), 0);
	*(((unsigned char *)color) + 2) = (unsigned char)val;
	val = ft_atoi(parts[2]);
	if (val > 255 || val < 0)
		return (free_ptr_array((void **)parts), 0);
	*(((unsigned char *)color) + 1) = (unsigned char)val;
	*(((unsigned char *)color)) = 255;
	free_ptr_array((void **)parts);
	return (true);
}

bool	parse_texture(char *texture_path, mlx_texture_t **texture)
{
	if (!texture_path || ft_strlen(texture_path) < 5)
		return (false);
	*texture = 0;
	if (has_file_type(texture_path, ".png"))
		*texture = mlx_load_png(texture_path);
	return (*texture);
}

bool	parse_line_content(t_map_header *map_header, char *line, bool *status)
{
	line = ft_strdup(line);
	remove_spaces(&line);
	if (!ft_strncmp("NO", line, 2))
		*status = parse_texture(line + 2, &map_header->north_tex);
	else if (!ft_strncmp("SO", line, 2))
		*status = parse_texture(line + 2, &map_header->south_tex);
	else if (!ft_strncmp("WE", line, 2))
		*status = parse_texture(line + 2, &map_header->west_tex);
	else if (!ft_strncmp("EA", line, 2))
		*status = parse_texture(line + 2, &map_header->east_tex);
	else if (!ft_strncmp("F", line, 1))
		*status = parse_color(line + 1, &map_header->floor_color);
	else if (!ft_strncmp("C", line, 1))
		*status = parse_color(line + 1, &map_header->sky_color);
	else
		return (free(line), false);
	free(line);
	return (true);
}

bool	parse_map_header(t_map_header *map_header, int fd)
{
	char	*line;
	bool	status;
	int		parsed;

	if (!map_header)
		return (false);
	parsed = 0;
	while (parsed < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (!parse_line_content(map_header, line, &status))
		{
			free(line);
			continue ;
		}
		free(line);
		parsed++;
		if (!status)
			return (false);
	}
	return (true);
}
