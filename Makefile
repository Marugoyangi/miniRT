# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 19:04:30 by jeongbpa          #+#    #+#              #
#    Updated: 2024/03/06 08:25:08 by jeongbpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
BONUS_DIR = ./bonus_srcs/

SRCS =	$(addprefix $(SRC_DIR), main.c\
								utils/utils.c utils/random.c utils/rng.c utils/free.c\
								utils/get_next_line.c utils/get_next_line_utils.c\
								utils/parse_utils.c\
								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c vector/vector_utils.c\
								transform/transform.c transform/transform_aabb.c transform/matrix.c\
								transform/hit_transformed.c transform/matrix_inverse.c\
								ray/ray.c ray/scatter.c ray/volume.c ray/material.c ray/pdf.c ray/pdf_object.c\
								ray/pdf_mixture.c\
								camera/camera.c camera/camera_utils.c\
								color/color.c color/render.c color/diffuse.c\
								object/object.c object/sphere.c object/quad.c object/box.c object/cylinder.c\
								object/hyperboloid.c\
								bvh/bvh.c bvh/bvh_utils.c bvh/bvh_compare.c \
								bvh/interval.c bvh/aabb.c bvh/aabb_utils.c \
								texture/checker.c texture/image.c texture/perlin.c texture/perlin_utils.c\
								control/key.c\
								parse/parse.c parse/init_env.c parse/init_material.c parse/init_obj.c\
								parse/parse_obj.c parse/parse_material.c parse/parse_env.c\
								test.c)

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 
# BONUS_SRCS =	$(addprefix $(SRC_DIR), main.c utils.c\
# 								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c \
# 								ray/ray.c \
# 								color/color.c color/print.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = minirt.h
HEADER_BONUS = minirt_bonus.h
CFLAGS = -I./mlx_linux -I./includes/ -I./libft -O3 -g3 #-Wall -Wextra -Werror

CC = cc
NAME = minirt
LIBMLX = ./mlx/libmlx.a
LIBFT = ./libft/libft.a


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
	$(CC) $^ -O3 -g3 -Lmlx -lmlx -L./libft/ -lft -lm -framework OpenGL -framework AppKit -o $(NAME)
	
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