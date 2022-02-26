/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:51:16 by nino              #+#    #+#             */
/*   Updated: 2021/09/01 12:07:53 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	ft_rest(char *buffer, char *rest, char **line)
{
	if (ft_search (rest, '\n') != -1)
	{
		if (ft_strlen (&rest[ft_search (rest, '\n') + 1]))
			ft_strcpymod (buffer, &rest[ft_search (rest, '\n') + 1]);
		rest[ft_search (rest, '\n') + 1] = '\0';
		*line = ft_strjoinmod (*line, rest);
		if (!*line)
			return (-1);
		if (ft_strlen (buffer))
			ft_strcpymod (rest, buffer);
		else
			rest[0] = '\0';
		return (-2);
	}
	*line = ft_strjoinmod (*line, rest);
	if (!*line)
		return (-1);
	rest[0] = '\0';
	return (1);
}

static char	*ft_return(char *buffer, char **rest, char *line, int status)
{
	if (status == 0 && *rest)
	{
		free (*rest);
		*rest = NULL;
	}
	if (status > 0)
	{
		if (ft_strlen (&buffer[ft_search (buffer, '\n') + 1]))
			ft_strcpymod (*rest, &buffer[ft_search (buffer, '\n') + 1]);
		buffer[ft_search (buffer, '\n') + 1] = '\0';
		line = ft_strjoinmod (line, buffer);
	}
	if (status == -1 || !line)
	{
		if (buffer)
			free (buffer);
		if (rest)
			free (*rest);
		if (line)
			free (line);
		return ((char *) NULL);
	}
	free (buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	int			status;
	static char	*rest;

	buffer = (char *)ft_calloc((int) sizeof(char) * (BUFFER_SIZE + 1));
	line = NULL;
	status = 1;
	if (!rest)
		rest = (char *)ft_calloc((int) sizeof(char) * (BUFFER_SIZE + 1));
	if (rest && *rest)
		status = ft_rest (buffer, rest, &line);
	if (!buffer || !rest || fd < 0 || BUFFER_SIZE <= 0)
		return (ft_return (buffer, &rest, line, -1));
	while (status > 0)
	{
		status = read (fd, buffer, BUFFER_SIZE);
		buffer[status + (status == -1)] = '\0';
		if (status <= 0 || ft_search(buffer, '\n') != -1)
			break ;
		line = ft_strjoinmod (line, buffer);
		if (!line)
			return (ft_return (buffer, &rest, line, -1));
	}
	return (ft_return (buffer, &rest, line, status));
}
