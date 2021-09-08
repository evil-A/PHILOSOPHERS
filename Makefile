#-fsanitize=address

NAME	= philo.a
OUTPUT	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread -g3 

ifeq ($(shell whoami), runner)
	COVID_NORM		=	ruby ~/.norminette/norminette.rb
else
	COVID_NORM		=	ruby -e STDOUT.sync=true -e 'load($$0=ARGV.shift)' ~/.norminette/norminette.rb
endif

SRC	= srcs/main.c	srcs/liba.c	srcs/checkin.c

OBJ	= $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(SRC) srcs/philo.h
	@gcc $(CFLAGS) $(SRC)
	@ar -r $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(NAME) -o $@

clean:
	@rm -f *.o
	@rm -f *.out

fclean: clean
	@rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
