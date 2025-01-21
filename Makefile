# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2025/01/21 19:31:03 by marcnava         ###   ########.fr        #
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
LIBPRINTF	=	./libs/ft_printf
LIBGNL		=	./libs/get_next_line

MLX			=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCSPATH	=	./src

SRCS 		=	$(SRCSPATH)/so_long.c		\
				$(SRCSPATH)/game_init.c		\
				$(SRCSPATH)/map_reader.c

OBJS		=	$(SRCS:.c=.o)

# **************************************************************************** #
#		ARCHIVOS	#

HEADERS		=	-I ./include -I $(LIBMLX)/include

# **************************************************************************** #
#		OBJETIVOS	#

all: 			libmlx compiling $(NAME)

getlibs:
				@printf "Cloning libft\n"
				@git clone https://github.com/marcnava-42cursus/libft.git ./libs/libft >/dev/null 2>&1
				@printf "Cloning minilibx\n"
				@git clone https://github.com/codam-coding-college/MLX42.git ./libs/minilibx >/dev/null 2>&1
				@printf "Cloning ft_printf\n"
				@git clone https://github.com/marcnava-42cursus/ft_printf.git ./libs/ft_printf >/dev/null 2>&1
				@printf "Cloning get_next_line\n"
				@git clone https://github.com/marcnava-42cursus/get_next_line.git ./libs/get_next_line >/dev/null 2>&1

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -C $(LIBFT)

$(LIBPRINTF)/libftprintf.a:
				@$(MAKE) --no-print-directory -C $(LIBPRINTF)

$(LIBGNL)/gnl.a:
				@$(MAKE) --no-print-directory -C $(LIBGNL)

$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(LIBPRINTF)/libftprintf.a $(LIBGNL)/gnl.a
				@$(CC) $(HEADERS) $(OBJS) $(MLX) -L$(LIBFT)/libft.a -L$(LIBPRINTF)/libftprintf.a -L$(LIBGNL)/gnl.a -o $(NAME)
				@printf "Compilado.\n"

%.o: %.c
				@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(LIBMLX)/build

fclean:			clean
				@$(RM) ./libs
				@$(RM) $(NAME)

compiling:
				@printf "Compilando el programa...\n"

re:				fclean all

.PHONY:			all clean fclean re libmlx compiling getlibss
