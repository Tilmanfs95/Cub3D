/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:15:30 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 18:42:59 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// function to get the wall-side at which the player looks
// nord = 1,	south = 2,	west = 3,	east = 4
int	get_wall_side(t_uni *uni, t_point wall)
{
	double	dir;

	dir = dir_in_degree(uni->player.pos, wall);
	if (dir >= -180 && dir <= -90 && fabs(round(wall.x) - wall.x) < 0.000001)
		return (3);
	if (dir >= -90 && dir <= 0 && fabs(round(wall.x) - wall.x) < 0.000001)
		return (4);
	if (dir <= 180 && dir >= 90 && fabs(round(wall.x) - wall.x) < 0.000001)
		return (3);
	if (dir <= 90 && dir >= 0 && fabs(round(wall.x) - wall.x) < 0.000001)
		return (4);
	if (dir >= -180 && dir <= 0)
		return (1);
	else
		return (2);
}

// draws a vertical line on the screen (ceiling, wall and floor)
void	draw_vert_line(t_uni *uni, int line)
{
	int		i;
	int		start;
	int		end;

	start = ((-uni->sight[line].line_len) / 2) + (uni->height / 2);
	end = ((uni->sight[line].line_len) / 2) + (uni->height / 2);
	i = 0;
	while (i < uni->height)
	{
		if (i <= start)
			mlx_put_pixel(uni->screen_img, line, i,
				uni->map_container.header.sky_color);
		if (i > start && i < end)
			draw_wall_px(uni, line, i,
				(double)(i - start) / (double)(end - start));
		if (i >= end)
			mlx_put_pixel(uni->screen_img, line, i,
				uni->map_container.header.floor_color);
		i++;
	}
}

// iterates throught and draws the vertical lines
void	render(t_uni *uni)
{
	int		i;

	i = 0;
	while (i < uni->width)
	{
		draw_vert_line(uni, i);
		i++;
	}
}

// get the directions of all the rays for uni->sight[]
void	get_ray_directions(t_uni *uni)
{
	t_point	left;
	t_point	right;
	double	dist;
	double	dir;
	int		i;

	left = get_point_in_dir(uni->player.pos,
			twist_dir(uni->player.dir, -(uni->view_angle / 2)), 10);
	right = get_point_in_dir(uni->player.pos,
			twist_dir(uni->player.dir, uni->view_angle / 2), 10);
	dist = distance(left, right);
	dir = dir_in_degree(left, right);
	dist = dist / (uni->width -1);
	i = 0;
	while (i < uni->width)
	{
		right = get_point_in_dir(left, dir, dist);
		uni->sight[i].ray_dir = dir_in_degree(uni->player.pos, left);
		left = right;
		i++;
	}
}

// function to start the raycasting and rendering process for
// each vertical line of the screen
void	raycast(t_uni *uni)
{
	int		i;

	i = 0;
	get_ray_directions(uni);
	while (i < uni->width)
	{
		uni->sight[i].wall = next_wall_in_dir(
				uni, uni->sight[i].ray_dir, &uni->sight[i].distance);
		uni->sight[i].angle = angle_between_dirs(
				uni->player.dir, uni->sight[i].ray_dir);
		uni->sight[i].distance = uni->sight[i].distance
			* cos(uni->sight[i].angle * M_PI / 180.0);
		uni->sight[i].line_len = (int)(
				uni->height * uni->wall_height / uni->sight[i].distance);
		uni->sight[i].wall_side = get_wall_side(uni, uni->sight[i].wall);
		i++;
	}
	render(uni);
}
