/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:13:01 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:13:13 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_echo(char **args, int outfile);
int		isdashnstring(char *str);
int		ft_cd(char **av);
int		ft_pwd(int outfile);
int		ft_unset(char **args);
int		ft_env(int flag, int outfile);
int		ft_exit(char **args);
int		ft_export(char **args, int outfile);
int		export_name(char **args, int i);
void	addtoenv(char *tmp);
char	**addtoenv2(char *tmp);
void	inisplit(char *var, char *value, char **split);
char	*current_env(char *str);

#endif
