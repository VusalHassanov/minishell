/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:45:31 by vhasanov          #+#    #+#             */
/*   Updated: 2025/12/15 13:11:25 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a position in string is inside single quotes */
int is_in_single_quotes(char *str, int pos)
{
    int i;
    int in_single;
    int in_double;
    
    i = 0;
    in_single = 0;
    in_double = 0;
    
    while (i < pos)
    {
        if (str[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (str[i] == '\"' && !in_single)
            in_double = !in_double;
        i++;
    }
    return (in_single);
}

/* Check if a position in string is inside any quotes */

//We can use it for bonus

// int is_in_quotes(char *str, int pos)
// {
//     int i;
//     int in_single;
//     int in_double;
    
//     i = 0;
//     in_single = 0;
//     in_double = 0;
    
//     while (i < pos)
//     {
//         if (str[i] == '\'' && !in_double)
//             in_single = !in_single;
//         else if (str[i] == '\"' && !in_single)
//             in_double = !in_double;
//         i++;
//     }
//     return (in_single || in_double);
// }

/* Remove all quotes from a string */

//Note: Here we make bigger String than we need bcs we don't use get_len_without_quotes(char *str) function. But I don't think it is a problem.
//We will free it anyway.

char *remove_quotes(char *str)
{
    char *result;
    int i;
    int j;
    int in_single;
    int in_double;
    
    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    in_single = 0;
    in_double = 0;
    
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
        {
            in_single = !in_single;
            i++;
        }
        else if (str[i] == '\"' && !in_single)
        {
            in_double = !in_double;
            i++;
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    return (result);
}

/* Count length of string after quote removal (for pre-allocation) */

//Note: We can use it to have efficient memory, but it is choice. Memory gonna be freed anyway.

// int get_len_without_quotes(char *str)
// {
//     int i;
//     int len;
//     int in_single;
//     int in_double;
    
//     i = 0;
//     len = 0;
//     in_single = 0;
//     in_double = 0;
    
//     while (str[i])
//     {
//         if (str[i] == '\'' && !in_double)
//             in_single = !in_single;
//         else if (str[i] == '\"' && !in_single)
//             in_double = !in_double;
//         else
//             len++;
//         i++;
//     }
//     return (len);
// }