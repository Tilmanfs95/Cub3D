/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:02:19 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/31 18:38:08 by mkneisl          ###   ########.fr       */
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
	mlx_close_hook(uni->mlx, &free_and_exit_hook, uni);
	if (mlx_loop_hook(uni->mlx, &input_hook, uni) == false)
		free_and_exit(uni, 1);
	if (mlx_loop_hook(uni->mlx, &render_hook, uni) == false)
		free_and_exit(uni, 1);
	mlx_loop(uni->mlx);
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
