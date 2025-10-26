/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:24:46 by mgunter           #+#    #+#             */
/*   Updated: 2024/11/30 12:30:00 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length_dst;
	size_t	length_src;

	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (length_dst >= size)
		return (size + length_src);
	else
	{
		dst = dst + length_dst;
		ft_strlcpy(dst, src, size - length_dst);
		return (length_src + length_dst);
	}
}
