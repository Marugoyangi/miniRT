# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongbpa <jeongbpa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 15:37:02 by jeongbpa          #+#    #+#              #
#    Updated: 2024/03/07 17:55:51 by jeongbpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
				ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
				ft_toupper.c ft_tolower.c ft_strrchr.c \
				ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c \
				ft_split.c ft_itoa.c \
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_strstr.c

OBJS			= $(SRCS:.c=.o)

CC				=	cc

RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror -I.

NAME			=	libft.a

ifdef BONUS_FLAG
OBJ_FLAG = $(OBJS)
else
OBJ_FLAG = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJ_FLAG)
	ar rcs $(NAME) $(OBJ_FLAG)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean $(NAME)

bonus:
	@make BONUS_FLAG=1 $(NAME)

.PHONY: all clean fclean re bonus