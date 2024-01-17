/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:23:09 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/31 16:04:57 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// check if you can move there
bool	is_wall(int cell)
{
	if (cell == 1 || cell == 2)
		return (0);
	return (1);
}

// get the difference between 2 integers
int	get_diff(int num1, int num2)
{
	int	result;

	result = num1 - num2;
	if (result < 0)
		result = -result;
	return (result);
}

// moves the weapon
void	move_weapon(t_uni *uni)
{
	static int		i = 0;
	static int		j = 0;

	if (j == 0)
	{
		uni->weapon_img->instances[0].y -= 2;
		uni->mf_img->instances[0].y -= 2;
	}
	else
	{
		uni->weapon_img->instances[0].y += 2;
		uni->mf_img->instances[0].y += 2;
	}
	if (i >= 8)
	{
		if (j == 0)
			j = 1;
		else
			j = 0;
		i = 0;
	}
	i++;
}

// moves the player
void	move_player(t_uni *uni, double dir, double distance)
{
	t_point			new_pos;

	new_pos = get_point_in_dir(uni->player.pos, dir, distance);
	if (is_wall(uni->map_container.map_array
			[((int)new_pos.y)][((int)new_pos.x)])
		&& !(get_diff(uni->player.pos.x, new_pos.x) == 1
		&& get_diff(uni->player.pos.y, new_pos.y) == 1))
			uni->player.pos = new_pos;
	else if (is_wall(uni->map_container.map_array
			[((int)new_pos.y)][((int)uni->player.pos.x)]))
			uni->player.pos = (struct s_point){uni->player.pos.x, new_pos.y};
	else if (is_wall(uni->map_container.map_array
			[((int)uni->player.pos.y)][((int)new_pos.x)]))
			uni->player.pos = (struct s_point){new_pos.x, uni->player.pos.y};
	move_weapon(uni);
}

// rotates the player
void	rotate_player(void *param, double angle)
{
	t_uni			*uni;

	uni = param;
	if (uni->player.dir == 180)
		uni->player.dir = -178;
	else
		uni->player.dir = uni->player.dir + angle;
}
