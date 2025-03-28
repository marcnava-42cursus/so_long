# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2025/03/28 22:45:08 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		:=	so_long
CC			:=	cc
RM			:=	rm -rf

CFLAGS		:=	-Wextra -Wall -Werror -Wunreachable-code -Ofast -g3
COMPILER	:=	$(CC) $(CFLAGS)

LIBFT		:=	./libs/libft
LIBMLX		:=	./libs/minilibx

MLX			:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# **************************************************************************** #
#		FILES		#

SRCSPATH	:=	./src
BUILD		:=	./build
UTILS		:=	$(SRCSPATH)/utils
HEADERS		:=	-I./includes -I$(LIBMLX)/include -I$(LIBFT)/includes

SRCS 		=	$(SRCSPATH)/so_long.c \
				$(SRCSPATH)/game_utils.c \
				$(SRCSPATH)/print_map.c \
				$(SRCSPATH)/draw_map.c \
				$(SRCSPATH)/movement.c

SRCS		+=	$(UTILS)/map_checker.c \
				$(UTILS)/flood_fill.c \
				$(UTILS)/error_handler.c

OBJS		:=	$(SRCS:$(SRCSPATH)/%.c=$(BUILD)/%.o)

# **************************************************************************** #
#		RULES		#

all: 			libmlx $(NAME)

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make --no-print-directory -s -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -s -C $(LIBFT)

$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
				@$(CC) $(HEADERS) $(OBJS) $(MLX) -L$(LIBFT) -lft -o $(NAME)

$(BUILD)/%.o:	$(SRCSPATH)/%.c
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
