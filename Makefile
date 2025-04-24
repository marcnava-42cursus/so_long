# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2025/04/24 02:26:18 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		:=	so_long
CC			:=	cc
RM			:=	rm -rf

CFLAGS		:=	-Wextra -Wall -Werror -Wunreachable-code -Ofast
COMPILER	:=	$(CC) $(CFLAGS)

LIBFT		:=	./libs/libft
LIBMLX		:=	./libs/minilibx

MLX			:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

GAME_LANG	?=	en-US

# **************************************************************************** #
#		FILES		#

SRCSPATH	:=	./src
BUILD		:=	./build
UTILS		:=	$(SRCSPATH)/utils
HEADERS		:=	-I./includes -I$(LIBMLX)/include -I$(LIBFT)/includes

SRCS 		=	$(SRCSPATH)/so_long.c \
				$(SRCSPATH)/game_utils.c \
				$(SRCSPATH)/draw_map.c \
				$(SRCSPATH)/draw_map_utils.c \
				$(SRCSPATH)/movement.c \
				$(SRCSPATH)/exit_game.c

SRCS		+=	$(UTILS)/map_checker.c \
				$(UTILS)/flood_fill.c \
				$(UTILS)/flood_fill_utils.c \
				$(UTILS)/error_handler.c

OBJS		:=	$(SRCS:$(SRCSPATH)/%.c=$(BUILD)/%.o)

# **************************************************************************** #
#		RULES		#

all: 			libmlx $(NAME)
.PHONY:		all

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make --no-print-directory -s -C $(LIBMLX)/build -j4
.PHONY:		libmlx

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -s -C $(LIBFT)

$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
				@$(CC) $(HEADERS) $(OBJS) $(MLX) -L$(LIBFT) -lft -o $(NAME)

$(BUILD)/%.o:	$(SRCSPATH)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -D LANG=\"$(GAME_LANG)\" -o $@ -c $< $(HEADERS)

clean:
				@$(RM) $(BUILD)
				@$(RM) $(LIBMLX)/build
				@$(MAKE) --no-print-directory -s -C $(LIBFT) clean
.PHONY:		clean

fclean:			clean
				@$(RM) $(NAME)
				@$(MAKE) --no-print-directory -s -C $(LIBFT) fclean
.PHONY:		fclean

re:				fclean all
.PHONY:		re

bonus:			libmlx $(LIBFT)/libft.a
				@make --no-print-directory -s -C _bonus/ all
.PHONY:		bonus
