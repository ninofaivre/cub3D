/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:24:37 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 22:44:15 by nfaivre          ###   ########.fr       */
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
	struct s_conf			*conf;
	struct s_map			*map;
	struct s_player			player;
	void					*mlx;
	void					*win;
	struct s_column_info	*column_info;
	struct s_key			*key;
	struct s_texture		*texture;
}	t_global_info;

typedef struct s_data
{
	int		bpp;
	int		line_lenght;
	int		endian;
	char	*data;
}	t_data;

typedef struct s_img
{
	void	*img;
	struct s_data	data;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	struct s_img north;
}	t_texture;

typedef struct s_wall
{
	char				orientation;
	double				distance;
	struct s_position	colision;
}	t_wall;

typedef struct s_key
{
	bool	z;
	bool	q;
	bool	s;
	bool	d;
	bool	l_arrow;
	bool	r_arrow;
}	t_key;


# include "calculation.h"

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

t_wall			get_wall_distance(t_position player_position, double angle, char **map);
void			display(t_global_info *info);
double			degrees_to_radians(double degrees);

#endif
