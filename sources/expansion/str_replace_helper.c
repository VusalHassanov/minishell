/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:53:55 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/08 12:05:10 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_var(char *str, int pos, char *value)
{
    char *result;
    int var_len;
    int new_len;
    
    var_len = get_var_len(str, pos);
    new_len = ft_strlen(str) - var_len + ft_strlen(value);
    result = malloc(new_len + 1);
    if (!result)
        return (NULL);
    copy_with_var(result, str, value, pos);
    return (result);
}

int get_var_len(char *str, int pos)
{
    int len;
    
    len = 1;  // Count the '$'
    pos++;    // Move past '$'
    
    // If first character after $ is a digit, only count that digit
    if (ft_isdigit(str[pos]))
    {
        len++;  // Just the $ and the digit
        return (len);
    }
    
    // Otherwise, count all valid variable name characters
    while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
    {
        len++;
        pos++;
    }
    
    return (len);
}

void copy_with_var(char *dst, char *src, char *value, int pos)
{
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    while (i < pos)
        dst[j++] = src[i++];
    k = 0;
    while (value[k])
        dst[j++] = value[k++];
    i += get_var_len(src, pos);
    while (src[i])
        dst[j++] = src[i++];
    dst[j] = '\0';
}

char *remove_var(char *str, int pos)
{
    char *result;
    int var_len;
    int new_len;
    
    var_len = get_var_len(str, pos);
    new_len = ft_strlen(str) - var_len;
    result = malloc(new_len + 1);
    if (!result)
        return (NULL);
    copy_without_var(result, str, pos, var_len);
    return (result);
}

void copy_without_var(char *dst, char *src, int pos, int var_len)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < pos)
        dst[j++] = src[i++];
    i += var_len;
    while (src[i])
        dst[j++] = src[i++];
    dst[j] = '\0';
}