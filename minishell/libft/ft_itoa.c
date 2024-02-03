/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellatr <mbellatr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 09:42:52 by mbellatr          #+#    #+#             */
/*   Updated: 2024/02/03 09:42:54 by mbellatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static	char	*ft_fillstr(char *str, int len, int nb, int n)
{
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (nb > 0)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

	len = 0;
	nb = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		len++;
		nb *= -1;
	}
	len += ft_len(n);
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	return (ft_fillstr(str, len, nb, n));
}
