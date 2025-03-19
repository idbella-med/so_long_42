/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:47:08 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 21:52:08 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	handle_collectible(t_game *a, int new_x, int new_y)
{
	if (a->map[new_y][new_x] == 'C')
	{
		a->collectibles_count--;
		a->map[new_y][new_x] = '0';
		if (a->collectibles_count == 0)
			load_exit(a, a->collectibles_count);
	}
}

static void	handle_exit(t_game *a, int new_x, int new_y)
{
	if (a->collectibles_count == 0)
	{
		destroy_images(a);
		ft_putstr_fd("You win!\n", 1);
		exit(0);
	}
	load_exit(a, a->collectibles_count);
	a->map[a->player->y][a->player->x] = '0';
	a->player->x = new_x;
	a->player->y = new_y;
}

void	search_for_player(t_player *a, t_game *s)
{
	int	i;
	int	j;

	i = 0;
	while (s->map[i])
	{
		j = 0;
		while (s->map[i][j])
		{
			if (s->map[i][j] == 'P')
			{
				a->x = j;
				a->y = i;
			}
			else if (s->map[i][j] == 'C')
				s->collectibles_count++;
			j++;
		}
		i++;
	}
}

void	move_player(t_game *a, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= a->x || new_y < 0 || new_y >= a->y
		|| a->map[new_y][new_x] == '1')
		return ;
	handle_collectible(a, new_x, new_y);
	if (a->map[new_y][new_x] == 'E')
		handle_exit(a, new_x, new_y);
	else
	{
		if (a->map[a->player->y][a->player->x] == 'E')
		{
			load_images(a);
			a->map[a->player->y][a->player->x] = 'E';
		}
		else
			a->map[a->player->y][a->player->x] = '0';
		a->player->x = new_x;
		a->player->y = new_y;
		a->map[new_y][new_x] = 'P';
	}
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(++a->moves_count, 1);
	ft_putchar_fd('\n', 1);
	render_map(a);
}
