# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfriedri <tfriedri@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 17:03:40 by tfriedri          #+#    #+#              #
#    Updated: 2023/03/31 17:07:40 by tfriedri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	PROBLEMS MAC:
#	if cmake is not installed:		brew install cmake
#	if glfw is not installed:		brew install glfw

NAME		=		cub3D
BONUS		=		cub3D_bonus
CC			=		cc
CFLAGS		=		-Wall -Werror -Wextra
MLXDIR		=		./MLX42
MLX			=		./MLX42/build/libmlx42.a
LIBFTDIR	=		./libft
LIBFT		=		./libft/libft.a

SRCS		=		srcs/mandatory/main.c					\
					srcs/mandatory/free_and_exit.c			\
					srcs/mandatory/helpers.c				\
					srcs/mandatory/player_move.c			\
					srcs/mandatory/get_distance.c			\
					srcs/mandatory/raycast_and_render.c		\
					srcs/mandatory/draw_walls.c				\
					srcs/mandatory/gnl.c					\
					srcs/mandatory/parsing.c				\
					srcs/mandatory/ft_split_str.c			\
					srcs/mandatory/string.c					\
					srcs/mandatory/parse_map_header.c		\
					srcs/mandatory/parse_map.c				\
					srcs/mandatory/parse_utils.c			\
					srcs/mandatory/remove_space.c			\
					srcs/mandatory/hooks.c					\

B_SRCS		=		srcs/bonus/main_bonus.c					\
					srcs/bonus/free_and_exit_bonus.c		\
					srcs/bonus/minimap_bonus.c				\
					srcs/bonus/helpers_bonus.c				\
					srcs/bonus/player_move_bonus.c			\
					srcs/bonus/get_distance_bonus.c			\
					srcs/bonus/raycast_and_render_bonus.c	\
					srcs/bonus/draw_walls_bonus.c			\
					srcs/bonus/bonus_bonus.c				\
					srcs/bonus/bonus_helpers_bonus.c		\
					srcs/bonus/gnl_bonus.c					\
					srcs/bonus/parsing_bonus.c				\
					srcs/bonus/ft_split_str_bonus.c			\
					srcs/bonus/string_bonus.c				\
					srcs/bonus/parse_map_header_bonus.c		\
					srcs/bonus/parse_map_bonus.c			\
					srcs/bonus/parse_utils_bonus.c			\
					srcs/bonus/remove_space_bonus.c			\
					srcs/bonus/hooks_bonus.c				\

OBJS		=		$(SRCS:.c=.o)

B_OBJS		=		$(B_SRCS:.c=.o)

all:				$(NAME)

bonus:				$(BONUS)

$(NAME):			$(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) MLX42/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

$(BONUS):			$(MLX) $(LIBFT) $(B_OBJS)
	@$(CC) $(CFLAGS) $(B_OBJS) $(MLX) $(LIBFT) MLX42/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o $(BONUS)

$(MLX):
	@cd $(MLXDIR) && cmake -B build
	@cd $(MLXDIR) && cmake --build build -j4

$(LIBFT):
	@cd $(LIBFTDIR) && make bonus

clean:
	@rm -f $(OBJS)
	@rm -f $(B_OBJS)
	@cd $(MLXDIR) && rm -rf build/
	@cd $(LIBFTDIR) && make clean

fclean:				clean
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@cd $(LIBFTDIR) && make fclean

re:
	@make fclean
	@make

norm:
	@norminette $(LIBFTDIR) srcs/ libft/
