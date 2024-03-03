/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamahdi <hamahdi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:33:50 by hamahdi           #+#    #+#             */
/*   Updated: 2024/03/03 18:15:43 by hamahdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *s)
{
	size_t	i;
	char	*the_line;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	the_line = malloc(i + 1);
	if (!the_line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		the_line[i] = s[i];
		i++;
	}
	the_line[i] = s[i];
	if (s[i] != '\0')
		the_line[++i] = '\0';
	return (the_line);
}

char	*ft_the_rest(char *rem)
{
	size_t	i;
	size_t	n;
	char	*rem2;

	i = 0;
	n = 0;
	if (!rem)
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] && rem[i] == '\n')
		i++;
	if (rem[i] == '\0')
		return (free(rem), NULL);
	rem2 = malloc(ft_strlen(rem) - i + 1);
	if (!rem2)
	{
		free(rem);
		return (NULL);
	}
	while (rem[i])
		rem2[n++] = rem[i++];
	rem2[n] = '\0';
	free(rem);
	return (rem2);
}

char	*ft_read_line(int fd, char *rem)
{
	char	*buffer;
	int		n;

	n = 1;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (n > 0 && !ft_strchr(rem, '\n'))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (free(buffer), free(rem), rem = NULL, NULL);
		buffer[n] = '\0';
		rem = ft_strjoin(rem, buffer);
	}
	if ((n == 0 && (rem && !(rem[0]))))
		return (free(buffer), free(rem), rem = NULL, NULL);
	free(buffer);
	buffer = NULL;
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	rem = ft_read_line(fd, rem);
	if (!rem)
		return (NULL);
	line = ft_line(rem);
	if (!line || (!line[0]))
		return (free(line), line = NULL, NULL);
	rem = ft_the_rest(rem);
	return (line);
}
