# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osabir <osabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:43:21 by osabir            #+#    #+#              #
#    Updated: 2024/03/14 14:16:45 by osabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc #-fsanitize=address 

FLAG			=  -Wall -Werror -Wextra -Ofast

MLX				= -lmlx -framework OpenGL -framework AppKit
			
SRC				= ./Mandatory/cub3d.c ./Mandatory/get_line/get_next_line.c ./Mandatory/get_line/get_next_line_utils.c \
				./Mandatory/parsing/tools_1.c ./Mandatory/parsing/tools_2.c ./Mandatory/parsing/tools_3.c ./Mandatory/parsing/tools_4.c \
				./Mandatory/parsing/tools_5.c ./Mandatory/parsing/tools_6.c ./Mandatory/parsing/tools_7.c ./Mandatory/parsing/tools_8.c \
				./Mandatory/parsing/tools_9.c ./Mandatory/parsing/tools_10.c ./Mandatory/parsing/tools_11.c ./Mandatory/parsing/tools_12.c \
				./Mandatory/mlx_func/mlx_func_1.c ./Mandatory/mlx_func/mlx_func_2.c ./Mandatory/mlx_func/mlx_func_3.c ./Mandatory/mlx_func/mlx_func_4.c \
				./Mandatory/mlx_func/move_1.c ./Mandatory/mlx_func/move_2.c \
				./Mandatory/raycasting/ray_1.c ./Mandatory/raycasting/ray_2.c ./Mandatory/raycasting/ray_3.c ./Mandatory/raycasting/ray_4.c \
				./Mandatory/raycasting/ray_5.c ./Mandatory/raycasting/ray_6.c \
				./Mandatory/struct/player.c ./Mandatory/struct/struct_1.c ./Mandatory/struct/struct_2.c

SRC_BONUS		= ./bonus/cub3d.c ./bonus/get_line/get_next_line.c ./bonus/get_line/get_next_line_utils.c \
				./bonus/parsing/tools_1.c ./bonus/parsing/tools_2.c ./bonus/parsing/tools_3.c ./bonus/parsing/tools_4.c \
				./bonus/parsing/tools_5.c ./bonus/parsing/tools_6.c ./bonus/parsing/tools_7.c ./bonus/parsing/tools_8.c \
				./bonus/parsing/tools_9.c ./bonus/parsing/tools_10.c ./bonus/parsing/tools_11.c ./bonus/parsing/tools_12.c \
				./bonus/mlx_func/mlx_func_1.c ./bonus/mlx_func/mlx_func_2.c ./bonus/mlx_func/mlx_func_3.c ./bonus/mlx_func/mlx_func_4.c \
				./bonus/mlx_func/move_1.c ./bonus/mlx_func/move_2.c \
				./bonus/raycasting/ray_1.c ./bonus/raycasting/ray_2.c ./bonus/raycasting/ray_3.c ./bonus/raycasting/ray_4.c \
				./bonus/raycasting/ray_5.c ./bonus/raycasting/ray_6.c ./bonus/raycasting/minimap.c \
				./bonus/struct/player.c ./bonus/struct/struct_1.c ./bonus/struct/struct_2.c
 		
OBJ 			= $(SRC:.c=.o)
OBJ_BONUS 		= $(SRC_BONUS:.c=.o)

NAME 			= cub3D
NAME_BONUS 		= cub3D_bonus

HD 				= ./Mandatory/cub3d.h
HD_BONUS 		= ./bonus/cub3d.h

all 			: $(NAME)
	
bonus				: $(NAME_BONUS)

$(NAME) 		: $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)
	

$(NAME_BONUS) 	: $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(MLX) -o $(NAME_BONUS)

%.o 			: %.c $(HD) $(HD_BONUS)
	$(CC) $(FLAG) -Imlx -c $< -o $@

clean 			:
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean 			: clean
	rm -rf $(NAME) $(NAME_BONUS)

re 				: fclean all