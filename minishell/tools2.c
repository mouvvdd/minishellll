/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:42 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:37:49 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checkingdupp(char *line, size_t *i)
{
	char	c;

	c = line[*i];
	while (line[*i] == c)
		(*i)++;
	(*i)--;
}

int	dquoting(char *line, char c, int i)
{
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == '\0')
	{
		g_gb.status_code = -4;
	}
	return (i);
}

void	dfree(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_nodes(t_cmd_lines *cmd_lines)
{
	t_cmd_lines	*tmp;

	while (cmd_lines)
	{
		tmp = cmd_lines;
		cmd_lines = cmd_lines->next;
		dfree(tmp->args);
		free(tmp->path);
		if (tmp->infile > 2)
			close(tmp->infile);
		if (tmp->outfile > 2)
			close(tmp->outfile);
		free(tmp);
	}
}

void	freeparsing(t_parsing *parsing)
{
	free(parsing->infiles);
	free(parsing->outfiles);
	dfree(parsing->prompt);
	free(parsing->tokens);
}
