NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror

LIBS = -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include -L libft -lft  -lcurses -fsanitize=address -g3

SRCS = 	minishell.c\
		tools.c\
		tools2.c\
		tools3.c\
		spliting.c\
		size_of_prompt.c\
		tokens.c\
		error.c\
		ft_norm.c\
		to_cmd_struct.c\
		expand.c\
		in_out.c\
		./execution/execute_cmd.c\
		./execution/execution_utils.c\
		./builtins/ft_echo.c\
		./builtins/ft_cd.c\
		./builtins/ft_pwd.c\
		./builtins/ft_export.c\
		./builtins/ft_unset.c\
		./builtins/ft_env.c\
		./builtins/ft_exit.c\
		./builtins/export_utils.c\
		
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@stty -echoctl
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[1;32mminishell is ready to go!\033[0;0m 🔥"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "\033[1;31mminishell objects are deleted\033[0;0m 🗑️"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "\033[1;31mminishell is deleted\033[0;0m 🗑️"

re: fclean all

.PHONY: all clean fclean re