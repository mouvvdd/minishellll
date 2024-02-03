/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerrakc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:15:17 by smerrakc          #+#    #+#             */
/*   Updated: 2024/02/03 15:15:22 by smerrakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_lstadd_back2(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!lst || !new)
		return ;
	if (*lst)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

void	addenvanyway(t_env *new, char **split)
{
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(split[0]);
	if (split[1] == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(split[1]);
	new->next = NULL;
	ft_lstadd_back2(&g_gb.env, new);
}

void	replacexisted(t_env *new, char **split)
{
	free(new->value);
	if (split[1] == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(split[1]);
}
