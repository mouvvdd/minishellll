/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:42:19 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:42:21 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (0);
	ft_bzero (str, (count * size));
	return (str);
}
