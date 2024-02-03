/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:39:28 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 16:39:32 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_norm(char *delimiter, int first_pipe, char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !ft_strchr(delimiter, '\"')
			&& !ft_strchr(delimiter, '\'') && !ft_strchr(delimiter, '$'))
			expand_var(&line, i, first_pipe);
		if (line[i])
			i++;
	}
	return (line);
}
