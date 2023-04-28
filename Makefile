# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 17:12:12 by fgomez-d          #+#    #+#              #
#    Updated: 2023/04/28 09:44:59 by fgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CPPFLAGS=-Ilibft -Iinc
NAME=fdf

GLFW_PATH="/Users/$(USER)/.brew/opt/glfw/lib/"
CFLAGS=-Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX=MLX42

HEADERS=-I$(LIBMLX)/include
LIBS=-ldl -lglfw -L$(GLFW_PATH) -pthread -lm $(LIBMLX)/libmlx42.a

LIB_DIR=libft
LIB_OBJ=$(LIB_DIR)/*.o

SRC_DIR=src
SRC=$(SRC_DIR)/fdf.c $(SRC_DIR)/parse_map.c $(SRC_DIR)/parse_utils.c \
	$(SRC_DIR)/colors.c $(SRC_DIR)/draw_tools.c $(SRC_DIR)/draw_map.c \
	$(SRC_DIR)/colors_utils.c $(SRC_DIR)/parse_utils2.c $(SRC_DIR)/normalization.c \
	$(SRC_DIR)/fdf_utils.c

OBJ=$(SRC:.c=.o)

all: libmlx $(NAME)

$(NAME): $(OBJ) $(LIB_OBJ)
	clear
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LIBS) $(HEADERS) $(OBJ) $(LIB_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

libmlx:
	@$(MAKE) -C $(LIBMLX)

libft:
	$(MAKE) -C libft

$(LIB_OBJ):
	$(MAKE) -C libft

deepclean: clean
	$(MAKE) -C libft fclean
	rm -f $(OBJS)
	$(MAKE) -C MLX42 fclean
	
clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re