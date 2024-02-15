# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osabir <osabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:43:21 by osabir            #+#    #+#              #
#    Updated: 2024/02/15 12:49:02 by osabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc -g # -fsanitize=address 

FLAG	=  -Wall -Werror -Wextra -Ofast

MLX		= -lmlx -framework OpenGL -framework AppKit

SRC	= cub3d.c get_next_line.c get_next_line_utils.c tools_1.c tools_2.c tools_3.c  tools_4.c
		
OBJ 	= $(SRC:.c=.o)

NAME 	= cub3D

HD 	= cub3d.h

all 	: $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

%.o : %.c $(HD)
	$(CC) $(FLAG) -Imlx -c $< -o $@

clean :
	rm -rf $(OBJ) 

fclean : clean
	rm -rf $(NAME) 

re : fclean all