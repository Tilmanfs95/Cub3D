/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:28:05 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/29 18:55:56 by tfriedri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// draws a line between 2 points on image
void	draw_line(mlx_image_t *img, t_point p1, t_point p2, uint32_t color)
{
	double	steps;
	double	x_increment;
	double	y_increment;
	int		i;

	steps = fmax(fabs(p2.x - p1.x), fabs(p2.y - p1.y));
	x_increment = (p2.x - p1.x) / steps;
	y_increment = (p2.y - p1.y) / steps;
	i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(img, round(p1.x), round(p1.y), color);
		p1.x += x_increment;
		p1.y += y_increment;
		i++;
	}
}

// clear an mlx image
void	clear_image(mlx_image_t	*img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int));
}
