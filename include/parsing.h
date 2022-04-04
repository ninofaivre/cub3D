/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:44:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:14:44 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "main.h"
# include <stdbool.h>

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_player
{
	t_position	position;
	double		orientation;
}	t_player;

typedef struct s_map
{
	char	**content;
	int		height;
}	t_map;

enum { north, south, west, east };

typedef struct s_conf
{
	char	**texture_path;
	char	*ceilling_rgb;
	char	*floor_rgb;
}	t_conf;

typedef struct s_global_info
{
	t_conf					*conf;
	t_map					*map;
	t_player				player;
	void					*mlx;
	void					*win;
	struct s_column_info	*column_info;
	t_key					*key;
	struct s_texture		*texture;
	struct s_img			*frame;
	struct s_put_texture	*put_texture;
	bool					first_frame;
}	t_global_info;

char			*get_next_line(int fd);

t_map			*get_map(int fd_conf);

bool			parsing_file(int fd_conf, t_conf *conf);

bool			parse_map(t_map *map, t_player *player);

void			replace_connected_1_by_3(char **map, int y, int x);
bool			is_in_map(t_map *map, int x, int y);
bool			is_zero_surrounded(t_map *map, int x, int y);

bool			pars_rgb(char *str, int i, char **rgb);

bool			pars_texture_info(char *str, int i, t_conf *conf);

t_global_info	*parsing(int argc, char **argv);

void			free_info(t_global_info *info);
void			print_error(char *error);

#endif
