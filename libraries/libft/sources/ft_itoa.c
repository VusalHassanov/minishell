/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:07:18 by mgunter           #+#    #+#             */
/*   Updated: 2024/11/27 18:46:13 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_length(int n)
{
	int	i;
	int	sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	else if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i + sign);
}

static void	ft_convert(int n, char *str, int len)
{
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[len] = '\0';
	while (n != 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;

	length = ft_number_length(n);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		str[0] = '-';
		ft_convert(2147483647, str + 1, length - 1);
		str[length - 1] = '8';
	}
	else
		ft_convert(n, str, length);
	return (str);
}
