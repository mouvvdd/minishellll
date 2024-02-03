/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:33:34 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:33:36 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errorandprint(char *msg, int value)
{
	ft_putendl_fd(msg, 2);
	g_gb.status_code = value;
}

void	errorandprint2(char *msg, int value, char *str)
{
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(str, 2);
	g_gb.status_code = value;
}

int	checkerrors2(t_parsing *parsing, size_t i)
{
	if (parsing->tokens[i] == 'A' && ft_strlen(parsing->prompt[i]) > 2)
	{
		errorandprint("syntax error near unexpected token `>>'", 258);
		return (1);
	}
	if (parsing->tokens[i] == 'H' && ft_strlen(parsing->prompt[i]) > 3)
	{
		errorandprint("syntax error near unexpected token `<'", 258);
		return (1);
	}
	if (parsing->tokens[i] != 'S' && parsing->tokens[i] != '|'
		&& parsing->tokens[i + 1] != 'S')
	{
		errorandprint2("syntax error near unexpected token ", 258,
			parsing->prompt[i + 1]);
		return (1);
	}
	if (parsing->tokens[i] != 'S' && !parsing->tokens[i + 1]
		&& parsing->tokens[i] != '|')
	{
		errorandprint("syntax error near unexpected token `newline'", 258);
		return (1);
	}
	return (0);
}

int	checkerrors(t_parsing *parsing)
{
	size_t	i;

	i = 0;
	if (g_gb.status_code == -4)
	{
		errorandprint("error: close the quotes\n", 258);
		return (1);
	}
	while (parsing->tokens[i])
	{
		if (parsing->tokens[i] == '|')
		{
			if (i == 0 || ft_strlen(parsing->prompt[i]) > 1
				|| !parsing->tokens[i + 1])
			{
				errorandprint("syntax error near unexpected token `|'", 258);
				return (1);
			}
		}
		if (checkerrors2(parsing, i))
			return (1);
		i++;
	}
	return (0);
}
