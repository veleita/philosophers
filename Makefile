# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 13:37:33 by mzomeno-          #+#    #+#              #
#    Updated: 2021/11/11 09:57:31 by mzomeno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g

NAME = philo

N_PHILOS 		= 5
TIME_TO_DIE 	= 800
TIME_TO_EAT 	= 200
TIME_TO_SLEEP 	= 200
N_MEALS 		= 7

SRCS = 	main.c \
		init.c \
		utils.c \
		custom_utils.c \
		life_cycle.c \
		termination.c \
		simulation.c
OBJS = 	$(SRCS:.c=.o)

OTHER_GARBAGE = *.dSYM .*.swp tags

all: $(NAME)


%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	${COMPILER} ${FLAGS} $(OBJS) -o $(NAME)


clean:
	rm -f $(OBJS)
	rm -rf $(OTHER_GARBAGE)

fclean: clean
	rm -f $(NAME)


re: fclean all


test: re
	./$(NAME) $(N_PHILOS) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP) $(N_MEALS)


.PHONY: all clean fclean re test
