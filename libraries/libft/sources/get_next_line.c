/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgunter <mgunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:56:37 by mgunter           #+#    #+#             */
/*   Updated: 2025/10/14 12:10:08 by mgunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

size_t		ft_strlen_gnl(const char *s);
void		*ft_calloc_gnl(size_t nmemb, size_t size);
char		*ft_strchr_gnl(const char *s, int c);
char		*ft_join_free_gnl(char *s1, char *s2);
char		*ft_strdup_gnl(const char *s);

static char	*ft_remain(char *buffer, char *remain_line)
{
	char	*temp;

	if (buffer[0] == '\0')
		return (NULL);
	temp = ft_strchr_gnl(buffer, '\n');
	if (temp && *(temp + 1))
		remain_line = ft_strdup_gnl(temp + 1);
	else
		return (NULL);
	return (remain_line);
}

static char	*ft_free(char *remain_line, char *buffer)
{
	char	*temp;

	temp = ft_join_free_gnl(remain_line, buffer);
	free(buffer);
	return (temp);
}

static char	*ft_next_line(char *string)
{
	int		length_line;
	char	*next_line;
	char	*temp;
	int		i;

	temp = ft_strchr_gnl(string, '\n');
	if (temp == NULL)
		length_line = ft_strlen_gnl(string);
	else
		length_line = temp - string + 1;
	next_line = ft_calloc_gnl(length_line + 1, sizeof(char));
	i = 0;
	while (i < length_line)
	{
		next_line[i] = string[i];
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

static char	*read_line(int fd)
{
	int		bytes_read;
	char	*buffer;
	char	*result;

	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	result = ft_calloc_gnl(1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(result), NULL);
		buffer[bytes_read] = '\0';
		result = ft_join_free_gnl(result, buffer);
		if (!result)
			return (free(buffer), NULL);
		if (ft_strchr_gnl(buffer, '\n') != NULL)
			break ;
		if (bytes_read == 0 && result[0] == '\0')
			return (free(buffer), free(result), NULL);
	}
	return (free(buffer), result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*next_line;
	static char	*remain_line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (remain_line)
		{
			free(remain_line);
			remain_line = NULL;
		}
		return (NULL);
	}
	buffer = read_line(fd);
	if (buffer == NULL && remain_line)
		buffer = ft_calloc_gnl(1, 1);
	else if (buffer == NULL && remain_line == NULL)
		return (free(buffer), NULL);
	if (remain_line)
		buffer = ft_free(remain_line, buffer);
	next_line = ft_next_line(buffer);
	remain_line = ft_remain(buffer, remain_line);
	return (free(buffer), next_line);
}

// int	main(void)
// {
// 	int		fd;
// 	int		line_counter;
// 	char	*next_line;

// 	line_counter = 1;
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 		{
// 			printf("\neof: NULL");
// 			break ;
// 		}
// 		printf("Line [%d]: %s", line_counter, next_line);
// 		free(next_line);
// 		next_line = NULL;
// 		line_counter++;
// 	}
// 	printf("\n");
// 	close(fd);
// 	return (0);
// }
