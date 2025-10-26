/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:20:39 by mgunter           #+#    #+#             */
/*   Updated: 2024/11/30 11:40:37 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		length;
	char	*ptr;

	length = ft_strlen(s);
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(ptr + i) = *(s + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
