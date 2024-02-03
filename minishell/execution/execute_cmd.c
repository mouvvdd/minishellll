/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:17:17 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:17:24 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_cmd_lines *cmd_lines, int prev_fd)
{
	int		fd[2];
	char	**env;
	pid_t	pid;

	pipe(fd);
	if (!cmd_lines->args || !cmd_lines->args[0])
		return (close(fd[0]), fd[1]);
	pid = fork();
	if (pid == 0)
	{
		handlepipe(cmd_lines, prev_fd, fd);
		env = reverse_env(g_gb.env);
		ifexec(cmd_lines, env);
	}
	else if (pid < 0)
	{
		printf("minishell: %s: command not found\n", cmd_lines->args[0]);
		g_gb.status_code = 127;
	}
	close(fd[1]);
	if (prev_fd > 0)
		close(prev_fd);
	return (fd[0]);
}

void	ft_execve(t_cmd_lines *cmd_lines)
{
	t_cmd_lines	*cmd;
	int			prev_fd;

	cmd = cmd_lines;
	prev_fd = 0;
	while (cmd)
	{
		prev_fd = ft_exec_cmd(cmd, prev_fd);
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sigquit_handler);
	while (wait(&g_gb.status_code) != -1)
		;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	if (WIFEXITED(g_gb.status_code))
		g_gb.status_code = WEXITSTATUS(g_gb.status_code);
	else if (WIFSIGNALED(g_gb.status_code))
		g_gb.status_code = 128 + WTERMSIG(g_gb.status_code);
}

int	is_builtin(t_cmd_lines *cmd_lines)
{
	if (ft_strcmp(cmd_lines->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_lines->args[0], "unset") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_cmd_lines *cmd_lines, int outfile)
{
	if (ft_strcmp(cmd_lines->args[0], "echo") == 0)
		ft_echo(cmd_lines->args, outfile);
	else if (ft_strcmp(cmd_lines->args[0], "cd") == 0)
		ft_cd(cmd_lines->args);
	else if (ft_strcmp(cmd_lines->args[0], "pwd") == 0)
		ft_pwd(outfile);
	else if (ft_strcmp(cmd_lines->args[0], "env") == 0)
		ft_env(0, outfile);
	else if (ft_strcmp(cmd_lines->args[0], "exit") == 0)
		ft_exit(cmd_lines->args);
	else if (ft_strcmp(cmd_lines->args[0], "export") == 0)
		ft_export(cmd_lines->args, outfile);
	else if (ft_strcmp(cmd_lines->args[0], "unset") == 0)
		ft_unset(cmd_lines->args);
}

void	execute_cmd(t_cmd_lines *cmd_lines)
{
	if (!cmd_lines->next && (!cmd_lines->args || !cmd_lines->args[0]))
		return ;
	if (!cmd_lines->next && is_builtin(cmd_lines))
	{
		exec_builtin(cmd_lines, cmd_lines->outfile);
		return ;
	}
	else
		ft_execve(cmd_lines);
}
