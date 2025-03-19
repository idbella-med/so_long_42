/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:00:15 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/17 17:56:40 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *a)
{
	int	new_x;
	int	new_y;

	if (keycode == 53)
	{
		destroy_images(a);
		exit(0);
	}
	new_x = a->player->x;
	new_y = a->player->y;
	if (keycode == 13 || keycode == 126)
		new_y--;
	else if (keycode == 1 || keycode == 125)
		new_y++;
	else if (keycode == 0 || keycode == 123)
		new_x--;
	else if (keycode == 2 || keycode == 124)
		new_x++;
	else
		return (0);
	move_player(a, new_x, new_y);
	return (0);
}

int	close_windows(t_game *a)
{
	if (a)
		destroy_images(a);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		*a;
	t_player	*p;

	if (ac != 2 || SIZE != 50)
		error_exit("Usage: ./so_long map.ber");
	init_game(&a, &p, av[1]);
	mlx_hook(a->windows, 17, 1, close_windows, a);
	mlx_hook(a->windows, 2, 1, handle_keypress, a);
	mlx_loop(a->mlx);
	return (0);
}
