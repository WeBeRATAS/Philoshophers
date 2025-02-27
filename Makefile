# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 19:41:42 by rbuitrag          #+#    #+#              #
#    Updated: 2025/02/27 19:45:29 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iinc -g -fsanitize=address -fsanitize=leak

MODE = null
HEADER = inc/philo.h
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

CFILES =  main.c\
		  		  
OBJS = $(addprefix src/, $(CFILES:.c=.o))


all: library $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

library:
	@make -C libft
	@make -C printf
	
clean:
	@make clean -C printf
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C printf
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re library
