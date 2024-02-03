/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:17:38 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:17:45 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ifexec(t_cmd_lines *cmd_lines, char **env)
{
	if (is_builtin(cmd_lines))
		exec_builtin(cmd_lines, 1);
	else if (execve(cmd_lines->path, cmd_lines->args, env) == -1)
	{
		printf("minishell: %s: command not found\n", cmd_lines->args[0]);
		g_gb.status_code = 127;
	}
	exit(g_gb.status_code);
}

void	handlepipe(t_cmd_lines *cmd_lines, int prev_fd, int fd[2])
{
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	if (prev_fd > 0)
		(dup2(prev_fd, 0), close(prev_fd));
	if (cmd_lines->infile > 0)
		(dup2(cmd_lines->infile, 0), close(cmd_lines->infile));
	if (cmd_lines->next)
		(dup2(fd[1], 1), close(fd[1]));
	if (cmd_lines->outfile > 1)
		(dup2(cmd_lines->outfile, 1), close(cmd_lines->outfile));
	(close(fd[0]), close(fd[1]));
}

void	sigquit_handler(int signal)
{
	(void)signal;
	write(1, "Quit: 3\n", 8);
}

char	**reverse_env(t_env *env)
{
	t_env	*tmp;
	char	**result;
	int		counter;
	int		i;

	i = 0;
	env = g_gb.env;
	tmp = env;
	counter = 0;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	result = (char **)malloc(sizeof(char *) * (counter + 1));
	result[counter] = NULL;
	tmp = env;
	while (tmp)
	{
		result[i] = strjoin_del(tmp->key, tmp->value, "=");
		tmp = tmp->next;
		i++;
	}
	return (result);
}

char	*strjoin_del(char *str1, char *str2, char *delimiter)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(str1, delimiter);
	result = ft_strjoin(tmp, str2);
	free(tmp);
	return (result);
}
