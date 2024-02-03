/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:34:31 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:34:33 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokening(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->prompt[i])
	{
		if (parsing->prompt[i][0] == '|')
			parsing->tokens[i] = '|';
		else if (parsing->prompt[i][0] == '<' && !parsing->prompt[i][1])
			parsing->tokens[i] = '<';
		else if (parsing->prompt[i][0] == '<' && parsing->prompt[i][1])
			parsing->tokens[i] = 'H';
		else if (parsing->prompt[i][0] == '>' && !parsing->prompt[i][1])
			parsing->tokens[i] = '>';
		else if (parsing->prompt[i][0] == '>' && parsing->prompt[i][1])
			parsing->tokens[i] = 'A';
		else
			parsing->tokens[i] = 'S';
		i++;
	}
	parsing->tokens[i] = '\0';
}
