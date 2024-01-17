/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:23:50 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/28 17:33:59 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// distance to next cell in horizontal direction
double	get_x_dist(t_point point, double x_incr)
{
	if (x_incr == 0)
		return (INFINITY);
	else
	{
		if (x_incr > 0)
			return ((ceil(point.x) - point.x) / x_incr);
		else
			return ((floor(point.x) - point.x) / x_incr);
	}
}

// distance to next cell in vertical direction
double	get_y_dist(t_point point, double y_incr)
{
	if (y_incr == 0)
		return (INFINITY);
	else
	{
		if (y_incr > 0)
			return ((ceil(point.y) - point.y) / y_incr);
		else
			return ((floor(point.y) - point.y) / y_incr);
	}
}

// get the distance to the next cell in the given direction
// (from the players position)
double	dist_next_cell(t_point point, double dir_rad)
{
	double	x_incr;
	double	y_incr;
	double	x_dist;
	double	y_dist;

	x_incr = cos(dir_rad);
	y_incr = sin(dir_rad);
	x_dist = get_x_dist(point, x_incr);
	y_dist = get_y_dist(point, y_incr);
	return (fmin(x_dist, y_dist));
}

// get the distance to the next wall in the given direction
// (from player's position)
double	dist_to_wall(t_uni	*uni, double dir)
{
	double	dist;
	double	full_dist;
	t_point	point;

	point = uni->player.pos;
	dist = 0;
	full_dist = 0;
	while (1)
	{
		dist = dist_next_cell(point, dir * M_PI / 180.0);
		point = get_point_in_dir(point, dir, dist + 0.0000001);
		full_dist = full_dist + dist;
		if (!is_wall(uni->map_container.map_array[(int)point.y][(int)point.x]))
			break ;
	}
	return (full_dist - 0.0000001);
}

// get the next wall in the given direction
// (from player position)
t_point	next_wall_in_dir(t_uni	*uni, double dir, double *distance)
{
	double	dist;
	double	full_dist;
	t_point	point;

	point = uni->player.pos;
	dist = 0;
	full_dist = 0;
	while (1)
	{
		dist = dist_next_cell(point, dir * M_PI / 180.0);
		point = get_point_in_dir(point, dir, dist + 0.0000001);
		full_dist = full_dist + dist;
		if (!is_wall(uni->map_container.map_array[(int)point.y][(int)point.x]))
			break ;
	}
	*distance = full_dist;
	return (point);
}
