/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:43:33 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:43:34 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;
	t_list	*temp;

	temp = content;
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = temp;
	node->next = NULL;
	return (node);
}
