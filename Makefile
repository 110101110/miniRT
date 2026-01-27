# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:17:44 by qizhang           #+#    #+#              #
#    Updated: 2026/01/27 16:13:19 by qizhang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
BONUS_NAME = miniRT_bonus

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR	= src
INC_DIR	= includes
OBJ_DIR	= obj
LIBFT_DIR = libft
MLX_DIR = mlx_macos

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# mlx library
# OS		= $(shell uname -s)
# ifeq ($(OS), Linux)
# 	MLX_FLAG = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
# 	INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -Isrc/math
# else
MLX_FLAG = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -Isrc/math
# endif

# 1. SHARED FILES (Math & Utils - Used by both Mandatory and Bonus)
SRC_SHARED_FILES = \
	math/vector_1.c \
	math/vector_2.c \
	math/colors.c \
	utils/errors.c \
	utils/clean_exit.c

SRC_MAND_FILES = \
	mandatory/main.c \
	mandatory/init/init.c \
	mandatory/init/init_camera.c \
	mandatory/render/render.c \
	mandatory/render/raycast.c \
	mandatory/render/render_utils.c \
	mandatory/render/light.c \
	mandatory/render/shadow.c \
	mandatory/parsing/parser.c \
	mandatory/objects/sphere.c \
	mandatory/objects/plane.c \
	mandatory/objects/cylinder.c\
	mandatory/objects/hit_object.c

# 3. BONUS FILES

# SRC_BONUS_FILES = \
# 	bonus/main_bonus.c \
# 	bonus/init/mlx_setup_bonus.c \
# 	bonus/render/render_bonus.c \
# 	bonus/render/render_utils.c \
# 	bonus/parsing/parser_bonus.c \
# 	bonus/objects/intersect_sphere.c

OBJ_MAND = $(addprefix $(OBJ_DIR)/, $(SRC_MAND_FILES:.c=.o))
OBJ_SHARED = $(addprefix $(OBJ_DIR)/, $(SRC_SHARED_FILES:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS_FILES:.c=.o))

ALL_OBJS_MAND = $(OBJ_MAND) $(OBJ_SHARED)
ALL_OBJS_BONUS = $(OBJ_BONUS) $(OBJ_SHARED)

all: $(LIBFT) $(MLX) $(NAME)

# Link Mandatory
$(NAME): $(ALL_OBJS_MAND)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(ALL_OBJS_MAND) $(LIBFT) $(MLX_FLAG) -o $(NAME)
	@echo "$(NAME) built successfully!"

# Link Bonus
bonus: $(LIBFT) $(MLX) $(BONUS_NAME)

$(BONUS_NAME): $(ALL_OBJS_BONUS)
	@echo "Linking $(BONUS_NAME)..."
	$(CC) $(CFLAGS) $(ALL_OBJS_BONUS) $(LIBFT) $(MLX_FLAG) -o $(BONUS_NAME)
	@echo "$(BONUS_NAME) built successfully!"

# Compile Objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Libft
$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

# Compile MLX
$(MLX):
	@echo "Building MLX..."
	@make -C $(MLX_DIR) 2>/dev/null || echo "MLX built"

# Cleanup
clean:
	$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
