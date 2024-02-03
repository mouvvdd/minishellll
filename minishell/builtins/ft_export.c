/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:14:18 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:14:24 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	inisplit(char *var, char *value, char **split)
{
	split[0] = var;
	split[1] = value;
	split[2] = NULL;
}

char	**addtoenv2(char *tmp)
{
	int		i;
	char	**split;
	char	*var;
	char	*value;

	i = 0;
	while (tmp && tmp[i] && tmp[i] != '=')
		i++;
	if (tmp && tmp[i] == '=')
	{
		var = ft_substr(tmp, 0, i);
		value = ft_substr(tmp + i + 1, 0, ft_strlen(tmp) - ft_strlen(var));
		split = malloc(sizeof(char *) * 3);
		inisplit(var, value, split);
		return (split);
	}
	else
	{
		split = ft_split(tmp, '=');
		return (split);
	}
}

void	addtoenv(char *tmp)
{
	t_env	*new;
	char	**split;

	split = addtoenv2(tmp);
	new = g_gb.env;
	while (new)
	{
		if (ft_strcmp(new->key, split[0]) == 0)
		{
			(replacexisted(new, split), dfree(split));
			return ;
		}
		new = new->next;
	}
	new = NULL;
	(addenvanyway(new, split), dfree(split));
}

int	export_name(char **args, int i)
{
	int	j;

	if (ft_isdigit(args[i][0]) == 1)
	{
		printf("export : '%s' : not a valid identifier\n", args[i]);
		return (g_gb.status_code = 1);
	}
	i = 0;
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '=')
				break ;
			if ((!ft_isalnum(args[i][j]) && args[i][j] != '_'
					&& args[i][j] != '='))
			{
				printf("export : '%s' : not a valid identifier\n", args[i]);
				return (g_gb.status_code = 1);
			}
			j++;
		}
	}
	return (g_gb.status_code = 0);
}

int	ft_export(char **args, int outfile)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!args[1])
	{
		ft_env(1, outfile);
		return (g_gb.status_code = 0);
	}
	if (export_name(args, i) == 1)
		return (g_gb.status_code = 1);
	while (args[i])
	{
		tmp = ft_strdup(args[i]);
		addtoenv(tmp);
		free(tmp);
		i++;
	}
	return (g_gb.status_code = 0);
}
