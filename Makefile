# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:17:44 by qizhang           #+#    #+#              #
#    Updated: 2026/01/29 18:46:18 by kevisout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR	= src
INC_DIR	= includes
OBJ_DIR	= obj
LIBFT_DIR = libft
# MLX_DIR = mlx_macos
MLX_DIR = mlx_linux

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# mlx library
# Linux
MLX_FLAG = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -Isrc/math
# Macos
# MLX_FLAG = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
# INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -Isrc/math

SRC_FILES = main.c \
	math/vector_1.c \
	math/vector_2.c \
	math/colors.c \
	utils/errors.c \
	utils/clean_exit.c \
	utils/objects_utils.c\
	init/init.c \
	init/init_camera.c \
	render/render.c \
	render/raycast.c \
	render/render_utils.c \
	render/light.c \
	render/shadow.c \
	objects/sphere.c \
	objects/plane.c \
	objects/cylinder.c\
	objects/hit_object.c \
	parsing/parser.c \
	parsing/parser_args.c \
	parsing/parser_debug.c \
	parsing/parser_utils.c \
	parsing/parser_file.c \
	parsing/parser_split.c \
	parsing/parser_validate.c \
	parsing/parser_validate2.c \
	parsing/parser_validate3.c \
	parsing/parser_fill.c \
	parsing/parser_fill_obj.c \
	parsing/parser_types.c \
	parsing/parser_content.c \
	parsing/parser_objects.c \
	parsing/parser_range.c \
	parsing/parser_check.c \
	parsing/parser_check_obj.c \
	parsing/parser_store.c \
	parsing/parser_store_obj.c \
	parsing/parser_free.c \

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAG) -o $(NAME)
	@echo "$(NAME) built successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "Building MLX..."
	@make -C $(MLX_DIR) 2>/dev/null || echo "MLX built"

clean:
	$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
