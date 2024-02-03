/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:33:56 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:34:08 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd_lines	*cmd_lines;

	(void)argv;
	(void)argc;
	setup_lenv(env);
	g_gb.status_code = 0;
	cmd_lines = NULL;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	g_gb.hsig = 0;
	g_gb.stdin = dup(0);
	while (1)
	{
		cmd_lines = ft_parsing(cmd_lines);
		if (cmd_lines == NULL)
			continue ;
		execute_cmd(cmd_lines);
		free_nodes(cmd_lines);
	}
}

void	ctrl_c_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	g_gb.status_code = 1;
}

t_cmd_lines	*ft_parsing(t_cmd_lines *cmd_lines)
{
	t_parsing	parsing;
	char		*line;

	initialpars(&parsing);
	line = readline("[minishell][:)]~> ");
	if (line == NULL)
		(write(2, "exit\n", 5), exit(g_gb.status_code));
	if (!(*line))
		return (free(line), NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	(ft_spliting(line, &parsing), free(line));
	if (!parsing.prompt[0])
		return (0);
	tokening(&parsing);
	if (checkerrors(&parsing))
		return (0);
	(expand(&parsing), check_io(&parsing));
	if (g_gb.hsig)
	{
		g_gb.hsig = 0;
		return (freeparsing(&parsing), NULL);
	}
	cmd_lines = addtostruct(&parsing);
	return (freeparsing(&parsing), cmd_lines);
}
