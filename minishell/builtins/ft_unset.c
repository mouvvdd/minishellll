/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:14:42 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:14:49 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_from_env(char *tmp)
{
	t_env	*new;
	t_env	*tmp2;
	int		i;

	new = g_gb.env;
	tmp2 = g_gb.env;
	i = 0;
	while (ft_strcmp(tmp2->key, tmp) != 0)
	{
		tmp2 = tmp2->next;
		i++;
	}
	if (i == 0)
	{
		g_gb.env = g_gb.env->next;
		(free(tmp2->key), free(tmp2->value), free(tmp2));
		return ;
	}
	else
	{
		while (new->next != tmp2)
			new = new->next;
		new->next = tmp2->next;
		(free(tmp2->key), free(tmp2->value), free(tmp2));
	}
}

int	env_here(char *tmp)
{
	t_env	*new;

	new = g_gb.env;
	while (new)
	{
		if (ft_strcmp(new->key, tmp) == 0)
			return (1);
		new = new->next;
	}
	return (0);
}

int	unvalididentifier(char **args, int i)
{
	printf("unset : '%s' : not a valid identifier\n", args[i]);
	return (g_gb.status_code = 1);
}

int	unset_name(char **args, int i)
{
	int	j;

	if ((ft_isdigit(args[i][0]) == 1))
	{
		printf("unset : '%s' : not a valid identifier\n", args[i]);
		return (g_gb.status_code = 1);
	}
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((!ft_isalnum(args[i][j]) || args[i][j] == '-'
					|| args[i][j] == '+'))
				unvalididentifier(args, i);
			j++;
		}
		i++;
	}
	i = 1;
	if (env_here(args[i]) == 0)
		return (g_gb.status_code = 1);
	return (g_gb.status_code = 0);
}

int	ft_unset(char **args)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!args[1])
		return (0);
	if (unset_name(args, i) == 1)
		return (g_gb.status_code = 1);
	while (args[i])
	{
		tmp = ft_strdup(args[i]);
		remove_from_env(tmp);
		free(tmp);
		i++;
	}
	return (g_gb.status_code = 0);
}
