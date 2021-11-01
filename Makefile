# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 13:37:33 by mzomeno-          #+#    #+#              #
#    Updated: 2021/11/01 19:08:22 by mzomeno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror

NAME = philo

N_PHILOS 		= 5
TIME_TO_DIE 	= 200
TIME_TO_EAT 	= 42
TIME_TO_SLEEP 	= 58

SRCS = 	main.c \
		init.c \
		utils.c \
		simulation.c
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


test: re
	./$(NAME) $(N_PHILOS) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP)


.PHONY: all clean fclean re test
