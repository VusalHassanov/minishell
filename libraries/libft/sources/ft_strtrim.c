/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:32:24 by mgunter           #+#    #+#             */
/*   Updated: 2024/12/01 20:25:00 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char const s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	length;
	size_t	i;
	char	*str;

	if (!s1)
		return (NULL);
	start = 0;
	while (check_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], set))
		end--;
	length = end - start;
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < length)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
