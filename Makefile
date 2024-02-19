# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 19:04:30 by jeongbpa          #+#    #+#              #
#    Updated: 2024/02/19 20:22:05 by seungwok         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
BONUS_DIR = ./bonus_srcs/

SRCS =	$(addprefix $(SRC_DIR), main.c\
								utils/utils.c utils/random.c\
								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c vector/vector_utils.c\
								transform/transform.c transform/transform_aabb.c transform/matrix.c\
								transform/hit_transformed.c\
								ray/ray.c ray/scatter.c ray/volume.c ray/material.c\
								camera/camera.c camera/camera_utils.c\
								color/color.c color/render.c color/diffuse.c\
								object/object.c object/sphere.c object/quad.c object/box.c\
								bvh/bvh.c bvh/bvh_utils.c bvh/bvh_compare.c \
								bvh/interval.c bvh/aabb.c bvh/aabb_utils.c \
								texture/checker.c texture/image.c texture/perlin.c\
								control/key.c\
								gnl/get_next_line.c
								)
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 
# BONUS_SRCS =	$(addprefix $(SRC_DIR), main.c utils.c\
# 								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c \
# 								ray/ray.c \
# 								color/color.c color/print.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = minirt.h
HEADER_BONUS = minirt_bonus.h
CFLAGS = -Wall -Wextra -Werror -I./mlx -I./includes/ -O3 -g3

CC = cc
NAME = minirt
LIBFT = ./libft/libft.a
LIBMLX = ./mlx/libmlx.a

ifeq ($(BONUS_FLAG), 42)
	OBJ_FLAG = $(BONUS_OBJS)
	OBJ_EXCEPT = $(OBJS)
	OBJ_HEADER = $(HEADER_BONUS)
else
	OBJ_FLAG = $(OBJS)
	OBJ_EXCEPT = $(BONUS_OBJS)
	OBJ_HEADER = $(HEADER)
endif

%.o: %.c $(OBJ_HEADER)
	 $(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ_FLAG) $(LIBMLX) $(LIBFT)
	@rm -f $(OBJ_EXCEPT)
	$(CC) $^ -O3 -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	
$(LIBMLX):
	@make -C mlx

$(LIBFT):
	@make -C libft

all: $(NAME)

bonus: 
	@make BONUS_FLAG=42 $(NAME)
		
re: fclean all

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C mlx clean
	@$(MAKE) -C ./libft fclean

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re bonus