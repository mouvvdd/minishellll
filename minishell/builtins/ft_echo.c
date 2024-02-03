/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:15:34 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:15:40 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	isdashnstring(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **args, int outfile)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		write(outfile, "\n", 1);
		return (1);
	}
	while (args[i])
	{
		if (isdashnstring(args[i]) == 1)
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], outfile);
		if (args[i + 1])
			ft_putstr_fd(" ", outfile);
		i++;
	}
	if (isdashnstring(args[1]) != 0)
		write(outfile, "\n", 1);
	return (0);
}
