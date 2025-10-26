/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:39:22 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/14 10:50:28 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*temp;
	size_t	min_size;

	temp = malloc(new_size);
	if (!temp)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			min_size = old_size;
		else
			min_size = new_size;
		ft_memcpy(temp, ptr, min_size);
		free(ptr);
	}
	return (temp);
}
