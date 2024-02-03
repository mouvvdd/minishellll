/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:45:34 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:45:35 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = ft_strlen(needle) - 1;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0'
			&& i + j < len)
		{
			if (j == x)
				return ((char *)&haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
