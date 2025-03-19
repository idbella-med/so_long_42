/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:00:23 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/17 17:57:17 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 50

# include <mlx.h>
# include "./gnl/get_next_line.h"
# include "./Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_game
{
	int			x;
	int			y;
	char		*mlx;
	char		*windows;
	char		**map;
	t_player	*player;
	t_img		wall;
	t_img		floor;
	t_img		player_img;
	t_img		collectible;
	t_img		exit;
	int			collectibles_count;
	int			moves_count;
}	t_game;

int		check_valid_path(t_game *a, t_player *player);
void	search_for_player(t_player *a, t_game *s);
int		count_line(char *map);
void	render_map(t_game *a);
void	load_images(t_game *a);
void	error_exit(const char *msg);
void	map(t_game *a, char *file_name);
void	init_struct(t_game *a, char *map);
void	ft_free(char **arr);
void	parsing_map(t_game *a);
void	load_exit(t_game *a, int c);
void	init_game(t_game **a, t_player **p, char *nmap);
void	destroy_images(t_game *a);
void	move_player(t_game *a, int new_x, int new_y);
void	check_newline(char *str);
#endif
