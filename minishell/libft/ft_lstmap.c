/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:43:28 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:43:29 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;
	t_list	*new;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	temp = lst;
	newlst = 0;
	while (temp)
	{
		data = f(temp->content);
		new = ft_lstnew(data);
		if (!new)
		{
			if (data)
				free (data);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, new);
		temp = temp->next;
	}
	return (newlst);
}
