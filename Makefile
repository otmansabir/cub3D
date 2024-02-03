# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osabir <osabir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:43:21 by osabir            #+#    #+#              #
#    Updated: 2024/02/03 11:09:26 by osabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc 

FLAG	= -Wall -Werror -Wextra

MLX		= -lmlx -framework OpenGL -framework AppKit

SRC	= cub3d.c get_next_line.c get_next_line_utils.c tools_1.c tools_2.c tools_3.c  tools_4.c
		
OBJ 	= $(SRC:.c=.o)

NAME 	= cub3D

HD 	= cub3D.h

all 	: $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

%.o : %.c $(HD1)
	$(CC) $(FLAG) -Imlx -c $< -o $@

clean :
	rm -rf $(OBJ) 

fclean : clean
	rm -rf $(NAME) 

re : fclean all