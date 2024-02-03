/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:45:48 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:45:50 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	substr = ft_calloc((len + 1), sizeof(char));
	if (!substr)
		return (0);
	i = 0;
	if (start > ft_strlen(s))
	{
		substr[i] = '\0';
		return (substr);
	}
	while (i < len)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	return (substr);
}
