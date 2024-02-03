/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:44:58 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:44:59 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendst;

	i = 0;
	lensrc = ft_strlen(src);
	if (!dst && !dstsize)
		return (lensrc);
	lendst = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= lendst)
		return (lensrc + dstsize);
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - lendst - 1)
		{
			dst[lendst + i] = src[i];
			i++;
		}
		dst[lendst + i] = '\0';
	}
	return (lensrc + lendst);
}
