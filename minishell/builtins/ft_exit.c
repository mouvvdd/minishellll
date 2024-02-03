/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:15:57 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:16:03 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_error(char *args)
{
	int	i;

	i = ft_atoi(args);
	ft_putstr_fd("exit\n", 1);
	exit(i);
}

void	numerror(char **args)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	exit(255);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	manyarguments(char **args)
{
	if (ft_isnumber(args[2]) != 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (g_gb.status_code = 1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
}

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		manyarguments(args);
	else if (i == 2)
	{
		if (ft_isnumber(args[1]) != 0)
			numerror(args);
		else
			exit_error(args[1]);
	}
	else
		exit_error(ft_itoa(g_gb.status_code));
	return (0);
}
