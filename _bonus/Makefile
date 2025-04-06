# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 16:38:07 by marcnava          #+#    #+#              #
#    Updated: 2025/04/06 20:33:54 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		:=	so_long
CC			:=	cc
RM			:=	rm -rf

CFLAGS		:=	-Wextra -Wall -Wunreachable-code -Ofast -g3
COMPILER	:=	$(CC) $(CFLAGS)

LIBFT		:=	../libs/libft
LIBMLX		:=	../libs/minilibx

MLX			:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

GAME_LANG	?=	en-US

# **************************************************************************** #
#		FILES		#

SRCSPATH	:=	./src
BUILD		:=	./build
UTILS		:=	$(SRCSPATH)/utils
MAP			:=	$(SRCSPATH)/map_utils
ERROR		:=	$(SRCSPATH)/error_utils
RENDER		:=	$(SRCSPATH)/render

HEADERS		:=	-I../includes -I$(LIBMLX)/include -I$(LIBFT)/includes

SRCS		=	$(SRCSPATH)/so_long_bonus.c

SRCS		+=	$(MAP)/error_handler_bonus.c \
				$(MAP)/flood_fill_bonus.c \
				$(MAP)/parse_map_bonus.c \
				$(MAP)/parse_map_utils_bonus.c

SRCS		+=	$(RENDER)/render_map_bonus.c \
				$(RENDER)/texture_error_bonus.c

SRCS		+=	$(UTILS)/exit_game_bonus.c \
				$(UTILS)/game_utils_bonus.c

OBJS		:=	$(SRCS:$(SRCSPATH)/%.c=$(BUILD)/%.o)

# **************************************************************************** #
#		RULES		#

all: 			libmlx $(NAME)
.PHONY:		all

libmlx:
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make --no-print-directory -s -C $(LIBMLX)/build -j4
.PHONY:		libmlx

$(LIBFT)/libft.a:
				@make --no-print-directory -s -C $(LIBFT) all
				
$(NAME):		$(OBJS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
				$(CC) $(HEADERS) $(OBJS) $(MLX) -L$(LIBFT) -lft -o ../$(NAME)

$(BUILD)/%.o: $(SRCSPATH)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -D LANG=\"$(GAME_LANG)\" -o $@ -c $< $(HEADERS)

clean:
				@$(RM) $(BUILD)
				@make --no-print-directory -s -C $(LIBFT) clean
.PHONY:		clean

fclean:			clean
				@$(RM) $(NAME)
				@make --no-print-directory -s -C $(LIBFT) fclean
.PHONY:		fclean

re:				fclean all
.PHONY:		re