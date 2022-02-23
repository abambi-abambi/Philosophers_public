# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abambi <abambi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 15:51:33 by abambi            #+#    #+#              #
#    Updated: 2021/09/25 18:27:55 by abambi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = a_main.c \
	b_malloc_init.c \
	c_life.c \
	d_end_the_game.c \
	e_lib_utils.c \
	g_ph_utils.c \
	h_ph_utils2.c \

OBJS = $(SRC:.c=.o)

INC = ./

RM	= rm -f
GCC = gcc -g
FLAGS = -Wall -Wextra -Werror -pthread

$(NAME): $(OBJS) Makefile $(INC)philosophers.h
	$(GCC) $(FLAGS) $(OBJS) -I$(INC) -o $(NAME)

PHONY:	all clean fclean re

all: $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} $(NAME)

re: fclean all
