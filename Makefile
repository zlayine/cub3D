# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlayine <zlayine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/25 11:19:56 by zlayine           #+#    #+#              #
#    Updated: 2020/01/13 11:12:34 by zlayine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = srcs/casting.c \
		srcs/draw.c \
		srcs/game.c \
		srcs/keys.c \
		srcs/parse_init.c \
		srcs/parse_manager.c \
		srcs/parse_map.c \
		srcs/sprite.c \
		srcs/texture.c \
		srcs/utils.c \
		srcs/bmp.c \
		srcs/error.c \
		srcs/parse_checker.c

LIBFT = ./libft

MLX = ./mlx_gl

MLX_LIB = $(MLX)/libmlx.a

LIBFT_LIB = $(LIBFT)/libft.a

CUB_LIB = cub3D.a

OBJ = $(SRC:.c=.o)

INC = includes

MAIN = main.c

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MAIN) $(INC)/cub3d.h
	@ar rcs $(CUB_LIB) $(OBJ)
	@gcc -Wall -Wextra -Werror $(MAIN) $(CUB_LIB) $(LIBFT_LIB) $(MLX_LIB) -lz -framework OpenGL -framework AppKit -o $(NAME)
	@echo "SUCCESS!"

%.o: %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@ -I $(INC)

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf $(CUB_LIB)
	@rm -rf $(NAME)

re: fclean all	