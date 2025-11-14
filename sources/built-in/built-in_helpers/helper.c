/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:53 by vhasanov          #+#    #+#             */
/*   Updated: 2025/11/13 15:26:35 by vhasanov         ###   ########.fr       */
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
    size_t len;
    char *res;
	
	len = ft_strlen(s1) + ft_strlen(sep) + ft_strlen(s2) + 1;
	res = malloc(len);
    if (!res)
        return NULL;
    ft_strlcpy(res, s1, len);
    ft_strlcat(res, sep, len);
    ft_strlcat(res, s2, len);
    return res;
}



