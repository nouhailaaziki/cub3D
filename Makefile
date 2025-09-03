# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 14:07:43 by hajel-ho          #+#    #+#              #
#    Updated: 2025/09/03 18:46:06 by hajel-ho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=address
DEBUGFLAGS = -Wall -Wextra -Werror 

FLMLX   = #-framework Cocoa -framework OpenGL -framework IOKit

SRC = cub3d.c \
      cub/get_next_line.c \
      cub/get_next_line_utils.c \
      cub/parsing_utils1.c \
      cub/parsing_utils2.c \
      cub/parsing.c \
      cub/split.c \
      cub/utils1.c \
      cub/utils2.c \

OBJ = $(SRC:.c=.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(FLMLX)

debug: $(OBJ)
	$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(FLMLX)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

