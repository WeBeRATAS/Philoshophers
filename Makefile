# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 19:41:42 by rbuitrag          #+#    #+#              #
#    Updated: 2025/03/10 19:13:24 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread #-fsanitize=leak

HEADER = inc/philo.h

CFILES =  main.c\
		  philo_actions.c \
		  check_args.c \
		  control_time.c \
		  utils.c \
		  		  		 

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
	rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

va: all
	valgrind --leak-check=full --show-leak-kinds=all -q -s ./philo 8 100 100 100
	5

re: fclean all

.PHONY: all clean fclean re
