/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:05:29 by mgunter           #+#    #+#             */
/*   Updated: 2024/12/01 20:13:32 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	length_s1;
	size_t	length_s2;

	if (!s1 || !s2)
		return (NULL);
	length_s1 = ft_strlen(s1);
	length_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (length_s1 + length_s2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (length_s1 + 1));
	ft_strlcat(str, s2, (length_s1 + length_s2 + 1));
	return (str);
}
