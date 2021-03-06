# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 13:37:33 by mzomeno-          #+#    #+#              #
#    Updated: 2021/11/10 16:32:28 by mzomeno-         ###   ########.fr        #
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
		simulation.c \
		termination.c
OBJS = 	$(SRCS:.c=.o)


all: $(NAME)


%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	${COMPILER} ${FLAGS} $(OBJS) -o $(NAME)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)


re: fclean all


test: fclean all
	./$(NAME) $(N_PHILOS) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP)


.PHONY: all clean fclean re test
