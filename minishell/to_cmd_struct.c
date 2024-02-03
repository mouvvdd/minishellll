/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:26 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:37:14 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd(char *all_paths, char *cmd_name)
{
	char	**paths;
	char	*absolute;
	char	*cmd;
	size_t	i;

	paths = ft_split(all_paths, ':');
	if (!paths)
		return (NULL);
	i = 0;
	cmd = ft_strjoin("/", cmd_name);
	while (paths[i++])
	{
		absolute = ft_strjoin(paths[i], cmd);
		if (!access(absolute, X_OK))
		{
			(dfree(paths), free(cmd));
			return (absolute);
		}
		free(absolute);
	}
	(dfree(paths), free(cmd));
	return (NULL);
}

char	*check_path(char *cmd_name)
{
	t_env	*env;

	if (cmd_name == NULL)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	env = g_gb.env;
	while (env)
	{
		if (!ft_strcmp("PATH", env->key))
			return (find_cmd(env->value, cmd_name));
		env = env->next;
	}
	return (NULL);
}

size_t	lenofargs(char *tokens, size_t i)
{
	size_t	len;

	len = 0;
	while (tokens[i] && tokens[i] != '|')
	{
		if (tokens[i] != 'S')
			i += 2;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	**setup_args(t_parsing *parsing, size_t cmd_index)
{
	size_t	i;
	size_t	times;
	char	**args;

	i = 0;
	setup_args_utils(parsing, cmd_index, &i);
	times = lenofargs(parsing->tokens, i);
	if (!times)
		return (NULL);
	args = malloc(sizeof(char *) * (times + 1));
	times = 0;
	while (parsing->tokens[i] && parsing->tokens[i] != '|')
	{
		if (parsing->tokens[i] != 'S')
			i += 2;
		else
		{
			args[times++] = ft_strdup(parsing->prompt[i]);
			i++;
		}
	}
	args[times] = 0;
	return (args);
}

t_cmd_lines	*addtostruct(t_parsing *parsing)
{
	t_cmd_lines	*cmd_lines;
	t_cmd_lines	*cmd;
	size_t		i;

	cmd_lines = malloc(sizeof(t_cmd_lines));
	i = 0;
	cmd = cmd_lines;
	while (i < parsing->cmd_size)
	{
		initialcmd(cmd);
		cmd->infile = parsing->infiles[i];
		cmd->outfile = parsing->outfiles[i];
		cmd->args = setup_args(parsing, i);
		if (cmd->args)
			cmd->path = check_path(cmd->args[0]);
		if (i + 1 < parsing->cmd_size)
		{
			cmd->next = malloc(sizeof(t_cmd_lines));
			cmd = cmd->next;
		}
		i++;
	}
	return (cmd_lines);
}
