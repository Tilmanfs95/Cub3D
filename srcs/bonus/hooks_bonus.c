/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:39:42 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 22:46:01 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// handle keyboard input
void	input_hook(void	*param)
{
	t_uni			*uni;

	uni = param;
	if (mlx_is_key_down(uni->mlx, MLX_KEY_ESCAPE))
		free_and_exit(uni, 0);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_W))
		move_player(uni, uni->player.dir, 0.05);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_S))
		move_player(uni, uni->player.dir, -0.05);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_A))
		move_player(uni, twist_dir(uni->player.dir, -90), 0.03);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_D))
		move_player(uni, twist_dir(uni->player.dir, 90), 0.03);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_LEFT))
		rotate_player(uni, -2);
	if (mlx_is_key_down(uni->mlx, MLX_KEY_RIGHT))
		rotate_player(uni, 2);
}

// handle cursor input
void	cursorhook(double xpos, double ypos, void *param)
{
	t_uni			*uni;

	uni = param;
	if (xpos != uni->cursor_xpos)
		rotate_player(uni, (xpos - uni->cursor_xpos) / 15);
	uni->cursor_xpos = xpos;
	if (ypos > uni->height / 1.5)
		mlx_set_mouse_pos(uni->mlx, xpos, uni->height / 1.5);
	else if (ypos < -uni->height / 1.5)
		mlx_set_mouse_pos(uni->mlx, xpos, -uni->height / 1.5);
	else
		uni->cursor_ypos = ypos;
}

// loop hook to raycast and render the game
void	render_hook(void *param)
{
	t_uni	*uni;

	uni = param;
	raycast(uni);
}
