/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkneisl <mkneisl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:34:44 by tfriedri          #+#    #+#             */
/*   Updated: 2023/03/31 18:27:01 by mkneisl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# define MCTNUM 420

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_player
{
	double			dir;
	t_point			pos;
}					t_player;

typedef struct s_map_header
{
	int32_t			sky_color;
	int32_t			floor_color;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;
	t_player		player;
}t_map_header;

typedef struct s_map_container
{
	t_map_header	header;
	int				map_width;
	int				map_height;
	int				**map_array;
}t_map_container;

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*sight;
	mlx_texture_t	*player;
	int32_t			px_per_block;
	int32_t			height;
	int32_t			width;
}					t_minimap;

typedef struct s_sigth
{
	double			distance;
	double			angle;
	double			ray_dir;
	int				line_len;
	t_point			wall;
	int				wall_side;
}					t_sight;

typedef struct s_uni
{
	mlx_t			*mlx;
	t_map_container	map_container;
	t_player		player;
	mlx_image_t		*screen_img;
	t_minimap		m_map;
	int32_t			width;
	int32_t			height;
	double			view_angle;
	double			wall_height;
	t_sight			*sight;
	mlx_texture_t	*door;
	mlx_texture_t	*reticle;
	mlx_image_t		*reticle_img;
	mlx_texture_t	*mf[4];
	mlx_image_t		*mf_img;
	mlx_texture_t	*weapon;
	mlx_image_t		*weapon_img;
	int				cursor_xpos;
	int				cursor_ypos;
}					t_uni;

// game
t_point	targeted_point(t_uni	*uni, double dir, double *distance);
void	tex_to_image(mlx_image_t *image, mlx_texture_t *tex,
			unsigned int x, unsigned int y);
void	bonus_key_hook(mlx_key_data_t keydata, void *param);
int32_t	get_color_from_tex(mlx_texture_t *tex, double x, double y);
void	input_hook(void	*param);
void	cursorhook(double xpos, double ypos, void *param);
void	render_hook(void *param);
void	free_and_exit(void	*param, int err);
void	free_and_exit_hook(void	*param);
void	create_minimap(t_uni *uni);
int32_t	create_color(int32_t red, int32_t green, int32_t blue, int32_t a);
void	draw_line(mlx_image_t *img, t_point p1, t_point p2, uint32_t color);
double	distance(t_point p1, t_point p2);
double	dir_in_degree(t_point p1, t_point p2);
t_point	get_point_in_dir(t_point point, double dir, double distance);
double	angle_between_dirs(double dir1, double dir2);
void	move_player(t_uni *uni, double dir, double distance);
void	move_forward(void *param);
void	move_backward(void *param);
void	move_left(void *param);
void	move_right(void *param);
void	rotate_player(void *param, double angle);
double	dist_to_wall(t_uni	*uni, double dir);
double	dist_next_cell(t_point point, double dir_rad);
t_point	next_wall_in_dir(t_uni	*uni, double dir, double *distance);
void	raycast(t_uni *uni);
double	twist_dir(double dir, double twist_angle);
void	draw_wall_px(t_uni *uni, int screen_x,
			int screen_y, double y_img_pos);
void	clear_image(mlx_image_t	*img);
bool	is_wall(int cell);
void	mousehook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
// Parsing
void	free_ptr_array(void **arr);
char	**ft_split_str(char const *s, char *cs);
char	*get_next_line(int fd);

bool	validate_map_border(t_map_container *world_map);
bool	validate_map(t_map_container *world_map);
void	copy_line(char *str, int *arr);
bool	parse_map_header(t_map_header *map_header, int fd);
bool	load_map(t_map_container *world_map, int fd);
bool	parse_map(t_map_container *world_map, t_list **list);
void	read_map(t_map_container *world_map, t_list	**list, int fd);

char	*string_append(char *str, char *to_append);
void	string_replace(char **str, char *insert, int start, int length);
void	replace_all(char **str, char *to_replace, char *new);
char	is_space(int c);
void	string_remove(char **str, int start, int length);
int		remove_spaces(char **str);
bool	has_file_type(char *str, char *type);

#endif