/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:47:23 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/28 22:32:32 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// twist an direction (degree as double) in an given angle
double	twist_dir(double dir, double twist_angle)
{
	double	new_dir;

	new_dir = dir + twist_angle;
	if (new_dir < -179)
		new_dir += 360;
	else if (new_dir > 180)
		new_dir -= 360;
	return (new_dir);
}

// get the direction (degree as double) between p1 and p2
double	dir_in_degree(t_point p1, t_point p2)
{
	double	x_diff;
	double	y_diff;

	x_diff = p2.x - p1.x;
	y_diff = p2.y - p1.y;
	return (atan2(y_diff, x_diff) * 180.0 / M_PI);
}

// get a new point with a specific distance and direction from another point
t_point	get_point_in_dir(t_point point, double dir, double distance)
{
	double	radiant;
	double	x_increment;
	double	y_increment;
	t_point	new_point;

	radiant = dir * M_PI / 180.0;
	x_increment = distance * cos(radiant);
	y_increment = distance * sin(radiant);
	new_point = (struct s_point){point.x + x_increment, point.y + y_increment};
	return (new_point);
}

// get the distance between 2 points
double	distance(t_point p1, t_point p2)
{
	return (hypot(p2.x - p1.x, p2.y - p1.y));
}

// get the angle between 2 directions
double	angle_between_dirs(double dir1, double dir2)
{
	double	angle;

	angle = dir2 - dir1;
	if (angle < -180)
	{
		angle += 360;
	}
	else if (angle > 180)
	{
		angle -= 360;
	}
	return (angle);
}
