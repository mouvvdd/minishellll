/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:13:50 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:13:58 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_someputstr_fd(char *key, char *value, int outfile)
{
	ft_putstr_fd(key, outfile);
	ft_putstr_fd("=", outfile);
	ft_putstr_fd(value, outfile);
	ft_putstr_fd("\n", outfile);
}

int	ft_env(int flag, int outfile)
{
	t_env	*tmp;

	tmp = g_gb.env;
	while (tmp)
	{
		if (flag)
		{
			ft_putstr_fd("declare -x ", outfile);
			ft_putstr_fd(tmp->key, outfile);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", outfile);
				ft_putstr_fd(tmp->value, outfile);
				ft_putstr_fd("\"", outfile);
			}
			ft_putstr_fd("\n", outfile);
		}
		else if (tmp->value)
			ft_someputstr_fd(tmp->key, tmp->value, outfile);
		tmp = tmp->next;
	}
	return (0);
}
