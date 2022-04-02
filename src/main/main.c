/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 22:45:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <mlx.h>

int	main(int argc, char **argv)
{
	t_global_info	*info;

	info = parsing(argc, argv);
	if (!info)
		exit(EXIT_FAILURE);
	display(info);
	free_info(info);
	printf("fin normal du programme atteinte");
	exit(EXIT_SUCCESS);
}
