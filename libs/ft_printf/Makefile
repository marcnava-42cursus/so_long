# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 17:33:23 by marcnava          #+#    #+#              #
#    Updated: 2025/01/21 16:58:37 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *************************************************************************** #
#		VARIABLES	#

NAME		=	libftprintf.a

CC			=	cc
RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror

COMPILER	=	$(CC) $(CFLAGS)
LIB			=	ar rcs

LIBFT		=	./libft

# *************************************************************************** #
#		FILES		#

SRCS 		=	\
				ft_printf.c \
				ft_printf_utils.c \
				ft_conversion_utils.c \
				ft_mod_printf.c

OBJS		=	$(SRCS:.c=.o)

# *************************************************************************** #
#		RULES		#

all: 			$(NAME)

$(LIBFT)/libft.a:
				@$(MAKE) --no-print-directory -C $(LIBFT)

$(NAME):		$(OBJS) $(LIBFT)/libft.a
				$(LIB) $(NAME) $(OBJS) $(LIBFT)/libft.a
				@$(MAKE) fclean --no-print-directory -C $(LIBFT)

.o:				.c
				$(COMPILER) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus