# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 15:03:55 by aricholm          #+#    #+#              #
#    Updated: 2021/12/11 16:32:08 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
BONUS		= philo_bonus
CFLAGS		= -Wall -Wextra -Werror

OBJ_MANDATORY	=	./philo_m/philosophers.o\
					./philo_m/utils.o\
					./philo_m/actions.o\
					./philo_m/error.o
					
OBJ_BONUS		=	./philo_b/philosophers.o\
					./philo_b/utils.o\
					./philo_b/actions.o\
					./philo_b/error.o
all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ_MANDATORY)
	$(CC) -o $(NAME) $(OBJ_MANDATORY) -lpthread

$(BONUS): $(OBJ_BONUS)
	$(CC) -o $(BONUS) $(OBJ_BONUS) -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	echo "Remove .o  ..."
	rm -f $(OBJ_MANDATORY) $(OBJ_BONUS) 

fclean: clean
	echo "Remove executables and libraries ..."
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus