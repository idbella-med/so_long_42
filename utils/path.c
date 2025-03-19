/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:55:36 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 21:57:03 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	**duplicate_map(t_game *a)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (a->y + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < a->y)
	{
		copy[i] = ft_strdup(a->map[i]);
		if (!copy[i])
			return (ft_free(copy), NULL);
	}
	copy[i] = NULL;
	return (copy);
}

static int	validate_filled_map(t_game *a, char **copy)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a->y)
	{
		j = -1;
		while (++j < a->x)
			if ((a->map[i][j] == 'C' || a->map[i][j] == 'E')
				&& copy[i][j] != 'F')
				return (ft_free(copy), 0);
	}
	return (ft_free(copy), 1);
}

static void	fill(char **tab, int x, int y)
{
	if (tab[y][x] == '1' || tab[y][x] == 'F'
			|| tab[y][x] == '\0' || tab[y] == NULL)
		return ;
	tab[y][x] = 'F';
	fill(tab, x - 1, y);
	fill(tab, x + 1, y);
	fill(tab, x, y - 1);
	fill(tab, x, y + 1);
}

int	check_valid_path(t_game *a, t_player *player)
{
	char	**copy;

	copy = duplicate_map(a);
	if (!copy)
		return (0);
	fill(copy, player->x, player->y);
	return (validate_filled_map(a, copy));
}
