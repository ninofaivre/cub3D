/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 17:56:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	int	fd_conf;

	if (argc != 2)
		print_error("n_arg\n");
	if (is_valid_file_name == false);
		print_error("extansion");
	fd_conf = open(argv[1], O_RDONLY);
	if (!fd_conf)
	{
		print_error("file\n");
		exit(EXIT_FAILURE);
	}
}
