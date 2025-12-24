/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:20:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/10 17:29:03 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(char *str, int pos, int exit_status)
{
	char	*result;
	char	*exit_str;
	int		new_len;

	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (NULL);
	new_len = ft_strlen(str) - 2 + ft_strlen(exit_str);
	result = malloc(new_len + 1);
	if (!result)
		return (free(exit_str), NULL);
	copy_exit_status(result, str, exit_str, pos);
	free(exit_str);
	return (result);
}

void	copy_exit_status(char *dst, char *src, char *exit_str, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < pos)
		dst[j++] = src[i++];
	k = 0;
	while (exit_str[k])
		dst[j++] = exit_str[k++];
	i += 2;
	while (src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
}
