/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:02 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:34:04 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./builtins/builtins.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

typedef struct s_parsing
{
	char				**prompt;
	char				*tokens;
	size_t				size;
	size_t				cmd_size;
	int					*infiles;
	int					*outfiles;
}						t_parsing;

typedef struct s_cmd_lines
{
	char				*path;
	char				**args;
	int					infile;
	int					outfile;
	struct s_cmd_lines	*next;
}						t_cmd_lines;

typedef struct s_utils
{
	int					first_pipe;
	char				prev_token;
}						t_utils;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_g_gb
{
	t_env				*env;
	int					status_code;
	int					hsig;
	int					stdin;
}						t_gb;

t_gb					g_gb;

// utils:
void					initialcmd(t_cmd_lines *cmd_lines);
void					initialpars(t_parsing *parsing);
int						ft_strcmp(char *line, char *str);
int						dquoting(char *line, char c, int i);
size_t					sizeofprompt(char *line);
int						checkerrors(t_parsing *parsing);
void					ft_checkingdupp(char *line, size_t *i);
size_t					remove_quote(char **line, size_t start, size_t end,
							t_utils *utils);
void					commands_size(t_parsing *parsing);
size_t					find_equal(char *env);
void					setup_args_utils(t_parsing *parsing, size_t cmd_index,
							size_t *i);
char					*ft_norm(char *delimiter, int first_pipe, char *line);

// structs:
t_cmd_lines				*ft_parsing(t_cmd_lines *cmd_lines);
void					ft_spliting(char *line, t_parsing *parsing);
void					tokening(t_parsing *parsing);
t_cmd_lines				*addtostruct(t_parsing *parsing);
void					setup_lenv(char **env);

// expand:
void					expand_var(char **line, size_t start, int first_pipe);
void					expand(t_parsing *parsing);
void					expand_line(char **line, int first_pipe,
							char prev_token);
void					expand_var(char **line, size_t start, int first_pipe);
char					*find_expand_var(char *line, size_t start, size_t *end,
							int first_pipe);

// error:

void					errorandprint(char *msg, int value);
void					errorandprint2(char *msg, int value, char *str);
void					ctrl_c_handler(int signal);
// freeing:
void					dfree(char **str);
void					free_nodes(t_cmd_lines *cmd_lines);
void					freedouble(t_parsing *parsing);
void					freeparsing(t_parsing *parsing);

// infile and outfile:
void					check_io(t_parsing *parsing);
int						open_here_doc(char *delimiter, int first_pipe);

// execution:
void					execute_cmd(t_cmd_lines *cmd_lines);
//void					rl_replace_line(const char *text, int clear_undo);
void					execute_mini(t_cmd_lines *cmd_lines);
void					ft_execve(t_cmd_lines *cmd_lines);
int						ft_exec_cmd(t_cmd_lines *cmd_lines, int prev_fd);
void					sigquit_handler(int signal);
char					**reverse_env(t_env *env);
char					*strjoin_del(char *str1, char *str2, char *delimiter);
int						is_builtin(t_cmd_lines *cmd_lines);
void					exec_builtin(t_cmd_lines *cmd_lines, int outfile);
void					ifexec(t_cmd_lines *cmd_lines, char **env);
void					handlepipe(t_cmd_lines *cmd_lines, int prev_fd,
							int fd[2]);
void					replacexisted(t_env *new, char **split);
void					addenvanyway(t_env *new, char **split);
void					ft_lstadd_back2(t_env **lst, t_env *new);

// signal:
void					ctrl_c_handler(int signal);
void					here_doc_controller(int signal);
#endif