# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 19:41:42 by rbuitrag          #+#    #+#              #
#    Updated: 2025/03/10 14:36:34 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
#-fsanitize=address -fsanitize=leak

HEADER = inc/philo.h

CFILES =  main.c\
		  create_pthread.c \
		  init_mutex_philo.c \
		  philo_routine.c \
		  custom_usleep.c \
		  		  		 

GREEN = "\033[92m" 
RESET = "\033[0m"

OBJS = $(addprefix src/, $(CFILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)		Successfully compiled!!$(RESET)
	@echo " "
	@echo " "
	$(CC) $(CFLAGS) -g $(OBJS) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

va: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q -s
	./philo

re: fclean all

.PHONY: all clean fclean re
