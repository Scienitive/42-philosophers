# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 22:37:55 by alyasar           #+#    #+#              #
#    Updated: 2022/06/18 15:03:38 by alyasar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

INC			=	./inc/

CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra -I$(INC) -pthread

SRCS		=	$(shell find ./srcs -name "*.c")
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:	
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re