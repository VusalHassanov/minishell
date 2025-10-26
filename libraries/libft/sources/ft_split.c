/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:51:28 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/20 17:25:01 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;
	int	new_word;

	i = 0;
	words = 0;
	new_word = 1;
	while (s[i])
	{
		if (new_word == 1 && s[i] != c)
		{
			words++;
			new_word = 0;
		}
		else if (s[i] == c)
		{
			new_word = 1;
		}
		i++;
	}
	return (words);
}

static void	free_memory(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
}

static int	length_word(char const *s, char c)
{
	int	length;

	length = 0;
	if (!ft_strchr(s, c))
		length = ft_strlen(s);
	else
		length = ft_strchr(s, c) - s;
	return (length);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		length;
	char	**array;

	array = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!array)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			length = length_word(s, c);
			array[j++] = ft_substr(s, 0, length);
			if (array[j - 1] == NULL)
				return (free_memory(array, j - 1), NULL);
			s += length;
		}
	}
	array[j] = NULL;
	return (array);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*string;
// 	char	c;
// 	char	**array;
// 	int		i;

// 	string = "\"String <\"<<\"String >\">>!";
// 	c = '"';
// 	array = ft_split(string, c);
// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// }
