/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/27 16:27:40 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
char **get_test_map(int fd);

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	int			fd_conf;

	if (argc != 2)
	{
		print_error("n_arg\n");
		exit(EXIT_FAILURE);
	}
	if (is_valid_file_name(argv[1]) == false)
	{
		print_error("extansion\n");
		exit(EXIT_FAILURE);
	}
	fd_conf = open(argv[1], O_RDONLY);
	if (fd_conf == -1)
	{
		print_error("file\n");
		exit(EXIT_FAILURE);
	}
	map.content = get_test_map(fd_conf);
	close(fd_conf);
	if (parse_map(&map, &player))
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
