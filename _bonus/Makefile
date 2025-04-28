# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 16:38:07 by marcnava          #+#    #+#              #
#    Updated: 2025/04/28 09:04:48 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#		VARIABLES	#

NAME		:=	so_long
CC			:=	cc
RM			:=	rm -rf

CFLAGS		:=	-Wextra -Wall -g3
COMPILER	:=	$(CC) $(CFLAGS)

LIBFT		:=	../libs/libft
LIBMLX		:=	../libs/minilibx

MLX			:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

GAME_LANG	?=	en-US

# **************************************************************************** #
#		FILES		#

SRCSPATH	:=	./src
BUILD		:=	./build
CONTROL		:=	$(SRCSPATH)/control
EXECUTION	:=	$(SRCSPATH)/execution
INPUT		:=	$(SRCSPATH)/input
MAP			:=	$(SRCSPATH)/map
FLOODFILL	:=	$(MAP)/flood_fill
PARSING		:=	$(MAP)/parsing
RENDER		:=	$(SRCSPATH)/render
UTILS		:=	$(SRCSPATH)/utils

HEADERS		:=	-I../includes -I$(LIBMLX)/include -I$(LIBFT)/includes

SRCS		=	$(SRCSPATH)/so_long_bonus.c

SRCS		+=	$(CONTROL)/block_bonus.c \
				$(CONTROL)/control_utils_bonus.c \
				$(CONTROL)/generation_bonus.c \
				$(CONTROL)/instructions_bonus.c \
				$(CONTROL)/movement_checks_bonus.c \
				$(CONTROL)/movement_effects_bonus.c \
				$(CONTROL)/orientation_bonus.c \
				$(CONTROL)/push_utils_bonus.c

SRCS		+=	$(EXECUTION)/ship_actions_bonus.c \
				$(EXECUTION)/ship_checks_bonus.c

SRCS		+=	$(INPUT)/key_handler_bonus.c

SRCS		+=	$(MAP)/error_handler_bonus.c \
				$(MAP)/map_utils_bonus.c \
				$(MAP)/validation_bonus.c

SRCS		+=	$(FLOODFILL)/flood_fill_bonus.c \
				$(FLOODFILL)/flood_fill_utils_bonus.c

SRCS		+=	$(PARSING)/map_io_bonus.c \
				$(PARSING)/memory_helpers_bonus.c \
				$(PARSING)/parse_map_bonus.c

SRCS		+=	$(RENDER)/baba_renderer_bonus.c \
				$(RENDER)/map_renderer_core_bonus.c \
				$(RENDER)/map_renderer_utils_bonus.c \
				$(RENDER)/ui_renderer_bonus.c

SRCS		+=	$(UTILS)/debug_bonus.c \
				$(UTILS)/exit_bonus.c \
				$(UTILS)/init_game_bonus.c

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
				$(CC) $(CFLAGS) -D LANG=\"$(GAME_LANG)\" -o $@ -c $< $(HEADERS)

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