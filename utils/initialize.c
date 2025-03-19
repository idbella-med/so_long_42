/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:46:51 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 22:02:32 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	allocate_memory(t_game **a, t_player **p)
{
	*a = malloc(sizeof(t_game));
	if (!(*a))
		error_exit("Memory allocation failed");
	ft_memset(*a, 0, sizeof(t_game));
	*p = malloc(sizeof(t_player));
	if (!(*p))
	{
		free(*a);
		error_exit("Memory allocation failed");
	}
	(*a)->player = *p;
}

static void	initialize_window(t_game *a)
{
	a->mlx = mlx_init();
	if (!a->mlx)
		error_exit("Failed to initialize MLX");
	a->windows = mlx_new_window(a->mlx, a->x * SIZE, a->y * SIZE, "so_long");
	if (!a->windows)
	{
		free(a->mlx);
		destroy_images(a);
		error_exit("Failed to create window");
	}
}

void	init_struct(t_game *a, char *map)
{
	if (a->map && a->map[0])
		a->x = ft_strlen(a->map[0]);
	a->y = count_line(map);
	a->collectibles_count = 0;
	a->moves_count = 0;
}

void	init_game(t_game **a, t_player **p, char *nmap)
{
	allocate_memory(a, p);
	map(*a, nmap);
	search_for_player(*p, *a);
	if (!check_valid_path(*a, *p))
	{
		destroy_images(*a);
		error_exit("No valid path!");
	}
	initialize_window(*a);
	load_images(*a);
	render_map(*a);
}

void	destroy_images(t_game *a)
{
	if (a->player_img.img)
		mlx_destroy_image(a->mlx, a->player_img.img);
	if (a->wall.img)
		mlx_destroy_image(a->mlx, a->wall.img);
	if (a->collectible.img)
		mlx_destroy_image(a->mlx, a->collectible.img);
	if (a->exit.img)
		mlx_destroy_image(a->mlx, a->exit.img);
	if (a->floor.img)
		mlx_destroy_image(a->mlx, a->floor.img);
	if (a->windows)
		mlx_destroy_window(a->mlx, a->windows);
	if (a->map)
		ft_free(a->map);
	if (a->player)
		free(a->player);
	free(a);
}
