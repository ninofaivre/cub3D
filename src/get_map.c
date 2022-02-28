/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:45:56 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/28 14:57:59 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <unistd.h>

static bool	is_line_empty(char *line)
{
	if (!line)
		return (false);
	while (is_charset(*line, " \n") && *line)
		line++;
	return (!*line);
}

#include <stdio.h>

t_map	*get_map(int fd_conf)
{
	t_map	*map;
	char	*line;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		print_error("Alloc\n");
		return (NULL);
	}
	map->content = NULL;
	line = get_next_line(fd_conf);
	while (line)
	{
		if (is_line_empty(line))
			free(line);
		else
			break ;
		line = get_next_line(fd_conf);
	}
	while (line)
	{
		line[str_len(line) - 1] = '\0';
		map->content = add_str_to_str_tab(map->content, line);
		if (!map->content)
		{
			free(map);
			print_error("Alloc\n");
			return (NULL);
		}
		line = get_next_line(fd_conf);
		if (is_line_empty(line))
		{
			print_error("Empty line encountered during map reading\n");
			free_str_tab(&(map->content));
			return (NULL);
		}
	}
	map->height = str_tab_len(map->content);
	return (map);
}

/*
char **get_test_map(int fd)
{
	char *str;
	char **map = NULL;

	str = get_next_line(fd);
	if (str)
		str[str_len(str) - 1] = '\0';
	while (str)
	{
		map = add_str_to_str_tab(map, str);
		str = get_next_line(fd);
		if (str)
			str[str_len(str) - 1] = '\0';
	}
	return (map);
}*/