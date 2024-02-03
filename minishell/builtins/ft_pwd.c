/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:16:16 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:16:23 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(int outfile)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s\n", current_env("OLDPWD"));
		return (0);
	}
	ft_putstr_fd(pwd, outfile);
	ft_putstr_fd("\n", outfile);
	free(pwd);
	return (0);
}
