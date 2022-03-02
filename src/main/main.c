/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/02 15:43:20 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_global_info	*info;

	info = parsing(argc, argv);
	if (!info)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
