# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 14:39:41 by inosong           #+#    #+#              #
#    Updated: 2022/09/30 14:40:33 by inosong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out

#
# SRCS and OBJS
#

SRCS	=	\
			fdf.c

OBJS = $(SRCS:%.c=%.o)

#
# Compiler and flags
#

CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra
CLIB	=	-Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx

#
# Rules
#

all		: $(NAME)

%.o	:%.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf	$(NAME)

re		: fclean all