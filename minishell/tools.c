/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:37 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:37:56 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialcmd(t_cmd_lines *cmd_lines)
{
	cmd_lines->args = NULL;
	cmd_lines->infile = 0;
	cmd_lines->next = NULL;
	cmd_lines->outfile = 1;
	cmd_lines->path = NULL;
}

void	initialpars(t_parsing *parsing)
{
	parsing->prompt = NULL;
	parsing->tokens = NULL;
	parsing->size = 0;
}

void	freedouble(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->prompt[i++])
		free(parsing->prompt[i]);
	free(parsing->prompt);
}

int	ft_strcmp(char *line, char *str)
{
	unsigned int	i;

	i = 0;
	while ((line[i] && str[i]) && line[i] == str[i])
		i++;
	return (line[i] - str[i]);
}

void	here_doc_controller(int signal)
{
	(void)signal;
	close(0);
	g_gb.hsig = 1;
}
