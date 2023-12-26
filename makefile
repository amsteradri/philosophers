# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 17:33:47 by adgutier          #+#    #+#              #
#    Updated: 2023/12/26 13:02:50 by adgutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS			= philo.c forks.c eat_sleep_think.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror -pthread 

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)
		rm -rf philo.a
		rm -rf philo


re: fclean all

.PHONY: all re clean fclean