# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 04:37:29 by marcnava          #+#    #+#              #
#    Updated: 2025/04/28 21:51:38 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		:=	so_long
CC			:=	cc
RM			:=	rm -rf

CFLAGS		:=	-Wextra -Wall -Werror -g3
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
				$(UTILS)/error_handler.c \
				$(UTILS)/map_checker_utils.c

OBJS		:=	$(SRCS:$(SRCSPATH)/%.c=$(BUILD)/%.o)

# **************************************************************************** #
#		RULES		#

all: 			libs libmlx $(NAME)
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
.PHONY:		clean

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) libs/
.PHONY:		fclean

re:				fclean all
.PHONY:		re

bonus:			libmlx $(LIBFT)/libft.a
				make --no-print-directory -C _bonus/ all

libs:			libs/libft/Makefile libs/minilibx/CMakeLists.txt
.PHONY:			libs

libs/libft/Makefile:
				git clone https://github.com/marcnava-42cursus/libft libs/libft

libs/minilibx/CMakeLists.txt:
				git clone https://github.com/codam-coding-college/MLX42.git libs/minilibx

.PHONY:		bonus
