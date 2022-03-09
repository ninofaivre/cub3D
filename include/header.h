/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:24:37 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/09 16:37:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	struct s_position	position;
	double				orientation;
}	t_player;

typedef struct s_map
{
	char	**content;
	int		height;
}	t_map;

enum { north, south, west, east, sprite };

typedef struct s_conf
{
	char			**texture_path;
	struct s_rgb	*ceilling_rgb;
	struct s_rgb	*floor_rgb;
}	t_conf;

typedef struct s_global_info
{
	struct s_conf	*conf;
	struct s_map	*map;
	struct s_player	player;
}	t_global_info;

char			*get_next_line(int fd);

t_global_info	*parsing(int argc, char **argv);

char			*str_dupe(char *str);
void			str_ncpy(char *dest, char *src, int n_char);

void			free_info(t_global_info *info);
void			print_error(char *error);

int				str_len(char *str);
bool			is_same_string(char *str1, char *str2);
bool			is_charset(char c, char *charset);
int				skip_space(char *str, int i);

bool			pars_rgb(char *str, int i, t_rgb **rgb);
bool			error_rgb(int error, int r, int g, int b);
int				next_nb(char *str, int i);
int				fake_atoi(char *str, int i);

char			*split_path_texture(char *str, int i);
bool			put_texture_in_struct(char *str, int i, char **ptr_path_texture);
bool			pars_texture_info(char *str, int i, t_conf *conf);

char			**str_tab_dupe(char **str_tab);
char			**add_str_to_str_tab(char **str_tab, char *str);
int				str_tab_len(char **str_tab);
char			**free_str_tab(char ***str_tab);
void			print_str_tab(char **str_tab);

t_map			*get_map(int fd_conf);
bool			parse_map(struct s_map *map, struct s_player *player);
bool			parsing_file(int fd_conf, t_conf *conf);

void			replace_connected_1_by_3(char **map, int y, int x);
bool			is_in_map(t_map *map, int x, int y);
bool			is_zero_surrounded(t_map *map, int x, int y);

void			replace_all_charset_by_char_in_str_tab(char *charset,
					char replace, char **str_tab);
int				get_n_char_in_str_tab(char c, char **str_tab);
bool			does_str_tab_contains_empty_str(char **str_tab);

void			print_str_tab(char **str_tab);

double			get_wall_distance(t_position player_position, double angle, char **map);
void			display(t_player *player, char **map);

#endif