/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:01:10 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/21 10:51:36 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	length_big;
	size_t	length_little;

	length_little = ft_strlen(little);
	if (length_little == 0)
		return ((char *)(big));
	length_big = ft_strlen(big);
	if ((length_big < length_little))
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			if ((ft_strcmp((big + i), (little)) == 0) && i
				+ length_little <= len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
