/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:49:29 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 17:19:16 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// function to get the targeted point
t_point	targeted_point(t_uni	*uni, double dir, double *distance)
{
	double	dist;
	double	full_dist;
	t_point	point;
	int		block_height;

	point = uni->player.pos;
	dist = 0;
	full_dist = 0;
	while (1)
	{
		dist = dist_next_cell(point, dir * M_PI / 180.0);
		point = get_point_in_dir(point, dir, dist + 0.0000001);
		full_dist = full_dist + dist;
		if (uni->map_container.map_array[(int)point.y][(int)point.x] != 0)
			break ;
	}
	*distance = full_dist;
	block_height = (int)(uni->height * (uni->wall_height / *distance));
	if ((-block_height / 2) + (uni->height / 2) - uni->cursor_ypos
		< uni->height / 2
		&& (block_height / 2) + (uni->height / 2) - uni->cursor_ypos
		> uni->height / 2)
		return (point);
	return ((struct s_point){0, 0});
}

// muzzle-flash-animation
void	muzzle_flash(t_uni *uni, bool shoot)
{
	static int	i = 0;

	if (shoot)
	{
		mlx_draw_texture(uni->mf_img, uni->mf[i],
			(uni->width / 2) - 40,
			(uni->height / 2) - 5);
		i++;
		if (i == 4)
			i = 0;
	}
	else
		clear_image(uni->mf_img);
}

// handle keyboard input to open doors
void	bonus_key_hook(mlx_key_data_t keydata, void *param)
{
	t_uni		*uni;
	t_point		pnt;
	double		distance;

	uni = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		pnt = targeted_point(uni, uni->player.dir, &distance);
		if (uni->map_container.map_array[(int)pnt.y][(int)pnt.x] == 2
			&& distance < 1.7)
			uni->map_container.map_array[(int)pnt.y][(int)pnt.x] = 3;
		else if (uni->map_container.map_array[(int)pnt.y][(int)pnt.x] == 3
			&& distance < 1.7)
			uni->map_container.map_array[(int)pnt.y][(int)pnt.x] = 2;
	}
}

// hook to handle the mouse-clicks
void	mousehook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param)
{
	t_uni	*uni;

	uni = ((t_uni *)param);
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		muzzle_flash(uni, true);
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		muzzle_flash(uni, false);
	(void)mods;
}
