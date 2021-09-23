# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 22:44:02 by evila-ro          #+#    #+#              #
#    Updated: 2021/09/18 20:19:32 by evila-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-fsanitize=address

NAME	= philo

SRCS	= ./init.c ./liba.c ./checkin.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I -g3 -fsanitize=address

LIBS	= -pthread

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} ${LIBS} ${OBJS} -o ${NAME}

all:	${NAME}

clean:
		@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
#ifeq ($(shell whoami), runner)
#	COVID_NORM		=	ruby ~/.norminette/norminette.rb
#else
#	COVID_NORM		=	ruby -e STDOUT.sync=true -e 'load($$0=ARGV.shift)' ~/.norminette/norminette.rb
#endif
