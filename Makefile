# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2024/12/13 03:57:10 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		=	so_long
CC			=	cc
RM			=	rm -rf

# CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code -Ofast
COMPILER	=	$(CC) $(CFLAGS)

LIBFT		=	./libs/libft
LIBMLX		=	./libs/minilibx
MLX			=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCSPATH	=	./src

SRCS 		=	$(SRCSPATH)/so_long.c

OBJS		=	$(SRCS:.c=.o)

# **************************************************************************** #
#		ARCHIVOS	#

HEADERS		=	-I ./include -I $(LIBMLX)/include

# **************************************************************************** #
#		OBJETIVOS	#

all: 			libmlx compiling $(NAME)

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -C $(LIBFT)

$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
				@$(CC) $(HEADERS) $(OBJS) $(MLX) $(LIBFT)/libft.a -o $(NAME)
				@printf "Compilado.\n"

%.o: %.c
				@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(LIBMLX)/build

fclean:			clean
				@$(RM) $(NAME)

compiling:
				@printf "Compilando el programa...\n"

re:				fclean all

.PHONY:			all clean fclean re libmlx compiling
