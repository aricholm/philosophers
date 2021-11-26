# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 15:03:55 by aricholm          #+#    #+#              #
#    Updated: 2021/11/19 11:02:17 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo
BONUS		= philo_bonus
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

OBJ_MANDATORY	= philosophers.o utils.o queue.o
OBJ_BONUS		= ./src/minitalk_server.o

all: $(NAME)

$(NAME): $(OBJ_MANDATORY)
	$(CC) -o $(NAME) $(OBJ_MANDATORY) -lpthread

$(BONUS): $(OBJ_BONUS)
	$(CC) -o $(NAME_CLNT) $(OBJ_CLIENT) -Lprintf -lftprintf

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	echo "Remove .o  ..."
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	$(MAKE) -C ./printf clean

fclean: clean
	echo "Remove executables and libraries ..."
	rm -f $(NAME_SERV) $(NAME_CLNT)
	$(MAKE) -C ./printf fclean

re: fclean all

.PHONY: all clean fclean re