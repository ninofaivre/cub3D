/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:45:56 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:01:42 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

static char	*skip_empty_line(int fd_conf)
{
	char	*line;

	line = get_next_line(fd_conf);
	while (line)
	{
		if (!str_len(line) || *line == '\n')
			free(line);
		else
			break ;
		line = get_next_line(fd_conf);
	}
	return (line);
}

t_map	*get_map(int fd_conf)
{
	t_map	*map;
	char	*line;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->content = NULL;
	line = skip_empty_line(fd_conf);
	while (line)
	{
		if (line[str_len(line) - 1] == '\n')
			line[str_len(line) - 1] = '\0';
		map->content = add_str_to_str_tab(map->content, line);
		if (!map->content)
			return (NULL);
		line = get_next_line(fd_conf);
	}
	map->height = str_tab_len(map->content);
	return (map);
}
