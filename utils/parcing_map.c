/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:36 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 21:36:54 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_walls(t_game *a)
{
	int	i;

	i = 0;
	while (i < a->y)
	{
		if (a->map[i][0] != '1' || a->map[i][ft_strlen(a->map[i]) - 1] != '1')
			error_exit("Invalid map: Side walls are not complete");
		i++;
	}
}

static void	count_elements(t_game *a, int *p, int *e, int *c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a->y)
	{
		j = -1;
		while (a->map[i][++j])
		{
			if (a->map[i][j] == 'P')
				(*p)++;
			else if (a->map[i][j] == 'E')
				(*e)++;
			else if (a->map[i][j] == 'C')
				(*c)++;
			else if (a->map[i][j] != '0' && a->map[i][j] != '1')
				error_exit("Invalid map: Unknown character");
		}
	}
}

void	parsing_map(t_game *a)
{
	int	player;
	int	exit;
	int	collectible;

	player = 0;
	exit = 0;
	collectible = 0;
	check_walls(a);
	count_elements(a, &player, &exit, &collectible);
	if (player != 1)
		error_exit("Invalid map: Exactly one player required");
	if (exit != 1)
		error_exit("Invalid map: Exactly one exit required");
	if (collectible < 1)
		error_exit("Invalid map: At least one collectible required");
}
