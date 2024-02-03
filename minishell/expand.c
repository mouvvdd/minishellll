/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:33:40 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:33:42 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_expand_var(char *line, size_t start, size_t *end, int first_pipe)
{
	t_env	*env;
	char	*key;

	env = g_gb.env;
	if (start == *end && line[start] == '?')
	{
		(*end)++;
		if (first_pipe)
			return (ft_strdup("0"));
		return (ft_itoa(g_gb.status_code));
	}
	while (env)
	{
		key = ft_substr(&line[start], 0, *end - start);
		if (!ft_strcmp(key, env->key))
		{
			free(key);
			return (ft_strdup(env->value));
		}
		free(key);
		env = env->next;
	}
	return (NULL);
}

char	*expand_var_utils(char **line, size_t start, int first_pipe,
		size_t *end)
{
	char	*value;

	while (ft_isdigit((*line)[*end]))
		(*end)++;
	while (!ft_isdigit((*line)[start + 1]) && (ft_isalnum((*line)[*end])
			|| (*line)[*end] == '_'))
		(*end)++;
	value = find_expand_var((*line), start + 1, end, first_pipe);
	if (!value)
		value = ft_strdup("");
	return (value);
}

void	expand_var(char **line, size_t start, int first_pipe)
{
	size_t	end;
	size_t	i;
	char	*value;
	char	*new_line;

	end = start + 1;
	value = expand_var_utils(line, start, first_pipe, &end);
	new_line = malloc(sizeof(char) * (start + ft_strlen(value)
				+ ft_strlen((*line)) - end + 1));
	i = 0;
	while (i < start)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	start = 0;
	while (start < ft_strlen(value))
		new_line[i++] = value[start++];
	while (end < ft_strlen((*line)))
		new_line[i++] = (*line)[end++];
	new_line[i] = 0;
	(free(*line), free(value));
	*line = new_line;
}

void	expand_line(char **line, int first_pipe, char prev_token)
{
	size_t	start;
	t_utils	*utils;

	start = 0;
	utils = malloc(sizeof(t_utils));
	utils->first_pipe = first_pipe;
	utils->prev_token = prev_token;
	while ((*line)[start])
	{
		if ((*line)[start] == '\'' || (*line)[start] == '\"')
			start = remove_quote(line, start, dquoting((*line), (*line)[start],
						start + 1), utils);
		else if ((*line)[start] == '$' && prev_token != 'H')
			expand_var(line, start, first_pipe);
		else
			start++;
	}
	free(utils);
}

void	expand(t_parsing *parsing)
{
	size_t	i;
	int		first_pipe;
	char	prev_token;

	i = 0;
	first_pipe = 0;
	prev_token = 0;
	while (parsing->tokens[i])
	{
		if (i)
			prev_token = parsing->tokens[i - 1];
		if (parsing->tokens[i] == '|')
			first_pipe = 1;
		else if (parsing->tokens[i] == 'S')
			expand_line(&parsing->prompt[i], first_pipe, prev_token);
		i++;
	}
}
