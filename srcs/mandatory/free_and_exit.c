/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:22:09 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 22:43:19 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_and_exit(void	*param, int err)
{
	t_uni	*uni;

	uni = (t_uni *)param;
	if (uni->mlx)
		mlx_close_window(uni->mlx);
	if (uni->screen_img)
		mlx_delete_image(uni->mlx, uni->screen_img);
	if (uni->sight)
		free(uni->sight);
	if (uni->map_container.header.north_tex)
		mlx_delete_texture(uni->map_container.header.north_tex);
	if (uni->map_container.header.south_tex)
		mlx_delete_texture(uni->map_container.header.south_tex);
	if (uni->map_container.header.east_tex)
		mlx_delete_texture(uni->map_container.header.east_tex);
	if (uni->map_container.header.west_tex)
		mlx_delete_texture(uni->map_container.header.west_tex);
	if (uni->mlx)
		mlx_terminate(uni->mlx);
	free_ptr_array((void **)uni->map_container.map_array);
	if (err == 1)
		printf("Error\nallocation error");
	exit(err);
}

void	free_and_exit_hook(void	*param)
{
	free_and_exit(param, 0);
}
