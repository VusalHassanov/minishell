/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:07:16 by mgunter           #+#    #+#             */
/*   Updated: 2024/12/01 18:56:28 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destination;
	unsigned const char	*source;

	i = 0;
	destination = (unsigned char *)dest;
	source = (unsigned const char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (destination > source)
	{
		while (n-- > 0)
			*(destination + n) = *(source + n);
	}
	else
	{
		while (i < n)
		{
			*(destination + i) = *(source + i);
			i++;
		}
	}
	return (dest);
}
