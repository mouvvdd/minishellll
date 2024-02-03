/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:21 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:34:23 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_checks(char *line, size_t i)
{
	if (line[i] == '<' || line[i] == '|' || line[i] == '>')
	{
		ft_checkingdupp(line, &i);
		i++;
	}
	else
	{
		while (line[i] && line[i] != '<' && line[i] != '|' && line[i] != '>'
			&& line[i] != ' ' && line[i] != '\t')
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

t_parsing	*initialsplit(t_parsing *parsing, char *line, size_t *i,
		size_t *start)
{
	*i = 0;
	*start = 0;
	parsing->size = sizeofprompt(line);
	parsing->prompt = malloc((parsing->size + 1) * sizeof(char **));
	parsing->tokens = malloc(parsing->size + 1);
	return (parsing);
}

void	ft_spliting(char *line, t_parsing *parsing)
{
	size_t	i;
	size_t	start;
	int		x;
	size_t	len;

	parsing = initialsplit(parsing, line, &i, &start);
	x = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			start++;
			continue ;
		}
		i = ft_checks(line, i);
		len = i - start;
		parsing->prompt[x] = ft_substr(line, start, len);
		x++;
		if (!line[i])
			break ;
		start = i;
	}
	parsing->prompt[x] = NULL;
}
