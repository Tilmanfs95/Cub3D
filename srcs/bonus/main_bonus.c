/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:02:19 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/31 18:38:18 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// function to start the game after the initialisation
void	start_game(t_uni *uni)
{
	int	screen_img_inst;

	uni->screen_img = mlx_new_image(uni->mlx, uni->width, uni->height);
	if (!uni->screen_img)
		free_and_exit(uni, 1);
	screen_img_inst = mlx_image_to_window(uni->mlx, uni->screen_img, 0, 0);
	if (screen_img_inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->screen_img->instances[screen_img_inst], 0);
	create_minimap(uni);
	mlx_close_hook(uni->mlx, &free_and_exit_hook, uni);
	if (mlx_loop_hook(uni->mlx, &input_hook, uni) == false)
		free_and_exit(uni, 1);
	mlx_key_hook(uni->mlx, &bonus_key_hook, uni);
	mlx_cursor_hook(uni->mlx, &cursorhook, uni);
	mlx_mouse_hook(uni->mlx, &mousehook, uni);
	if (mlx_loop_hook(uni->mlx, &render_hook, uni) == false)
		free_and_exit(uni, 1);
	mlx_loop(uni->mlx);
}

// initialisation of bonus images
void	init_bonus_images(t_uni *uni)
{
	int	inst;

	uni->reticle_img = mlx_texture_to_image(uni->mlx, uni->reticle);
	uni->weapon_img = mlx_texture_to_image(uni->mlx, uni->weapon);
	uni->mf_img = mlx_new_image(uni->mlx, uni->width, uni->height);
	if (!uni->reticle_img || !uni->weapon_img || !uni->mf_img)
		free_and_exit(uni, 1);
	inst = mlx_image_to_window(uni->mlx, uni->reticle_img,
			(uni->width / 2) - (uni->reticle->width / 2),
			(uni->height / 2) - (uni->reticle->height / 2));
	if (inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->reticle_img->instances[inst], 2);
	inst = mlx_image_to_window(uni->mlx, uni->weapon_img,
			(uni->width) - (uni->weapon->width),
			(uni->height) - (uni->weapon->height / 1.3));
	if (inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->weapon_img->instances[inst], 2);
	inst = mlx_image_to_window(uni->mlx, uni->mf_img, 0, 0);
	if (inst == -1)
		free_and_exit(uni, 1);
	mlx_set_instance_depth(&uni->mf_img->instances[inst], 1);
}

// initialisation of bonus stuff
void	init_bonus(t_uni *uni)
{
	mlx_get_mouse_pos(uni->mlx, &uni->cursor_xpos, &uni->cursor_ypos);
	mlx_set_cursor_mode(uni->mlx, MLX_MOUSE_DISABLED);
	uni->m_map.height = uni->height / 5;
	uni->m_map.px_per_block = uni->m_map.height / uni->map_container.map_height;
	uni->m_map.width = (uni->m_map.height / uni->map_container.map_height)
		* uni->map_container.map_width;
	uni->door = mlx_load_png("images/door.png");
	uni->reticle = mlx_load_png("images/reticle.png");
	uni->weapon = mlx_load_png("images/weapon.png");
	uni->mf[0] = mlx_load_png("images/mf1.png");
	uni->mf[1] = mlx_load_png("images/mf2.png");
	uni->mf[2] = mlx_load_png("images/mf3.png");
	uni->mf[3] = mlx_load_png("images/mf4.png");
	uni->m_map.player = mlx_load_png("images/minimap_player.png");
	if (!uni->door || !uni->m_map.player || !uni->reticle
		|| !uni->weapon || !uni->mf[0] || !uni->mf[1]
		|| !uni->mf[2] || !uni->mf[3])
		free_and_exit(uni, 1);
	init_bonus_images(uni);
}

// initialisation of the uni struct
void	init_uni_struct(t_uni *uni)
{
	uni->width = 1200;
	uni->height = 850;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	uni->mlx = mlx_init(uni->width, uni->height, "cub3D", true);
	if (!uni->mlx)
		free_and_exit(uni, 1);
	uni->sight = (t_sight *)ft_calloc(uni->width, sizeof(t_sight) + 1);
	if (!uni->sight)
		free_and_exit(uni, 1);
	uni->view_angle = 66.0;
	uni->wall_height = 1.0;
	uni->player.pos.x = uni->map_container.header.player.pos.x + 0.5;
	uni->player.pos.y = uni->map_container.header.player.pos.y + 0.5;
	uni->player.dir = uni->map_container.header.player.dir;
	init_bonus(uni);
}

int	main(int argc, char **argv)
{
	t_uni	uni;
	int		fd;

	ft_memset((char *)&uni, 0, sizeof(t_uni));
	if (argc != 2)
	{
		printf("Error\nneed a map as argument!\n");
		return (1);
	}
	if (!has_file_type(argv[1], ".cub"))
		return (printf("Error\nwrong map file type!\n"), 1);
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nfailed to open the map-file!\n");
		return (1);
	}
	if (!load_map(&uni.map_container, fd))
		return (close(fd), 1);
	close(fd);
	init_uni_struct(&uni);
	start_game(&uni);
	free_and_exit(&uni, 0);
	return (EXIT_SUCCESS);
}
