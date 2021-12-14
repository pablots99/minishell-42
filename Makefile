NAME=minishell

SRCS =	minishell.c 							\
		srcs/parser/parse_comands.c				\
		srcs/parser/tokens.c					\
		srcs/parser/parse_aux.c					\
		srcs/parser/parse_aux2.c				\
		srcs/parser/parse_errors.c				\
		srcs/execution/execute_command.c		\
		srcs/execution/execute_command_aux.c	\
		srcs/execution/signal__handler.c 		\
		srcs/builtins/env.c						\
		srcs/builtins/pwd_cd.c					\
		srcs/builtins/echo.c					\
		srcs/builtins/export.c					\
		srcs/builtins/exit.c					\
		srcs/builtins/unset.c					\
		srcs/builtins/session_vars.c			\
		srcs/utils/utils.c						\
		srcs/utils/utils1.c						\
		srcs/utils/utils2.c						\
		srcs/utils/utils3.c						\
		srcs/utils/utils4.c						\
		srcs/utils/utils5.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Wall -Werror -Wextra -g3

#campues
LIBFLAGS = -L. libft/libft.a -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include
export LDFLAGS="-L/Users/${USER}/.brew/opt/readline/lib"
export CPPFLAGS="-I/Users/${USER}/.brew/opt/readline/include"

#mac
# export LDFLAGS="-L/usr/local/opt/readline/lib"
# export CPPFLAGS="-I/usr/local/opt/readline/include"
# LIBFLAGS = -L. libft/libft.a -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
#-fsanitize=address


FLAGS = -lreadline  -o $(NAME)


all:$(NAME)

$(NAME):$(OBJS)
	$(MAKE) bonus -C ./libft
	$(CC) $(FLAGS) $(LIBFLAGS) $(OBJS)

clean:
	$(stty -echoctlexp)
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm $(NAME)

re: fclean all
