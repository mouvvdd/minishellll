/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:43:08 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:43:09 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*tmpnxt;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		tmpnxt = temp->next;
		ft_lstdelone(temp, del);
		temp = tmpnxt;
	}
	*lst = NULL;
}
