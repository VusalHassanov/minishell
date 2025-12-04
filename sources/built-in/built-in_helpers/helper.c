/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:53 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/30 19:18:31 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *ft_strjoin_three(const char *s1, const char *sep, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t len3;
    char *res;
	
    if (!s1 || !sep || !s2)
        return NULL;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(sep);
    len3 = ft_strlen(s2);
	res = malloc(len1 + len2 + len3 + 1);
    if (!res)
        return NULL;
    ft_strlcpy(res, s1, len1 + 1);
    ft_strlcat(res, sep, len1 + len2 + 1);
    ft_strlcat(res, s2, len1 + len2 + len3 + 1);
    return res;
}



