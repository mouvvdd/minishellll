/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_of_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:15 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:36:37 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_checkiprompt(char *line, size_t i)
{
	if (line[i] == '<' || line[i] == '|' || line[i] == '>')
	{
		ft_checkingdupp(line, &i);
		i++;
	}
	else
	{
		while (line[i] && line[i] != '<' && line[i] != '|'
			&& line[i] != '>' && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '\"' || line[i] == '\'')
			{
				i++;
				i = dquoting(line, line[i - 1], i);
				i++;
			}
			else
				i++;
		}
	}
	return (i);
}

size_t	sizeofprompt(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue ;
		}
		i = ft_checkiprompt(line, i);
		count++;
	}
	return (count);
}
