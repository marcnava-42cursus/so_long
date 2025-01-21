# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 18:09:00 by marcnava          #+#    #+#              #
#    Updated: 2025/01/21 18:17:41 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *************************************************************************** #
#		VARIABLES	#

NAME		=	gnl.a

CC			=	cc
RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror

COMPILER	=	$(CC) $(CFLAGS)
LIB			=	ar rcs

# *************************************************************************** #
#		FILES		#

SRCS		=	get_next_line.c \
				get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

# *************************************************************************** #
#		RULES		#

all: 			$(NAME)

$(NAME):		$(OBJS)
				$(LIB) $(NAME) $(OBJS)

.o:				.c
				$(COMPILER) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus