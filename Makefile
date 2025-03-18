# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2025/03/07 20:16:50 by marcnava         ###   ########.fr        #
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
BUILD		=	./build

SRCS 		=	$(SRCSPATH)/so_long.c \
				$(SRCSPATH)/game_utils.c

OBJS		=	$(SRCS:$(SRCSPATH)/%.c=$(BUILD)/%.o)

# **************************************************************************** #
#		ARCHIVOS	#

HEADERS		=	-I ./includes -I $(LIBMLX)/include -I $(LIBFT)/includes

# **************************************************************************** #
#		OBJETIVOS	#

all: 			libmlx $(NAME)

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make --no-print-directory -s -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -s -C $(LIBFT)

$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
				@$(CC) $(HEADERS) $(OBJS) $(MLX) -L$(LIBFT) -lft -o $(NAME)

$(BUILD)/%.o: $(SRCSPATH)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
				@$(RM) $(BUILD)
				@$(RM) $(LIBMLX)/build
				@$(MAKE) --no-print-directory -s -C $(LIBFT) clean

fclean:			clean
				@$(RM) $(NAME)
				@$(MAKE) --no-print-directory -s -C $(LIBFT) fclean

re:				fclean all

.PHONY:			all clean fclean re libmlx
