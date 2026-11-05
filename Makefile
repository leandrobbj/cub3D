# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/29 14:00:29 by lbraga            #+#    #+#              #
#    Updated: 2026/11/05 16:21:40 by lbraga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
HEADER	=	cub3D.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I.
OBJ		=	$(SRC:src/%.c=obj/%.o)
LIBFT_D	=	src/libft
LIBFT	=	$(LIBFT_D)/libft.a
MLX_D	=	minilibx-linux
MLX		=	$(MLX_D)/libmlx.a
MLX_LNK	=	-L$(MLX_D) -lmlx -lXext -lX11 -lm -lz

SRC		=	src/main.c \
			src/elements/color.c src/elements/elements.c src/elements/texture.c \
			src/map/map_closed.c src/map/map_grid.c src/map/map_parsing.c src/map/map.c \
			src/parsing/error.c src/parsing/file.c src/parsing/parsing.c src/parsing/utils.c \
			src/exec/init.c src/exec/handlers.c src/exec/move.c src/exec/dda.c \
			src/exec/draw.c src/exec/minimap.c

all: $(NAME)
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) $(MLX_LNK) -o $(NAME) 
	@echo "* $(NAME) compiled"

obj/%.o: src/%.c $(HEADER)
	@mkdir -p $(@D)
	@echo "* Compiling $<"
	@$(CC) $(CFLAGS) -c -o $@ $< 

$(LIBFT): $(LIBFT_D)
	@$(MAKE) -C $(LIBFT_D) --no-print-directory

$(MLX):
	@$(MAKE) -s -C $(MLX_D) --no-print-directory

clean:
	@$(MAKE) fclean -C $(LIBFT_D) --no-print-directory
	@$(MAKE) clean -C $(MLX_D) --no-print-directory
	@rm -rf obj
	@echo "* $(NAME) objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "* $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re new