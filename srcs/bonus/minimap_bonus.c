/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:02:22 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/31 16:45:55 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// draw the green lines which present the players view direction / angle
void	draw_player_dir(t_uni *uni)
{
	double			x;
	double			y;
	double			dir;
	double			wall_dist;
	int				i;

	i = 0;
	dir = twist_dir(uni->player.dir, -uni->view_angle / 2);
	while (i <= (int)uni->view_angle)
	{
		wall_dist = dist_to_wall(uni, dir);
		x = uni->m_map.px_per_block * uni->player.pos.x;
		y = uni->m_map.px_per_block * uni->player.pos.y;
		draw_line(uni->m_map.sight, (struct s_point){x, y},
			get_point_in_dir((struct s_point){x, y},
				dir, uni->m_map.px_per_block * wall_dist),
			create_color(0, 255, 0, 255));
		dir = twist_dir(dir, 1);
		i++;
	}
}

// loop-hook to draw the players position
void	draw_player_hook(void *param)
{
	t_uni			*uni;

	uni = param;
	clear_image(uni->m_map.sight);
	mlx_draw_texture(uni->m_map.sight, uni->m_map.player,
		uni->m_map.px_per_block * uni->player.pos.x - 5,
		uni->m_map.px_per_block * uni->player.pos.y - 5);
	draw_player_dir(uni);
}

// draw a wall block at the minimap
void	draw_block(t_uni *uni, int pos_x, int pos_y, int32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < uni->m_map.px_per_block)
	{
		j = -1;
		while (++j < uni->m_map.px_per_block)
			mlx_put_pixel(uni->m_map.walls, pos_x + i, pos_y + j, color);
		i++;
	}
}

// load (and display) the needed images and textures
void	init_map_images(t_uni *uni)
{
	int	inst;

	uni->m_map.walls = mlx_new_image(
			uni->mlx, uni->m_map.width, uni->m_map.height);
	if (!uni->m_map.walls)
		free_and_exit(uni, 1);
	inst = mlx_image_to_window(uni->mlx,
			uni->m_map.walls, uni->width - uni->m_map.width,
			uni->height - uni->m_map.height);
	if (inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->m_map.walls->instances[inst], 4);
	uni->m_map.sight = mlx_new_image(
			uni->mlx, uni->m_map.width, uni->m_map.height);
	if (!uni->m_map.sight)
		free_and_exit(uni, 1);
	inst = mlx_image_to_window(uni->mlx,
			uni->m_map.sight, uni->width - uni->m_map.width,
			uni->height - uni->m_map.height);
	if (inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->m_map.sight->instances[inst], 3);
}

// create and display the minimap 
void	create_minimap(t_uni *uni)
{
	int	x;
	int	y;

	init_map_images(uni);
	mlx_loop_hook(uni->mlx, &draw_player_hook, uni);
	x = 0;
	while (x++ < uni->map_container.map_width - 2)
	{
		y = 0;
		while (y++ < uni->map_container.map_height - 2)
		{
			if (uni->map_container.map_array[y][x] == 1)
				draw_block(uni,
					x * (uni->m_map.width / uni->map_container.map_width),
					y * (uni->m_map.height / uni->map_container.map_height),
					create_color(0, 0, 0, 255));
			else if (uni->map_container.map_array[y][x] == 2)
				draw_block(uni,
					x * (uni->m_map.width / uni->map_container.map_width),
					y * (uni->m_map.height / uni->map_container.map_height),
					create_color(102, 0, 0, 150));
		}
	}
}
