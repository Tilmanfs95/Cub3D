/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:21:31 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 18:56:13 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// creates a color to use with mlx
int32_t	create_color(int32_t red, int32_t green, int32_t blue, int32_t a)
{
	return (red << 24 | green << 16 | blue << 8 | a);
}

// converts a pixel to a color
int32_t	px_to_color(int32_t pixel)
{
	int32_t	a;
	int32_t	b;
	int32_t	g;
	int32_t	r;

	a = (pixel >> 24) & 0xFF;
	b = (pixel >> 16) & 0xFF;
	g = (pixel >> 8) & 0xFF;
	r = pixel & 0xFF;
	return (create_color(r, g, b, a));
}

// function to get the color of a specific position of a texture
// x and y have to be doubles between 0.0 and 1.0
int32_t	get_color_from_tex(mlx_texture_t *tex, double x, double y)
{
	int32_t	px;
	int		width;
	int		height;

	width = x * tex->width;
	height = y * tex->height;
	ft_memcpy(&px,
		tex->pixels + (((height) * tex->width) + width) * sizeof(int32_t),
		sizeof(int32_t));
	return (px_to_color(px));
}

void	x_img_if_door(t_uni *uni, int screen_x, double *x_img)
{
	if (uni->sight[screen_x].wall_side == 5)
	{
		if (fmod(uni->sight[screen_x].wall.y, 1.0) <= 0.000001)
			*x_img = fmod(uni->sight[screen_x].wall.x, 1.0);
		else
			*x_img = fmod(uni->sight[screen_x].wall.y, 1.0);
	}
}

// draws a pixel of a wall on the screen.
void	draw_wall_px(t_uni *uni, int screen_x,
	int screen_y, double y_img_pos)
{
	mlx_texture_t	*wall;
	double			x_img;

	if (uni->sight[screen_x].wall_side == 1
		|| uni->sight[screen_x].wall_side == 2)
		x_img = fmod(uni->sight[screen_x].wall.x, 1.0);
	else
		x_img = fmod(uni->sight[screen_x].wall.y, 1.0);
	if (uni->sight[screen_x].wall_side == 1)
		wall = uni->map_container.header.north_tex;
	else if (uni->sight[screen_x].wall_side == 2)
		wall = uni->map_container.header.south_tex;
	else if (uni->sight[screen_x].wall_side == 3)
		wall = uni->map_container.header.west_tex;
	else if (uni->sight[screen_x].wall_side == 4)
		wall = uni->map_container.header.east_tex;
	if (uni->map_container.map_array[(int)uni->sight[screen_x].wall.y]
		[(int)uni->sight[screen_x].wall.x] == 2)
		wall = uni->door;
	mlx_put_pixel(uni->screen_img, screen_x, screen_y,
		get_color_from_tex(wall,
			x_img,
			y_img_pos
			));
}
