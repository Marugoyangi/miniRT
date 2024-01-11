# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 19:04:30 by jeongbpa          #+#    #+#              #
#    Updated: 2024/01/11 16:57:19 by jeongbpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
BONUS_DIR = ./bonus_srcs/

SRCS =	$(addprefix $(SRC_DIR), main.c utils.c\
								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c \
								ray/ray.c \
								color/color.c color/print.c)
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = 
# BONUS_SRCS =	$(addprefix $(SRC_DIR), main.c utils.c\
# 								vector/vector_ops.c vector/vector_cals.c vector/vector_const.c \
# 								ray/ray.c \
# 								color/color.c color/print.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = minirt.h
HEADER_BONUS = minirt_bonus.h
CFLAGS = -Wall -Wextra -Werror -I./mlx -I./includes/

CC = CC
NAME = minirt
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

$(NAME): $(OBJ_FLAG) $(LIBMLX)
	@rm -f $(OBJ_EXCEPT)
	$(CC) $^ -O3 -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	
$(LIBMLX):
	@make -C mlx

all: $(NAME)

bonus: 
	@make BONUS_FLAG=42 $(NAME)
		
re: fclean all

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C mlx clean

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re bonus